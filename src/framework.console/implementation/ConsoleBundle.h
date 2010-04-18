/*========================================================
* ConsoleBundle.h
* @author Sergey Mikhtonyuk
* @date 17 December 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _CONSOLEBUNDLE_H__
#define _CONSOLEBUNDLE_H__

#include "framework/Framework.h"
#include "module/implementations.h"
#include "common/stringutils.h"
#include <boost/thread.hpp>
#include <iostream>
#include <map>

using namespace module;
using namespace Framework;

class ConsoleCommand;

class NOVTABLE CConsoleBundle : 
	public module::ComRootObject<>,
	public IBundleActivator
{
public:
	
	DECLARE_IMPLEMENTATION(CConsoleBundle)

	BEGIN_INTERFACE_MAP()
		INTERFACE_ENTRY(IBundleActivator)
	END_INTERFACE_MAP()

	virtual void Start(IBundleContext* context);
	virtual void Stop(IBundleContext* context);

	typedef std::map<const char*, ConsoleCommand*, cstrcmp_less> TCommands;

	IBundleContext* getContext();
	IBundle* getSystemBundle();
	TCommands* getCommands();

private:
	void ThreadRoutine();
	void OnCommand(const std::string& cmd);
	void SplitCommand(const std::string& cmd, std::vector<std::string>& elements);

private:
	TCommands m_commands;
	boost::thread m_consoleThread;
	boost::mutex m_consoleLock;
	IBundleContext* m_context;
	IBundle* m_systemBundle;
};

#endif // _CONSOLEBUNDLE_H__
