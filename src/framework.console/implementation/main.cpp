/*========================================================
* main.cpp
* @author Sergey Mikhtonyuk
* @date 21 November 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "Framework/Framework.h"
#include "Module/Module.h"

#include <windows.h>
#include <crtdbg.h>

using namespace Module;
using namespace Framework;

int main(int argc, char* argv[])
{
	//_crtBreakAlloc = 193;
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	ModuleHandle fw("Framework.dll");
	
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
