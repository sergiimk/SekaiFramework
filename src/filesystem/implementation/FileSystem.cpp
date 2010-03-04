/*========================================================
* FileSystem.cpp
* @author Sergey Mikhtonyuk
* @date 19 November 2008
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/

#include "FileSystem.h"
#include "implementation/CFileSystem.h"
#include "framework/Framework.h"
#include "module/module.h"
#include "module/intellectual.h"

using namespace Framework;

namespace FileSystem
{
	DECLARE_MODULE_MAP()

	/// Activator that registers FileSystem service
	/** @ingroup FileSystem  */
	class NOVTABLE CFSActivator :
		public Module::ComRootObject<>,
		public IBundleActivator
	{
	public:

		DECLARE_IMPLEMENTATION(CFSActivator)

		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(IBundleActivator)
		END_INTERFACE_MAP()

		virtual void Start(IBundleContext* context)
		{
			Module::ModuleHandle m(&GetModuleMap);

			Module::com_ptr<IFileSystem> fs;
			if(SF_SUCCEEDED( create_instance(fs, m) ))
				context->RegisterService(uuid_of(IFileSystem), fs);
		}

		virtual void Stop(IBundleContext* context)
		{
		}
	};

	BEGIN_MODULE_MAP()
		OBJECT_ENTRY(CLSID_CFileSystem, uuid_of(IFileSystem), CFileSystem)
		OBJECT_ENTRY(CLSID_BundleActivator, uuid_of(IBundleActivator), CFSActivator)
	END_MODULE_MAP()

} // namespace
