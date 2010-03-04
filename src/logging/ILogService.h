/*========================================================
* ILogService.h
* @author Sergey Mikhtonyuk
* @date 04 December 2008
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
/** @defgroup Logging Logging
 *  Logging and exception handling library */

#ifndef _ILOGSERVICE_H__
#define _ILOGSERVICE_H__

#include "platform/platform.h"
#include "ILogListener.h"
#include "extensionmanager/GlobalEnvironment.h"
#include <stdarg.h>

namespace Logging
{
	//////////////////////////////////////////////////////////////////////////
	// This enables extended argument checking by GCC.
	// Put this after the function or method declaration (not the definition!),
	// between the final closing parenthesis and the semicolon.
	// The first parameter indicates the 1-based index of the format string
	// parameter, the second parameter indicates the 1-based index of the first
	// variable parameter.
	//
	// Example:
	// void foobar(int a, const char *fmt, ...) PRINTF_PARAMS(2, 3);
	//
	// For va_list based printf style functions, specfy 0 as the second parameter.
	// Example:
	//   void foobarv(int a, const char *fmt, va_list ap) PRINTF_PARAMS(2, 0);
	//
	// Note that 'this' is counted as a method argument. For non-static methods,
	// add 1 to the indices.
	//////////////////////////////////////////////////////////////////////////
	#ifdef COMPILER_GNUC
		#define PRINTF_PARAMS(...) __attribute__ ((format (printf, __VA_ARGS__)))
		#define SCANF_PARAMS(...) __attribute__ ((format (scanf, __VA_ARGS__)))
	#else
		#define PRINTF_PARAMS(...)
		#define SCANF_PARAMS(...)
	#endif

	//////////////////////////////////////////////////////////////////////////

	// Logging level affects to log functions without *Always
	// Values [0..4] 4 - maximum
	#define LOG_LEVEL 4

	//////////////////////////////////////////////////////////////////////////

	/// Logging types that defines the importance of logging
	enum LogType
	{
		LogT_TRACE		= 0,
		LogT_INFO		= 1,
		LogT_WARNING	= 2,
		LogT_ERROR		= 3,
	};

	//////////////////////////////////////////////////////////////////////////

	/// Logging service interface
	/** @ingroup Logging */
	sf_interface ILogService : public Module::IUnknown
	{
		sf_uuid("aa82aafb-be77-4b20-ab68-e03b294cf7b5")

		/// Creates logging files
		virtual void Initialize(const char* execfile, const char* errorfile) = 0;

		/// Clears all log files
		virtual void ClearLog() = 0;

		/// Logs message with specified logging type
		virtual void Log(LogType type, const char* format, va_list args) PRINTF_PARAMS(3, 0) = 0;

		/// Register log listener
		virtual void AddListener(ILogListener *listener) = 0;

		/// Removes log listener
		virtual void RemoveListener(ILogListener *listener) = 0;
	};

	//////////////////////////////////////////////////////////////////////////

	#if LOG_LEVEL >= 4
		#define LogTrace(format, ...)	Logging::_LogTraceAlways(format, ## __VA_ARGS__)
	#endif
	#if LOG_LEVEL >= 3
		#define LogInfo(format, ...)	Logging::_LogInfoAlways(format, ## __VA_ARGS__)
	#endif
	#if LOG_LEVEL >= 2
		#define LogWarning(format, ...) Logging::_LogWarningAlways(format, ## __VA_ARGS__)
	#endif
	#if LOG_LEVEL >= 1
		#define LogError(format, ...)	Logging::_LogErrorAlways(format, ## __VA_ARGS__)
	#endif

	#define LogTraceAlways(format, ...)		Logging::_LogTraceAlways(format, ## __VA_ARGS__)
	#define LogInfoAlways(format, ...)		Logging::_LogInfoAlways(format, ## __VA_ARGS__)
	#define LogWarningAlways(format, ...)	Logging::_LogWarningAlways(format, ## __VA_ARGS__)
	#define LogErrorAlways(format, ...)		Logging::_LogErrorAlways(format, ## __VA_ARGS__)

	//////////////////////////////////////////////////////////////////////////

	void _LogTraceAlways(const char *format, ...) PRINTF_PARAMS(1, 2);
	inline void _LogTraceAlways(const char *format, ...)
	{
		if(Extensions::gEnv && Extensions::gEnv->Logger)
		{
			va_list args;
			va_start(args, format);
			Extensions::gEnv->Logger->Log(LogT_TRACE, format, args);
			va_end(args);
		}
	}

	void _LogInfoAlways(const char *format, ...) PRINTF_PARAMS(1, 2);
	inline void _LogInfoAlways(const char *format, ...)
	{
		if(Extensions::gEnv && Extensions::gEnv->Logger)
		{
			va_list args;
			va_start(args, format);
			Extensions::gEnv->Logger->Log(LogT_INFO, format, args);
			va_end(args);
		}
	}

	void _LogWarningAlways(const char *format, ...) PRINTF_PARAMS(1, 2);
	inline void _LogWarningAlways(const char *format, ...)
	{
		if(Extensions::gEnv && Extensions::gEnv->Logger)
		{
			va_list args;
			va_start(args, format);
			Extensions::gEnv->Logger->Log(LogT_WARNING, format, args);
			va_end(args);
		}
	}

	void _LogErrorAlways(const char *format, ...) PRINTF_PARAMS(1, 2);
	inline void _LogErrorAlways(const char *format, ...)
	{
		if(Extensions::gEnv && Extensions::gEnv->Logger)
		{
			va_list args;
			va_start(args, format);
			Extensions::gEnv->Logger->Log(LogT_ERROR, format, args);
			va_end(args);
		}
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace

#endif // _ILOGSERVICE_H__
