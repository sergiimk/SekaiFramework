/*========================================================
* IScriptObject.h
* @author Sergey Mikhtonyuk
* @date 07 Feb 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _ISCRIPTOBJECT_H__
#define _ISCRIPTOBJECT_H__

#include "module/interfaces.h"
#include "Scripting_fwd.h"

namespace Script
{
	/// Interface for manipulation on script objects
	/** @ingroup Script */
	sf_interface IScriptObject : public module::IUnknown
	{
		sf_uuid("7d18bfd5-dc29-4894-b684-f1990484af61")

		/// Checks if member with specified name exists
		virtual bool HasMember(const char* mem_name) = 0;

		/// Retrieves member value by specified name
		virtual bool GetMember(const char* mem_name, SScriptAny& out_mem) = 0;
	};
}

#endif //_ISCRIPTOBJECT_H__
