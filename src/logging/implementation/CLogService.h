/*========================================================
* CLogService.h
* @author Sergey Mikhtonyuk
* @date 04 December 2008
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _CLOGSERVICE_H__
#define _CLOGSERVICE_H__

#include "ILogService.h"
#include "module/implementations.h"

#include <string>
#include <vector>

namespace Logging
{
	//////////////////////////////////////////////////////////////////////////

	#define MAX_MESSAGE_LENGTH 4096

	//////////////////////////////////////////////////////////////////////////
	
	/// Logging service implementation
	/** @ingroup Logging */
	class NOVTABLE CLogService : 
		public Module::ComRootObject<Module::MultiThreadModel>,
		public ILogService
	{
	public:

		DECLARE_IMPLEMENTATION(CLogService)

		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(ILogService)
		END_INTERFACE_MAP()

		void Initialize(const char* execfile, const char* errorfile);
		void ClearLog();
		void Log(LogType type, const char* format, va_list args);
		void Log(LogType type, const char* format, ...);
		
		void AddListener(ILogListener *listener);
		void RemoveListener(ILogListener *listener);
		void NotifyListeners(LogType type, const char* msg) const;

	private:
		std::string mExecFile;
		std::string mErrorFile;
		std::vector<ILogListener*> mListeners;
	};



} // namespace

#endif // _CLOGSERVICE_H__
