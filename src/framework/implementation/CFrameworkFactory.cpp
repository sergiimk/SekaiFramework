/*========================================================
* CFrameworkFactory.cpp
* @author Sergey Mikhtonyuk
* @date 21 November 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "CFrameworkFactory.h"
#include "CSystemBundle.h"
#include <memory>

namespace Framework
{
	//////////////////////////////////////////////////////////////////////////

	com_ptr<IFramework> CFrameworkFactory::NewFramework(int argc, char *argv[], const char* settingsFile)
	{
		CSystemBundle* sys_bundle;

		if(SF_FAILED(create_instance_impl(&sys_bundle)))
			return com_ptr<IFramework>();

		sys_bundle->FinalConstruct(argc, argv, settingsFile);

		com_ptr<IFramework> framework(sys_bundle);
		sys_bundle->Release();

		return framework;
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace
