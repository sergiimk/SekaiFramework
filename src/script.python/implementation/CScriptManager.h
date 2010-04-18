/*========================================================
* CScriptManager.h
* @author Sergey Mikhtonyuk
* @date 06 July 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _CSCRIPTMANAGER_H__
#define _CSCRIPTMANAGER_H__

#include "IScriptManager.h"
#include "IScriptFunction.h"
#include "SScriptAny.h"
#include "module/implementations.h"
#include "reflection/reflection_fwd.h"
#include "reflection/types/Type.h"
#include "common/stringutils.h"
#include <vector>
#include <unordered_map>
#include <Python.h>
#include "EntryTypes.h"

using namespace Script;

namespace ScriptPy
{
	struct SInvokeArgs;

	/// Implementation of script manager for Python binding
	/** @ingroup Py */
	class NOVTABLE CScriptManager :
		public module::ComRootObject<>,
		public IScriptManager
	{
	public:

		DECLARE_IMPLEMENTATION2(CScriptManager, module::ComClassFactorySingleton)

		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(IScriptManager)
		END_INTERFACE_MAP()

		CScriptManager();
		~CScriptManager();

		void Init(int argc, wchar_t** argv);

		void Shutdown();

		void ExportModule(const char* moduleName, const module::ModuleHandle& module);

		void ExportType(const char* moduleName, reflection::user_type* type);

		void RunScript(const char* file);

		bool FindEntry(const char* name, SScriptAny& outValue);

		virtual bool ExportVariable(const char* moduleName, const char* varName, const reflection::value_type_pair& value);

		virtual bool CreateInstance(const char* type, SScriptAny& outInstance);

		//////////////////////////////////////////////////////////////////////////

		void InvokeCallable(PyObject* callable, reflection::value_type_pair* args, size_t nargs, reflection::value_type_pair* ret);

		static bool PackFunctionArguments(reflection::type* types[], size_t ntypes, SInvokeArgs& args, PyObject* pyargs, size_t startIndex);

		static PyObject* callback_invoke(PyObject* self, PyObject* args);

		static PyObject* callback_attribute_get(PyObject* self, void* closure);

		static int callback_attribute_set(PyObject* self, PyObject* value, void* closure);

		static PyObject* callback_new(PyTypeObject *type, PyObject *args, PyObject *kwds);

		static int callback_init(PyObject* self, PyObject *args, PyObject *kwds);

		static void callback_dealloc(PyObject* self);

		static PyObject* callback_tostring(PyObject* self);

		static PyObject* callback_richcompare(PyObject *self, PyObject *other, int op);

		static long callback_hash(PyObject *self);

		//////////////////////////////////////////////////////////////////////////

		ExportEntry* FindExportedType(const char* name, CScriptModule* moduleHint);

		PyObject* FindScriptObject(const char* name);

		//////////////////////////////////////////////////////////////////////////

		PyObject* CreateBuiltinScriptObject(reflection::ETypeTag type, void* pVal);

		PyObject* CreateUserDefScriptObject(const reflection::type* type, void* pVal, CScriptModule* moduleHint, InstanceType inst_t);

		//////////////////////////////////////////////////////////////////////////

		bool MakeAny(PyObject* obj, SScriptAny& val);

		bool ConvertToBuiltinValue(reflection::ETypeTag type, void* pValOut, PyObject* v);

		bool ConvertObject(PyObject* v, reflection::value_type_pair& ret);

		PyObject* ConvertToObject(const reflection::value_type_pair& v);

		//////////////////////////////////////////////////////////////////////////

		static reflection::method_member* ExtractMethodInfo(PyObject* methodSelf);

		static InstanceObject* ExtractInstanceInfo(PyObject* inst);

		static ExportEntry* ExtractTypeInfo(PyObject* type);

		static ExportEntry* FindExportedBase(PyTypeObject* type);

		static void* PrepareInstancePointer(InstanceObject* inst_info, const reflection::user_type* ownerType);

		//////////////////////////////////////////////////////////////////////////

		static bool IsBuiltIn(const reflection::type* t);

		static bool IsUserDefined(const reflection::type* t);

		static bool IsPointerToBuiltin(const reflection::type* t);

		static bool IsPointerToUserDefined(const reflection::type* t);

		//////////////////////////////////////////////////////////////////////////

	private:

		CScriptModule* FindOrCreateModule(const char* moduleName);

		typedef std::unordered_map<const char*, CScriptModule*, cstr_hash, cstrcmp_eq> TModuleMap;
		TModuleMap					mModules;
		std::vector<CScriptModule*>	mUnloaded;
		PyObject*					mMainModule;

	public:

		static CScriptManager*	sInstance;
	};

	inline bool script_cast(PyObject* v, reflection::value_type_pair& ret)
	{
		return CScriptManager::sInstance->ConvertObject(v, ret);
	}

	inline PyObject* script_cast(const reflection::value_type_pair& v)
	{
		return CScriptManager::sInstance->ConvertToObject(v);
	}

} // namespace

#endif // _CSCRIPTMANAGER_H__
