/*========================================================
* CLogService.cpp
* @author Sergey Mikhtonyuk
* @date 04 December 2008
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "CLogService.h"
#include <stdio.h>
#include <functional>
#include <algorithm>
#include <fstream>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace  Logging
{
	//////////////////////////////////////////////////////////////////////////

	void CLogService::Initialize(const char* execfile, const char* errorfile)
	{
		mExecFile = execfile;
		mErrorFile = errorfile;
		ClearLog();
	}

	//////////////////////////////////////////////////////////////////////////

	void CLogService::ClearLog()
	{
		std::ofstream ofs;
		ofs.open(mExecFile.c_str(), std::ios_base::out);
		if(!ofs.bad())
			ofs.close();

		ofs.open(mErrorFile.c_str(), std::ios_base::out);
		if(!ofs.bad())
			ofs.close();
	}

	//////////////////////////////////////////////////////////////////////////

	const char* GetPrefix(LogType type)
	{
		switch(type)
		{
		case LogT_TRACE:	return " -TRACE-";
		case LogT_INFO:		return " -INFO-";
		case LogT_WARNING:	return " <<WARNING>>";
		case LogT_ERROR:	return " ===ERROR===";
		default:			return "";
		}
	}

	//////////////////////////////////////////////////////////////////////////

	int WritePrefix(char *buffer, LogType type)
	{
		boost::posix_time::ptime now(boost::posix_time::second_clock::local_time());
		boost::posix_time::time_duration time(now.time_of_day());

		return sprintf(buffer, "[%0.2d:%0.2d:%0.2d] %s\t",
							time.hours(),
							time.minutes(),
							time.seconds(),
							GetPrefix(type));
	}

	//////////////////////////////////////////////////////////////////////////

	void DumpToFile(const std::string& file, const std::string& info)
	{
		std::ofstream ofs;
		ofs.open(file.c_str(), std::ios_base::out | std::ios_base::app);
		if (!ofs.bad())
		{
			ofs << info;
			ofs.close();
		}
	}

	//////////////////////////////////////////////////////////////////////////

	void CLogService::Log(LogType type, const char* format, va_list args)
	{
		char buffer[MAX_MESSAGE_LENGTH];

		int pref = WritePrefix(buffer, type);
		int len = MAX_MESSAGE_LENGTH - pref - 1;

		len = vsnprintf(&buffer[pref], len - 1, format, args);

		NotifyListeners(type, &buffer[pref]);

		if(len == -1)	len = MAX_MESSAGE_LENGTH - 2;
		else			len += pref;

		buffer[len] = '\n';
		buffer[len + 1] = '\0';

		DumpToFile(mExecFile, buffer);
		if(type == LogT_ERROR)
			DumpToFile(mErrorFile, buffer);
	}

	//////////////////////////////////////////////////////////////////////////

	void CLogService::Log(LogType type, const char* format, ...)
	{
		va_list args;
		va_start(args, format);
		Log(type, format, args);
		va_end(args);
	}

	//////////////////////////////////////////////////////////////////////////

	void CLogService::AddListener(Logging::ILogListener *listener)
	{
		mListeners.push_back(listener);
	}

	//////////////////////////////////////////////////////////////////////////

	void CLogService::RemoveListener(ILogListener *listener)
	{
		std::vector<ILogListener*>::iterator it =
			std::find(mListeners.begin(), mListeners.end(), listener);

		if(it != mListeners.end()) mListeners.erase(it);
	}

	//////////////////////////////////////////////////////////////////////////

	void CLogService::NotifyListeners(LogType type, const char* msg) const
	{
		typedef void (ILogListener::*lfT)(const char*);
		lfT fun = 0;

		switch(type)
		{
		case LogT_TRACE:
			fun = &ILogListener::OnTrace;
			break;
		case LogT_INFO:
			fun = &ILogListener::OnInfo;
			break;
		case LogT_WARNING:
			fun = &ILogListener::OnWarning;
			break;
		case LogT_ERROR:
			fun = &ILogListener::OnError;
			break;
		};

        for(size_t i = 0; i != mListeners.size(); ++i)
            (mListeners[i]->*fun)(msg);
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace
