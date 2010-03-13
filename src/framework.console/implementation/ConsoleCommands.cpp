/*========================================================
* ConsoleCommands.cpp
* @author Sergey Mikhtonyuk
* @date 19 December 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "ConsoleBundle.h"
#include "ConsoleCommands.h"
#include "framework/reflection.h"
#include <stdio.h>

//////////////////////////////////////////////////////////////////////////

com_ptr<IBundle> ConsoleCommand::getBundleFromParam(CConsoleBundle &console, const char *id)
{
	com_ptr<IBundle> bndl;
	size_t pid;

	if(sscanf(id, "%ul", &pid) == 1)
		bndl = console.getContext()->getBundle(pid);

	return bndl;
}

//////////////////////////////////////////////////////////////////////////

std::string ConsoleCommand::getStateName(EBundleState state)
{
	char stateBuf[128];
	Reflection::UserType* stateT = static_cast<Reflection::UserType*>(Reflection::type_of<EBundleState>());

	stateT->ToString(&state, stateBuf, 128);
	return stateBuf;
}

//////////////////////////////////////////////////////////////////////////

void CmdHelp::Execute(CConsoleBundle &console, const char **args, size_t nargs)
{
	typedef CConsoleBundle::TCommands TCmds;
	TCmds& cmds = *console.getCommands();

	if(nargs == 0)
	{
		for(TCmds::const_iterator it = cmds.begin(); it != cmds.end(); ++it)
		{
			std::cout << it->second->getName()
				<< '\t' << it->second->getShortDescription()<<std::endl;
		}
	}
	else
	{
		TCmds::const_iterator it = cmds.find(args[0]);
		if(it != cmds.end())
			std::cout << it->second->getFullDescription() << std::endl;
		else
			std::cout << "no help associated with: " << args[0] << std::endl;
	}
}

//////////////////////////////////////////////////////////////////////////

void CmdStatus::Execute(CConsoleBundle &console, const char **args, size_t nargs)
{
	if(!nargs)
	{
		DynArrayImplOwned<com_ptr<IBundle> > bundles;
		console.getContext()->getBundles(bundles);

		std::cout<<"ID\tState\tBundle"<<std::endl;

		for(size_t i = 0, size = bundles.size(); i != size; ++i)
		{
			IBundle* bndl = bundles[i];
			std::cout<<bndl->getBundleId()<<'\t'<<getStateName(bndl->getState())<<'\t'<<bndl->getLocation()<<std::endl;
		}
	}
	else
	{
		com_ptr<IBundle> bndl = getBundleFromParam(console, args[0]);

		if(!bndl)
		{
			std::cout<<"Invalid bundle ID/Name"<<std::endl;
			return;
		}

		std::cout<< "ID: " << bndl->getBundleId() << std::endl
			<< "Name: " << "<unavailable>" << std::endl
			<< "Location: " << bndl->getLocation() << std::endl
			<< "State: " << getStateName(bndl->getState()) << std::endl;
	}
}

//////////////////////////////////////////////////////////////////////////

void CmdStart::Execute(CConsoleBundle &console, const char **args, size_t nargs)
{
	if(nargs == 1)
	{
		com_ptr<IBundle> bndl = getBundleFromParam(console, args[0]);

		if(bndl)
			bndl->Start();
		else
			std::cout<<"Invalid bundle ID/Name"<<std::endl;
	}
	else
	{
		std::cout<<"Invalid number of parameters"<<std::endl;
	}
}

//////////////////////////////////////////////////////////////////////////

void CmdStop::Execute(CConsoleBundle &console, const char **args, size_t nargs)
{
	if(nargs)
	{
		com_ptr<IBundle> bndl = getBundleFromParam(console, args[0]);

		if(bndl)
		{
			size_t id = bndl->getBundleId();

			if(id == 0 || id == console.getContext()->getBundle()->getBundleId())
			{
				console.Stop(0);
				console.getSystemBundle()->Stop();
				return;
			}
			else
			{
				bndl->Stop();
			}
		}
		else
		{
			std::cout<<"Invalid bundle ID/Name"<<std::endl;
		}
	}
	else
	{
		console.Stop(0);
		console.getSystemBundle()->Stop();
	}
}

//////////////////////////////////////////////////////////////////////////

void CmdInstall::Execute(CConsoleBundle &console, const char **args, size_t nargs)
{
	if(nargs == 1)
	{
		console.getContext()->InstallBundle(args[0]);
	}
	else
	{
		std::cout<<"Invalid number of parameters"<<std::endl;
	}
}

//////////////////////////////////////////////////////////////////////////

void CmdUninstall::Execute(CConsoleBundle &console, const char **args, size_t nargs)
{
	if(nargs == 1)
	{
		com_ptr<IBundle> bndl = getBundleFromParam(console, args[0]);

		if(bndl)
			bndl->Uninstall();
		else
			std::cout<<"Invalid bundle ID/Name"<<std::endl;
	}
	else
	{
		std::cout<<"Invalid number of parameters"<<std::endl;
	}
}

//////////////////////////////////////////////////////////////////////////
