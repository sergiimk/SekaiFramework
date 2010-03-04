/*========================================================
* Logging.cpp
* @author Sergey Mikhtonyuk
* @date 13 December 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "CLogService.h"
#include "logging.h"
#include "framework/Framework.h"
#include "module/module.h"
#include "module/intellectual.h"

using namespace Framework;

namespace Logging
{
	/// Activator that registers FileSystem service
	/** @ingroup FileSystem  */
	class NOVTABLE CLogActivator :
		public Module::ComRootObject<>,
		public IBundleActivator
	{
	public:

		DECLARE_IMPLEMENTATION(CLogActivator)

		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(IBundleActivator)
		END_INTERFACE_MAP()

		virtual void Start(IBundleContext* context)
		{
			Module::com_ptr<ILogService> log;
			create_instance<CLogService, ILogService>(log);
			context->RegisterService(uuid_of(ILogService), log);
		}

		virtual void Stop(IBundleContext* context)
		{
		}
	};

	BEGIN_MODULE_MAP()
		OBJECT_ENTRY(CLSID_CLogService, uuid_of(ILogService), CLogService)
		OBJECT_ENTRY(CLSID_BundleActivator, uuid_of(IBundleActivator), CLogActivator)
	END_MODULE_MAP()

} // namespace
