/*========================================================
* IScriptManager.h
* @author Sergey Mikhtonyuk
* @date 06 July 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _ISCRIPTMANAGER_H__
#define _ISCRIPTMANAGER_H__

#include "Scripting_fwd.h"
#include "module/interfaces.h"
#include "reflection/reflection_fwd.h"

// Fwd for whole-module export
namespace module { class ModuleHandle; }

namespace Script
{
	/// Manages the script execution and implements C++ type exporting
	/** Common interaction pattern is:
	 *  - Init()
	 *  - Export user-defined types using ExportType() function
	 *  - Run existing script using RunScript() function
	 *  - Manually control script execution
	 *  - Shutdown()
	 *  @ingroup Script */
	sf_interface IScriptManager : public module::IUnknown
	{
		sf_uuid("01eefbeb-c80d-4434-b323-2d4dd2e95489")
	
		/// Initializes the script system
		virtual void Init(int argc = 0, wchar_t** argv = 0) = 0;

		/// Shuts down the script interpreter
		virtual void Shutdown() = 0;

		/// Exports all entries of module that have associated reflection
		virtual void ExportModule(const char* moduleName, const module::ModuleHandle& module) = 0;

		/// Exports user-defined type to script engine
		virtual void ExportType(const char* moduleName, reflection::user_type* type) = 0;

		/// Runs the specified script
		virtual void RunScript(const char* file) = 0;

		/// Exports object as global variable of specified module
		virtual bool ExportVariable(const char* moduleName, const char* varName, const reflection::value_type_pair& value) = 0;

		/// Searches and returns script value wrapper
		virtual bool FindEntry(const char* name, SScriptAny& outValue) = 0;

		/// Creates instance of specified type
		virtual bool CreateInstance(const char* type, SScriptAny& outInstance) = 0;
	};

} // namespace

#endif // _ISCRIPTMANAGER_H__