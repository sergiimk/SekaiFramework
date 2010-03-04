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
		mVersion = version;
		mPluginName = pluginName;
		mModuleName = pluginName + ".dll";
	}

	//////////////////////////////////////////////////////////////////////////

	Module::HResult CPluginShadow::CreateInstance(const Module::GUID &clsid, const Module::GUID &riid, void **ppv)
	{
		if(!mModule.IsLoaded())
		{
			Module::HResult hr = LoadModule();
			if(SF_FAILED(hr)) return hr;
		}

		Module::HResult hr = create_instance(ppv, riid, clsid, mModule);
		if(SF_FAILED(hr))
		{
			LogWarningAlways("CreateInstance request failed, target: %s", mPluginName.c_str());
		}
		return hr;
	}

	//////////////////////////////////////////////////////////////////////////

	Module::HResult CPluginShadow::CreateInstance(const Module::GUID &riid, void **ppv)
	{
		if(!mModule.IsLoaded())
		{
			Module::HResult hr = LoadModule();
			if(SF_FAILED(hr)) return hr;
		}

		Module::HResult hr = create_instance(ppv, riid, mModule);
		if(SF_FAILED(hr))
		{
			LogWarningAlways("CreateInstance request failed, target: %s", mPluginName.c_str());
		}
		return hr;
	}

	//////////////////////////////////////////////////////////////////////////

	Module::HResult CPluginShadow::LoadModule()
	{
		LogTrace("Loading plugin module: %s", mModuleName.c_str());

		Module::HResult hr = mModule.Init(mModuleName.c_str());
		if(SF_FAILED(hr)) return hr;
		return static_cast<CPluginManager*>(gEnv->PluginManager)->OnPluginLoad(this);
	}

	//////////////////////////////////////////////////////////////////////////

	void CPluginShadow::Shutdown()
	{
		LogTrace("[Shutdown] Shadow shutdown: %s", mPluginName.c_str());
		mModule.Shutdown();
	}

	//////////////////////////////////////////////////////////////////////////

	bool CPluginShadow::Exports(const Module::GUID &clsid)
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
