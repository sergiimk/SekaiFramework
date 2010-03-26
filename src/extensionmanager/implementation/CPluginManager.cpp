#include "SekaiCore.h"

#include "CExtension.h"
#include "CPluginShadow.h"
#include "CPluginManager.h"
#include "CExtensionPoint.h"

#include "module/module.h"
#include "filesystem/FileSystem.h"
#include "common/stack_string.h"
#include <boost/bind.hpp>
#include <cctype>
#include <algorithm>

namespace Extensions
{
	using namespace Module;
	using namespace filesystem;

	//////////////////////////////////////////////////////////////////////////
	// Init / Shutdown
	//////////////////////////////////////////////////////////////////////////

	CPluginManager::CPluginManager() : mCoreParams(0)
	{
	}

	//////////////////////////////////////////////////////////////////////////

	void CPluginManager::Run(const char* paramsFile)
	{
		LoadCorePlugins();

		// parse settings file
		if(paramsFile)
		{
			LogTrace("[Init] Loading core settings file");
			mCoreParams = new CoreParams;
			if(!mCoreParams->ParseFile(paramsFile))
			{
				LogWarning("[Init] Loading failed, proceeding with default settings");
				delete mCoreParams;
				mCoreParams = 0;
			}
		}

		LoadPlugins();

		if(mCoreParams) { delete mCoreParams; mCoreParams = 0; }
	}

	//////////////////////////////////////////////////////////////////////////

	CPluginManager::~CPluginManager()
	{
		// Shutting down used shadows in reverse to its creation order
		std::for_each(mCreationStack.rbegin(), mCreationStack.rend(),
			boost::bind(&CPluginShadow::Shutdown, _1));

		// Release plug-in graph (now released all loaded modules)
		std::for_each(mShadows.begin(), mShadows.end(),
			boost::bind(&IUnknown::Release,
			boost::bind(&TShadowMap::value_type::second, _1)));
	}



	//////////////////////////////////////////////////////////////////////////
	// Core plug-ins
	//////////////////////////////////////////////////////////////////////////

	Module::HResult CPluginManager::LoadCorePlugins()
	{
		LogTrace("[Init] Loading core plug-ins");

		// Initializing core-plugin
		CPluginShadow *pShadow = CreatePluginShadow("core", 1);
		pShadow->mExportTable.insert(CLSID_CCore);
		CreateExtensionPoint(pShadow, "startlisteners", uuid_of(IStartListener));

		// Initializing file system
		return SF_S_OK;
	}



	//////////////////////////////////////////////////////////////////////////
	// Plug-in loading
	//////////////////////////////////////////////////////////////////////////

	void CPluginManager::LoadPlugins()
	{
		LogTrace("[Init] Loading regular plug-ins");

		// Find all xml files
		std::vector<path> deffiles;
		deffiles.reserve(50);
		FindDefinitionFiles(deffiles);

		// Parse them and pass them a visitors
		std::vector<CPluginDefVisitor> visitors(deffiles.size());
		ParseDefinitions(visitors, deffiles);

		// Create shadows
		CreateShadows(visitors);
		// Delayed step, so that all shadows would be accessible
		BindPlugins(visitors);

		LogInfoAlways("[Init] %d plug-ins loaded", mShadows.size());
	}

	//////////////////////////////////////////////////////////////////////////

	void CPluginManager::FindDefinitionFiles(std::vector<path>& files)
	{
		stack_string<8> ext = ".xml";

		directory_iterator dir(path::current_dir());

		while(dir)
		{
			path current = dir.current();

			if(current.is_file() && *ext == current.extension())
				files.push_back(current);

			++dir;
		}
	}

	//////////////////////////////////////////////////////////////////////////

