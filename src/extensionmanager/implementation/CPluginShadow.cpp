/*========================================================
* CPluginShadow.cpp
* @author Sergey Mikhtonyuk
* @date 16 November 2008
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/

#include "CPluginShadow.h"
#include "logging/logging.h"
#include "CPluginManager.h"
#include "IExtension.h"
#include "IExtensionPoint.h"
#include "CCore.h"
#include <boost/bind.hpp>
#include <algorithm>

namespace Extensions
{
	//////////////////////////////////////////////////////////////////////////

	CPluginShadow::CPluginShadow()
	{
	}

	//////////////////////////////////////////////////////////////////////////

	CPluginShadow::~CPluginShadow()
	{
		LogTrace("[Shutdown] Unloading shadow: %s", mPluginName.c_str());

		std::for_each(mExtensions.begin(), mExtensions.end(), boost::mem_fn(&IUnknown::Release));
		std::for_each(mExtensionPoints.begin(), mExtensionPoints.end(), boost::mem_fn(&IUnknown::Release));
	}

	//////////////////////////////////////////////////////////////////////////

	void CPluginShadow::FinalConstruct(const std::string &pluginName, int version)
	{
		/// \todo refactor to common assembly prefix\suffix
		mVersion = version;
		mPluginName = pluginName;
		mModuleName = pluginName + ".dll";
	}

	//////////////////////////////////////////////////////////////////////////

	module::ModuleError CPluginShadow::CreateInstance(const module::guid &clsid, const module::guid &riid, void **ppv)
	{
		module::ModuleError err;

		if(!mModule.IsLoaded())
		{
			if(err = LoadModule()) 
				return err;
		}

		if(err = create_instance(ppv, riid, clsid, mModule))
		{
			LogWarningAlways("CreateInstance request failed, target: %s", mPluginName.c_str());
		}
		return err;
	}

	//////////////////////////////////////////////////////////////////////////

	module::ModuleError CPluginShadow::CreateInstance(const module::guid &riid, void **ppv)
	{
		module::ModuleError err;
		if(!mModule.IsLoaded())
		{
			if(err = LoadModule()) 
				return err;
		}

		if(err = create_instance(ppv, riid, mModule))
		{
			LogWarningAlways("CreateInstance request failed, target: %s", mPluginName.c_str());
		}
		return err;
	}

	//////////////////////////////////////////////////////////////////////////

	module::ModuleError CPluginShadow::LoadModule()
	{
		LogTrace("Loading plugin module: %s", mModuleName.c_str());

		module::ModuleError err = mModule.Init(mModuleName.c_str());
		if(err) return err;
		return static_cast<CPluginManager*>(gEnv->PluginManager)->OnPluginLoad(this);
	}

	//////////////////////////////////////////////////////////////////////////

	void CPluginShadow::Shutdown()
	{
		LogTrace("[Shutdown] Shadow shutdown: %s", mPluginName.c_str());
		mModule.Shutdown();
	}

	//////////////////////////////////////////////////////////////////////////

	bool CPluginShadow::Exports(const module::guid &clsid)
	{
		return mExportTable.find(clsid) != mExportTable.end();
	}

	//////////////////////////////////////////////////////////////////////////

	bool CPluginShadow::Provides(const std::string &expoint)
	{
		return FindExtensionPoint(expoint) != 0;
	}

	//////////////////////////////////////////////////////////////////////////

	bool CPluginShadow::Extends(const std::string &expoint)
	{
		for(std::vector<IExtension*>::const_iterator it = mExtensions.begin();
			it != mExtensions.end(); ++it)
			if((*it)->ExtensionPoint()->UniqueID() == expoint) return true;
		return false;
	}

	//////////////////////////////////////////////////////////////////////////

	IExtensionPoint* CPluginShadow::FindExtensionPoint(const std::string &name)
	{
		for(std::vector<IExtensionPoint*>::const_iterator it = mExtensionPoints.begin();
			it != mExtensionPoints.end(); ++it)
			if((*it)->ID() == name) return *it;
		return 0;
	}

} // namespace
