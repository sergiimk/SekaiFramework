/*========================================================
* CCore.cpp
* @author Sergey Mikhtonyuk
* @date 09 November 2008
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/

#include "CCore.h"
#include "CPluginManager.h"
#include "logging/logging.h"
#include "IExtension.h"
#include "IExtensionPoint.h"
#include "IPluginShadow.h"
#include "IStartListener.h"

#include "module/exception.h"
#include "platform/platform.h"

namespace Extensions
{
	//////////////////////////////////////////////////////////////////////////

	// Instance
	GlobalEnvironment* gEnv;

	//////////////////////////////////////////////////////////////////////////

	CCore::CCore()
		: pCurrentEnvironment(&mEnvironment)
	{
		memset(&mEnvironment, 0, sizeof(GlobalEnvironment));

		gEnv = pCurrentEnvironment;
		pCurrentEnvironment->Core = this;
	}

	//////////////////////////////////////////////////////////////////////////

	void CCore::Initialize(const char* paramsFile)
	{
		if(gEnv->PluginManager)
			throw Module::RuntimeException("Multiple Core initialization");

		mLogModule.Init("Logging.dll");
		create_instance(&gEnv->Logger, Logging::CLSID_CLogService, mLogModule);
		gEnv->Logger->Initialize("Execution.log", "Error.log");

		LogInfoAlways("[Init] Initializing core");
		LogTrace("[Init] Creating plugin manager");

		create_instance<CPluginManager>(&gEnv->PluginManager);
		static_cast<CPluginManager*>(gEnv->PluginManager)->Run(paramsFile);
	}

	//////////////////////////////////////////////////////////////////////////

	CCore::~CCore()
	{
		LogInfoAlways("[Shutdown] Shutting down the core");

		if(gEnv->PluginManager)
			gEnv->PluginManager->Release();

		if(gEnv->Logger)
			gEnv->Logger->Release();
	}

	//////////////////////////////////////////////////////////////////////////

	void CCore::StartExecution(int argc, char *argv[])
	{
		try
		{
			StartExecution_actual(argc, argv);
		}
		catch(Module::Exception& cex)
		{
			LogErrorAlways("%s: %s", cex.className(), cex.message());
		}
		catch(std::exception& stdex)
		{
			LogErrorAlways(stdex.what());
		}
		catch(...)
		{
			LogErrorAlways("Unrecognized exception");
		}
	}

	//////////////////////////////////////////////////////////////////////////

	void CCore::StartExecution_actual(int argc, char *argv[])
	{
		IPluginShadow *pMyShadow = gEnv->PluginManager->FindPluginShadow("core");
		IExtensionPoint *pStartListeners = pMyShadow->FindExtensionPoint("startlisteners");
		size_t nextensions = pStartListeners->getExtensionCount();

		for(size_t i = 0; i != nextensions; ++i)
		{
			IExtension *pEx = pStartListeners->getExtension(i);
			LogTrace("[Startup] Notifying start listener: %s", pEx->Extender()->PluginName().c_str());

			Module::com_ptr<IStartListener> l;
			pEx->Extender()->CreateInstance(pEx->ImplClassID(), UUID_PPV(IStartListener, l.wrapped()));

			if(l)
			{
				l->OnStart(argc, argv);
			}
			else
			{
				LogErrorAlways("[Startup] Failed to create start listener's implementation: %s",
								pEx->Extender()->PluginName().c_str());
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////

	void CCore::RegisterEnvironment(GlobalEnvironment* newEnv)
	{
		memcpy(newEnv, pCurrentEnvironment, sizeof(GlobalEnvironment));
		pCurrentEnvironment = newEnv;
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace
