/*========================================================
* CScriptModule.h
* @author Sergey Mikhtonyuk
* @date 08 July 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _CSCRIPTMODULE_H__
#define _CSCRIPTMODULE_H__

#include <deque>
#include <unordered_map>
#include <Python.h>
#include "reflection/reflection_fwd.h"
#include "common/stringutils.h"
#include "EntryTypes.h"
#include "module/module.h"

namespace ScriptPy
{
    struct hash_typeptr
	{
		size_t operator()(const reflection::user_type* l) const
		{ return (size_t)l; }
	};

	/// Python module, acts like type registry
	/** @ingroup Py */
	class CScriptModule
	{
	public:

		/// Ctor
		CScriptModule(const char* name);

		/// Destructor
		~CScriptModule();

		/// Returns the name of the module
		const char* ModuleName() const;

		/// Exports specified type to module
		ExportEntry* ExportType(const reflection::user_type* type);

		/// Adds arbitrary module-global variable
		bool ExportVariable(const char* varName, PyObject* pyvalue);

		/// Finds the exported type by name
		/** Used in return type conversions, when
		 *  exported type is unknown.
		 *  @param typeName Fully-qualified type name */
		ExportEntry* FindExportedType(const char* typeName) const;

		/// Associates a module handle with script
		void SetModuleHandle(const module::ModuleHandle& module);

		/// Returns associated module handle (check IsLoaded before using)
		const module::ModuleHandle& GetModuleHandle() const;

	private:

		/// Used to create class object using reflected type
		ExportEntry* CreateClassObject(const reflection::user_type* type);

		/// Creates and initializes empty class with basic set of methods
		ExportEntry* CreateClass(const reflection::user_type* type, ExportEntry* base_class);

		/// Associates methods with the class object
		void AddMethods(const reflection::user_type* type, ExportEntry* entry);

		/// Creates method object
		void CreateMethod(const char* name, PyObject* dictionary, PyObject* self, PyCFunction handler, const char* docString = 0);

		/// Creates null-terminated array of attributes
		PyGetSetDef* CreateAttributes(const reflection::user_type* type);

	private:
		static void FillAttributeDesc(PyGetSetDef& def, const reflection::accessor_member* acc);

		typedef std::unordered_map<const reflection::user_type*, ExportEntry*, hash_typeptr> THintMap;
		typedef std::unordered_map<const char*, ExportEntry*, cstr_hash, cstrcmp_eq> TExportMap;

		module::ModuleHandle		mModuleHandle;
		std::deque<PyMethodDef>		mMethodDefStorage;
		std::vector<PyGetSetDef*>	mAttributeStorage;
		TExportMap					mEntries;
		THintMap					mHintMap;
		const char*					mName;

		PyObject*					mPyModule;
		PyObject*					mPyModuleDict;
		PyObject*					mPyModuleName;
	#ifdef PYTHON31
		PyModuleDef					mPyModuleDef;
	#endif
	};

} // namespace

#endif // _CSCRIPTMODULE_H__
