/*========================================================
* ILogListener.h
* @author Sergey Mikhtonyuk
* @date 04 December 2008
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _ILOG_LISTENER_H__
#define _ILOG_LISTENER_H__

#include "module/interfaces.h"
#include <string>

namespace Logging
{
	/// Interface for objects that want to intercept the logging messages
	/** @ingroup Logging */
	sf_interface ILogListener : public module::IUnknown
	{
		sf_uuid("b1d0733f-5539-4c8c-b53e-535dbaf69266")

		/// Trace message
		virtual void OnTrace	(const char* msg) = 0;
		
		/// Info message
		virtual void OnInfo		(const char* msg) = 0;
		
		/// Warning message
		virtual void OnWarning	(const char* msg) = 0;

		/// Error message
		virtual void OnError	(const char* msg) = 0;
	};


} // namespace

#endif
