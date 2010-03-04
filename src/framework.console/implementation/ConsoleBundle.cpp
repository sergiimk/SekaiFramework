/*========================================================
* ConsoleBundle.cpp
* @author Sergey Mikhtonyuk
* @date 17 December 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "ConsoleBundle.h"
#include "ConsoleCommands.h"
#include <boost/regex.hpp>

//////////////////////////////////////////////////////////////////////////

void CConsoleBundle::Start(IBundleContext *context)
{
	m_context = context;
	m_systemBundle = context->getBundle(0);

	ConsoleCommand* cmd = new CmdHelp;
	m_commands.insert(std::make_pair(cmd->getName(), cmd));

	cmd = new CmdStart;
	m_commands.insert(std::make_pair(cmd->getName(), cmd));

	cmd = new CmdStop;
	m_commands.insert(std::make_pair(cmd->getName(), cmd));

	cmd = new CmdInstall;
	m_commands.insert(std::make_pair(cmd->getName(), cmd));

	cmd = new CmdUninstall;
	m_commands.insert(std::make_pair(cmd->getName(), cmd));

	cmd = new CmdStatus;
	m_commands.insert(std::make_pair(cmd->getName(), cmd));

	m_consoleThread = boost::thread(boost::bind(&CConsoleBundle::ThreadRoutine, this));
}

//////////////////////////////////////////////////////////////////////////

void CConsoleBundle::Stop(IBundleContext *context)
{
	m_consoleThread.interrupt();

	if(boost::this_thread::get_id() != m_consoleThread.get_id())
	{
		if(context)
			m_consoleThread.timed_join(boost::posix_time::millisec(1000));

		for(TCommands::iterator it = m_commands.begin(), end = m_commands.end();
			it != end; ++it)
			delete it->second;
	}
}

//////////////////////////////////////////////////////////////////////////

IBundleContext* CConsoleBundle::getContext()
{
	return m_context;
}

//////////////////////////////////////////////////////////////////////////

IBundle* CConsoleBundle::getSystemBundle()
{
	return m_systemBundle;
}

//////////////////////////////////////////////////////////////////////////

CConsoleBundle::TCommands* CConsoleBundle::getCommands()
{
	return &m_commands;
}

//////////////////////////////////////////////////////////////////////////

void CConsoleBundle::ThreadRoutine()
{
	std::string inputBuffer;

	while(!boost::this_thread::interruption_requested())
	{
		std::cout<<">> ";
		std::getline(std::cin, inputBuffer);
		{
			boost::lock_guard<boost::mutex> l(m_consoleLock);
			OnCommand(inputBuffer);
		}
	}
}

//////////////////////////////////////////////////////////////////////////

void CConsoleBundle::OnCommand(const std::string& cmd)
{
	std::vector<std::string> elements;
	SplitCommand(cmd, elements);

	if(elements.empty())
		return;

	const char* pargs[256];

	for(size_t i = 1; i < elements.size(); ++i)
		pargs[i - 1] = elements[i].c_str();

	TCommands::const_iterator it = m_commands.find(elements[0].c_str());

	std::cout << std::endl;

	if(it != m_commands.end())
	{
		it->second->Execute(*this, pargs, elements.size() - 1);
	}
	else
	{
		std::cout<<"unknown command: "<<cmd<<std::endl;
	}

	std::cout << std::endl;
}

//////////////////////////////////////////////////////////////////////////

void CConsoleBundle::SplitCommand(const std::string& cmd, std::vector<std::string>& elements)
{
	boost::regex exp("(\"[^\"]*\")|([^ \"]+)");
	boost::smatch match;

	std::string::const_iterator it = cmd.begin();
	while(boost::regex_search(it, cmd.end(), match, exp))
	{
		std::string res(match[0].first, match[0].second);

		if(res[0] == '\"' && res[res.length() - 1] == '\"')
			res = res.substr(1, res.length() - 2);

		elements.push_back(res);

		it = match[0].second;
	}

}

//////////////////////////////////////////////////////////////////////////
