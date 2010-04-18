/*========================================================
* main.cpp
* @author Sergey Mikhtonyuk
* @date 21 November 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "framework/Framework.h"
#include "module/module.h"

#if defined OS_WINDOWS
#   include <windows.h>
#   include <crtdbg.h>
#endif

using namespace module;
using namespace Framework;

int main(int argc, char* argv[])
{
    #if defined OS_WINDOWS
	//_crtBreakAlloc = 193;
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	#endif

	ModuleHandle fw(SHARED_LIB_NAME("framework"));

	com_ptr<IFrameworkFactory> factory;
	create_instance(factory, fw);

	com_ptr<IFramework> framework = factory->NewFramework(argc, argv, 0);
	framework->Init();
	framework->Start();

	com_ptr<IBundleContext> fwkContext = framework->getBundleContext();

	IBundle* console = fwkContext->InstallBundle("Framework.Console.exe");

	if(console) console->Start();
	else framework->Stop();

	framework->WaitForStop(0);
	return 0;
}
