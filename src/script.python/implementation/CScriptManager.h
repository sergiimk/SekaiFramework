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
#include <Python.h>
#include "platform/hash_map.h"
#include "EntryTypes.h"

using namespace Script;

namespace ScriptPy
{
	struct SInvokeArgs;

	/// Implementation of script manager for Python binding
	/** @ingroup Py */
	class NOVTABLE CScriptManager :
		public Module::ComRootObject<>,
		public IScriptManager
	{
	public:

		DECLARE_IMPLEMENTATION2(CScriptManager, Module::ComClassFactorySingleton)

		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(IScriptManager)
		END_INTERFACE_MAP()

		CScriptManager();
		~CScriptManager();

		void Init(int argc, wchar_t** argv);

		void Shutdown();

		void ExportModule(const char* moduleName, const Module::ModuleHandle& module);

		void ExportType(const char* moduleName, Reflection::UserType* type);

		void RunScript(const char* file);

		bool FindEntry(const char* name, SScriptAny& outValue);

		virtual bool ExportVariable(const char* moduleName, const char* varName, const Reflection::ValueTypePair& value);

		virtual bool CreateInstance(const char* type, SScriptAny& outInstance);

		//////////////////////////////////////////////////////////////////////////

		void InvokeCallable(PyObject* callable, Reflection::ValueTypePair* args, size_t nargs, Reflection::ValueTypePair* ret);

		static bool PackFunctionArguments(Reflection::Type* types[], size_t ntypes, SInvokeArgs& args, PyObject* pyargs, size_t startIndex);

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

		PyObject* CreateBuiltinScriptObject(Reflection::ETypeTag type, void* pVal);

		PyObject* CreateUserDefScriptObject(const Reflection::Type* type, void* pVal, CScriptModule* moduleHint, InstanceType inst_t);

		//////////////////////////////////////////////////////////////////////////

		bool MakeAny(PyObject* obj, SScriptAny& val);

		bool ConvertToBuiltinValue(Reflection::ETypeTag type, void* pValOut, PyObject* v);

		bool ConvertObject(PyObject* v, Reflection::ValueTypePair& ret);

		PyObject* ConvertToObject(const Reflection::ValueTypePair& v);

		//////////////////////////////////////////////////////////////////////////

		static Reflection::MethodDescriptor* ExtractMethodInfo(PyObject* methodSelf);

		static InstanceObject* ExtractInstanceInfo(PyObject* inst);

		static ExportEntry* ExtractTypeInfo(PyObject* type);

		static ExportEntry* FindExportedBase(PyTypeObject* type);

		static void* PrepareInstancePointer(InstanceObject* inst_info, Reflection::UserType* ownerType);

		//////////////////////////////////////////////////////////////////////////

		static bool IsBuiltIn(const Reflection::Type* t);

		static bool IsUserDefined(const Reflection::Type* t);

		static bool IsPointerToBuiltin(const Reflection::Type* t);

		static bool IsPointerToUserDefined(const Reflection::Type* t);

		//////////////////////////////////////////////////////////////////////////

	private:

		CScriptModule* FindOrCreateModule(const char* moduleName);

		typedef std::hash_map<const char*, CScriptModule*, cstr_hash, cstrcmp_eq> TModuleMap;
		TModuleMap					mModules;
		std::vector<CScriptModule*>	mUnloaded;
		PyObject*					mMainModule;

	public:

		static CScriptManager*	sInstance;
	};

	inline bool script_cast(PyObject* v, Reflection::ValueTypePair& ret)
	{
		return CScriptManager::sInstance->ConvertObject(v, ret);
	}

	inline PyObject* script_cast(const Reflection::ValueTypePair& v)
	{
		return CScriptManager::sInstance->ConvertToObject(v);
	}

} // namespace

#endif // _CSCRIPTMANAGER_H__