	void CPluginManager::ParseDefinitions(
		std::vector<CPluginDefVisitor> &visitors,
		std::vector<path> &files)
	{
		for(size_t i = 0, size = files.size(); i < size; ++i)
		{
			try
			{
				TiXmlDocument doc;
				doc.LoadFile(files[i].c_str());

				if(!doc.FirstChild())
				{
					LogErrorAlways("XML parsing failed, file: %s", files[i].c_str());
					continue;
				}

				doc.Accept(&visitors[i]);
			}
			catch(Module::Exception& ex)
			{
				visitors[i].PluginName.clear();
				LogErrorAlways("Plugin definition load failed: %s, in %s", ex.message(), files[i].c_str());
				continue;
			}

			// Check the settings
			if(mCoreParams && !mCoreParams->ShouldLoad(visitors[i].PluginName.c_str()))
			{
				LogTrace("[init] Ignoring %s plugin by filter...", visitors[i].PluginName.c_str());
				visitors[i].PluginName.clear();
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////

	void CPluginManager::CreateShadows(std::vector<CPluginDefVisitor>& visitors)
	{
		for(size_t i = 0; i < visitors.size(); ++i)
		{
			// If plugin parsed successfully
			if(!visitors[i].PluginName.size()) continue;

			CPluginShadow *pShadow = CreatePluginShadow(visitors[i].PluginName, visitors[i].Version);

			// Filling the export table
			for(CPluginDefVisitor::TExports::const_iterator it = visitors[i].Exports.begin();
				it != visitors[i].Exports.end(); ++it)
			{
				pShadow->mExportTable.insert((*it)->ClassGUID);
			}

			// Filling the extension points
			for(CPluginDefVisitor::TExtensionPoints::const_iterator it = visitors[i].ExtensionPoints.begin();
				it != visitors[i].ExtensionPoints.end();
				++it)
			{
				CreateExtensionPoint(pShadow, (*it)->PointID, (*it)->InterfaceID);
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////

	void CPluginManager::BindPlugins(std::vector<CPluginDefVisitor>& visitors)
	{
		/// \todo Check prerequisites
		for(size_t i = 0; i < visitors.size(); ++i)
		{
			// If plugin parsed successfully
			if(!visitors[i].PluginName.size()) continue;

			// For each extension
			for(CPluginDefVisitor::TExtensions::iterator it = visitors[i].Extensions.begin();
				it != visitors[i].Extensions.end(); ++it)
			{
				std::string extendee, point;
				ParseExtesionPoint((*it)->PointID, extendee, point);

				// Find extendee & provider
				CPluginShadow *pExtender = mShadows.find(visitors[i].PluginName)->second;
				TShadowMap::const_iterator sme = mShadows.find(extendee);
				if(sme == mShadows.end())
				{
					LogWarningAlways("Extendee not found: %s", extendee.c_str());
					continue;
				}
				CPluginShadow *pExtendee = sme->second;

				// Find extension point
				IExtensionPoint *pPoint = pExtendee->FindExtensionPoint(point);
				if(!pPoint)
				{
					LogWarningAlways("Extension point not found: %s", point.c_str());
					continue;
				}

				// Create new extension object
				IExtension *pExtension = CreateExtension(pExtender, pPoint, (*it)->ClassID, (*it)->PropertyMap);
			}
		}
	}


	//////////////////////////////////////////////////////////////////////////
	// Shadows
	//////////////////////////////////////////////////////////////////////////

	CPluginShadow* CPluginManager::CreatePluginShadow(const std::string& name, int version)
	{
		LogTrace("[Init] Creating plug-in shadow: %s", name.c_str());

		CPluginShadow *pShadow;
		create_instance_impl<CPluginShadow>(&pShadow);
		pShadow->FinalConstruct(name, version);

		mShadows.insert(std::make_pair(name, pShadow));
		return pShadow;
	}

	//////////////////////////////////////////////////////////////////////////

	CExtensionPoint* CPluginManager::CreateExtensionPoint(CPluginShadow* provider, const std::string &name, const Module::GUID &iid)
	{
		LogTrace("[Init] Creating extension point: %s", name.c_str());

		CExtensionPoint *pEP;
		create_instance_impl<CExtensionPoint>(&pEP);
		pEP->mName = name;
		pEP->mFullName = provider->PluginName() + "::" + name;
		pEP->mInterfaceID = iid;
		pEP->mProvider = provider;
		provider->mExtensionPoints.push_back(pEP);

		return pEP;
	}

	//////////////////////////////////////////////////////////////////////////

	CExtension* CPluginManager::CreateExtension(CPluginShadow* extender,
		IExtensionPoint* exPoint, const Module::GUID& classID, std::map<std::string, std::string>& paramMap)
	{
		LogTrace("[Init] Creating extension, point: %s", exPoint->UniqueID().c_str());

		CExtension *pEx;
		create_instance_impl<CExtension>(&pEx);
		pEx->pExtender = extender;
		pEx->pExtensionPoint = exPoint;
		pEx->mImplClassID = classID;
		std::swap(pEx->mParameterMap, paramMap);

		extender->mExtensions.push_back(pEx);
		CExtensionPoint *pEP = static_cast<CExtensionPoint*>(exPoint);
		pEP->mExtensions.push_back(pEx);

		return pEx;
	}

	//////////////////////////////////////////////////////////////////////////
	// Runtime
	//////////////////////////////////////////////////////////////////////////

	HResult CPluginManager::OnPluginLoad(CPluginShadow *pShadow)
	{
		// Initializes plugin and puts it to creation stack
		LogTrace("Loading plugin binary: %s", pShadow->ModuleName().c_str());
		mCreationStack.push_back(pShadow);

		com_ptr<IPlugin> plugin;
		pShadow->CreateInstance(UUID_PPV(IPlugin, plugin.wrapped()));
		if(plugin)
			plugin->Initialize(gEnv->Core->Environment(), pShadow);
		return SF_S_OK;
	}


	//////////////////////////////////////////////////////////////////////////
	// Service
	//////////////////////////////////////////////////////////////////////////

	IPluginShadow* CPluginManager::FindPluginShadow(const std::string &name)
	{
		std::string n(name);
		std::transform(n.begin(), n.end(), n.begin(), tolower);
		TShadowMap::const_iterator it = mShadows.find(n);
		if(it != mShadows.end())
			return it->second;

		return 0;
	}

	//////////////////////////////////////////////////////////////////////////

	IExtensionPoint* CPluginManager::FindExtensionPoint(const std::string &name)
	{
		std::string plugin, point;
		ParseExtesionPoint(name, plugin, point);
		std::transform(plugin.begin(), plugin.end(), plugin.begin(), tolower);
		std::transform(point.begin(), point.end(), point.begin(), tolower);

		if(!point.size()) return 0;

		IPluginShadow *pShadow = FindPluginShadow(plugin);
		if(!pShadow) return 0;

		return pShadow->FindExtensionPoint(point);
	}

	//////////////////////////////////////////////////////////////////////////

	void CPluginManager::ParseExtesionPoint(const std::string& str, std::string& plugin, std::string& point)
	{
		size_t sep = str.find("::");
		if(sep == std::string::npos) { plugin = str; return; }

		plugin = str.substr(0, sep);
		point = str.substr(sep + 2, std::string::npos);
	}
} // namespace
