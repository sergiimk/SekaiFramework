/*========================================================
* ConsoleCommands.h
* @author Sergey Mikhtonyuk
* @date 19 December 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _CONSOLECOMMANDS_H__
#define _CONSOLECOMMANDS_H__

//////////////////////////////////////////////////////////////////////////

#include <string>

class CConsoleBundle;

//////////////////////////////////////////////////////////////////////////

class ConsoleCommand
{
public:
	virtual const char* getName() = 0;
	virtual const char* getShortDescription() = 0;
	virtual const char* getFullDescription() = 0;
	virtual void Execute(CConsoleBundle& console, const char** args, size_t nargs) = 0;

protected:
	com_ptr<IBundle> getBundleFromParam(CConsoleBundle& console, const char* id);
	std::string getStateName(EBundleState state);
};

//////////////////////////////////////////////////////////////////////////

class CmdHelp : public ConsoleCommand
{
public:
	virtual const char* getName() { return "help"; }
	virtual const char* getShortDescription() { return "Displays this message"; }
	virtual const char* getFullDescription() 
	{ 
		return 
"help [command]\n\n\
Displays available commands with short descriptions.\n\
If command parameter is provided displays detailed help on this command."; 
	}
	virtual void Execute(CConsoleBundle& console, const char** args, size_t nargs);
};

//////////////////////////////////////////////////////////////////////////

class CmdStatus : public ConsoleCommand
{
public:
	virtual const char* getName() { return "ss"; }
	virtual const char* getShortDescription() { return "Lists status of all registered bundles"; }
	virtual const char* getFullDescription() 
	{ 
		return 
"ss ID | Name\n\n\
Lists status of all registered bundles in current framework instance.\n\
If bundle ID or symbolic name is specified prints detailed info on the bundle."; 
	}
	virtual void Execute(CConsoleBundle& console, const char** args, size_t nargs);
};

//////////////////////////////////////////////////////////////////////////

class CmdStart : public ConsoleCommand
{
public:
	virtual const char* getName() { return "start"; }
	virtual const char* getShortDescription() { return "Starts specified bundle"; }
	virtual const char* getFullDescription() 
	{ 
		return 
"start ID | NAME\n\n\
Starts bundle by specified ID or symbolic name."; 
	}
	virtual void Execute(CConsoleBundle& console, const char** args, size_t nargs);
};

//////////////////////////////////////////////////////////////////////////

class CmdStop : public ConsoleCommand
{
public:
	virtual const char* getName() { return "stop"; }
	virtual const char* getShortDescription() { return "Stops bundle or the whole framework"; }
	virtual const char* getFullDescription() 
	{ 
		return 
"stop [ID | NAME]\n\n\
Stops bundle by specified ID or symbolic name.\n\
Stops framework in no parameters provided."; 
	}
	virtual void Execute(CConsoleBundle& console, const char** args, size_t nargs);
};

//////////////////////////////////////////////////////////////////////////

class CmdInstall : public ConsoleCommand
{
public:
	virtual const char* getName() { return "install"; }
	virtual const char* getShortDescription() { return "Installs bundle by the specified path or URL"; }
	virtual const char* getFullDescription() 
	{ 
		return 
"install PATH | URL\n\n\
Installs bundle by the specified path or URL."; 
	}
	virtual void Execute(CConsoleBundle& console, const char** args, size_t nargs);
};

//////////////////////////////////////////////////////////////////////////

class CmdUninstall : public ConsoleCommand
{
public:
	virtual const char* getName() { return "uninstall"; }
	virtual const char* getShortDescription() { return "Uninstalls specified bundle"; }
	virtual const char* getFullDescription() 
	{ 
		return 
"uninstall ID | NAME\n\n\
Uninstalls bundle with specified ID or symbolic name."; 
	}
	virtual void Execute(CConsoleBundle& console, const char** args, size_t nargs);
};

//////////////////////////////////////////////////////////////////////////

#endif // _CONSOLECOMMANDS_H__
