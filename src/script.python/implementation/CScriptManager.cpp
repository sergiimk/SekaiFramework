/*========================================================
* CScriptManager.cpp
* @author Sergey Mikhtonyuk
* @date 06 July 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "CScriptManager.h"
#include "CScriptModule.h"
#include "CScriptFunction.h"
#include "reflection/reflection.h"
#include "module/exception.h"

#include <vector>
#include <string>

#if !defined(PYTHON26) && !defined(PYTHON31)
#error "Python version is not specified"
#endif


namespace ScriptPy
{

	using namespace reflection;

	//////////////////////////////////////////////////////////////////////////

	CScriptManager* CScriptManager::sInstance;

	//////////////////////////////////////////////////////////////////////////

	CScriptManager::CScriptManager()
		: mMainModule(0)
	{
		sInstance = this;
	}

	//////////////////////////////////////////////////////////////////////////

	void CScriptManager::Init(int argc, wchar_t** wargv)
	{
		if(argc && wargv)
		{
	#ifdef PYTHON31
			Py_SetProgramName(wargv[0]);
	#elif defined(PYTHON26)
			char programName[255] = {0};
			wcstombs(programName, wargv[0], 255);
			Py_SetProgramName(programName);
	#endif
		}

		Py_Initialize();

		if(argc && wargv)
		{
	#ifdef PYTHON31
			PySys_SetArgv(argc, wargv);
	#elif defined(PYTHON26)
			// Will refactor later
			std::vector<std::string> argsCollection;
			std::vector<char*> argv;
			char buffer[255] = {0};
			for (int i = 0; i < argc; ++i)
			{
				wcstombs(buffer, wargv[i], 255);
				argsCollection.push_back( buffer );
				argv.push_back( const_cast<char*>( argsCollection.back().c_str() ) );
			}
			PySys_SetArgv(argc, &argv[0]);
	#endif

		}

		mMainModule = PyImport_AddModule("__main__");
	}

	//////////////////////////////////////////////////////////////////////////

	void CScriptManager::Shutdown()
	{
		Py_Finalize();

		TModuleMap::iterator it = mModules.begin();
		while(it != mModules.end())
		{
			// Some bug in python, it tries to access
			// modules after finalize
			mUnloaded.push_back(it->second);
			++it;
		}

		mModules.clear();
	}

	//////////////////////////////////////////////////////////////////////////

	CScriptManager::~CScriptManager()
	{
		for(size_t i = 0; i != mUnloaded.size(); ++i)
			delete mUnloaded[i];
	}

	//////////////////////////////////////////////////////////////////////////

	void CScriptManager::ExportModule(const char* moduleName, const module::ModuleHandle& module)
	{
		CScriptModule* scriptModule = FindOrCreateModule(moduleName);
		module::ModuleHandle::iterator end = module.MapEnd();
		for(module::ModuleHandle::iterator it = module.MapBegin();
			it != end;
			++it)
		{
			if(type* t = it.ReflectedType())
			{
				ASSERT_STRICT(t->arch_type() == ARCH_USERDEFINED);
				scriptModule->ExportType(static_cast<user_type*>(t));
			}
		}

		scriptModule->SetModuleHandle(module);
	}

	//////////////////////////////////////////////////////////////////////////

	void CScriptManager::ExportType(const char* moduleName, user_type *type)
	{
		CScriptModule* module = FindOrCreateModule(moduleName);
		module->ExportType(type);
	}

	//////////////////////////////////////////////////////////////////////////

	CScriptModule* CScriptManager::FindOrCreateModule(const char* moduleName)
	{
		TModuleMap::iterator it = mModules.find(moduleName);
		if(it != mModules.end())
			return it->second;

		CScriptModule* module = new CScriptModule(moduleName);
		bool unique = mModules.insert(std::make_pair(moduleName, module)).second;
		ASSERT_STRICT(unique);
		return module;
	}

	//////////////////////////////////////////////////////////////////////////

	void CScriptManager::RunScript(const char *file)
	{
	#ifdef PYTHON31
		PyObject* pyName = PyUnicode_FromString(file);
	#elif defined(PYTHON26)
		PyObject* pyName = PyString_FromString(file);
	#endif
		PyObject* pyScript = PyImport_Import(pyName);
		Py_DECREF(pyName);

		if(!pyScript)
		{
			PyErr_Print();
			throw module::RuntimeException("Module loading failed");
		}

		PyModule_AddObject(mMainModule, file, pyScript);
		//Py_DECREF(pyScript);
	}

	//////////////////////////////////////////////////////////////////////////

	bool CScriptManager::FindEntry(const char* name, SScriptAny& outValue)
	{
		outValue.clear();

		if(!name)
			return false;

		PyObject* obj = FindScriptObject(name);
		bool res = MakeAny(obj, outValue);

		Py_XDECREF(obj);
		return res;
	}

	//////////////////////////////////////////////////////////////////////////

	bool CScriptManager::ExportVariable(const char* moduleName, const char* varName, const reflection::value_type_pair& value)
	{
		PyObject* pyvalue = ConvertToObject(value);

		CScriptModule* module = FindOrCreateModule(moduleName);

		return module && pyvalue
			? module->ExportVariable(varName, pyvalue)
			: false;
	}

	//////////////////////////////////////////////////////////////////////////

	bool CScriptManager::CreateInstance(const char* typeName, SScriptAny& outInstance)
	{
		if(!typeName)
			return false;

		// Find type object
		PyObject* type = FindScriptObject(typeName);
		if(!type || !PyType_Check(type))
		{
			Py_XDECREF(type);
			return false;
		}

		// Create instance
		PyObject* args = PyTuple_New(0);
		PyObject* inst = PyObject_CallObject(type, args);
		Py_DECREF(args);
		Py_DECREF(type);

		if(!inst)
			return false;

		bool ret = MakeAny(inst, outInstance);
		Py_DECREF(inst);

		return ret;
	}

	//////////////////////////////////////////////////////////////////////////

	void CScriptManager::InvokeCallable(PyObject* callable, value_type_pair* args, size_t nargs, value_type_pair* ret)
	{
		// Create arguments
		PyObject* py_args = PyTuple_New(nargs);

		for(size_t i = 0; i != nargs; ++i)
		{
			PyObject *arg = ConvertToObject(args[i]);

			/// \todo error handling
			PyTuple_SET_ITEM(py_args, i, arg);
		}

		// Call
		PyObject *py_ret = PyObject_CallObject(callable, py_args);
		PyErr_Print();

		// Handle return value
		if(ret)
			ConvertObject(py_ret, *ret);

		Py_DECREF(py_ret);
		Py_DECREF(py_args);
	}

	//////////////////////////////////////////////////////////////////////////

	ExportEntry* CScriptManager::FindExportedType(const char* name, CScriptModule* moduleHint)
	{
		ExportEntry* typeEntry = 0;
		if(moduleHint)
		{
			typeEntry = moduleHint->FindExportedType(name);
		}
		else
		{
			TModuleMap::const_iterator it = mModules.begin();
			while(it != mModules.end())
			{
				if(it->second != moduleHint)
				{
					typeEntry = it->second->FindExportedType(name);
					if(typeEntry)
						break;
				}
			}
		}
		return typeEntry;
	}

	//////////////////////////////////////////////////////////////////////////

	PyObject* CScriptManager::FindScriptObject(const char *name)
	{
		char name_buf[100];

		int first = 0;
		int last = 0;
		PyObject *obj = mMainModule;
		Py_INCREF(obj);

		while(true)
		{
			// Iterate to find position of "." or end of string
			for(; name[last] != '.' && name[last] != '\0'; ++last);

			assert(last - first < 100);
			memcpy(name_buf, &name[first], last - first);
			name_buf[last-first] = '\0';

			PyObject *t = obj;
			obj = PyObject_GetAttrString(t, name_buf);
			Py_DECREF(t);

			if(!obj || name[last] == '\0')
				break;

			first = ++last;
		}

		return obj;
	}

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	method_member* CScriptManager::ExtractMethodInfo(PyObject* methodSelf)
	{
		ASSERT_STRICT(PyLong_Check(methodSelf));
		return reinterpret_cast<method_member*>(PyLong_AsSsize_t(methodSelf));
	}

	//////////////////////////////////////////////////////////////////////////

	InstanceObject* CScriptManager::ExtractInstanceInfo(PyObject* inst)
	{
		return (InstanceObject*)inst;
	}

	//////////////////////////////////////////////////////////////////////////

	ExportEntry* CScriptManager::ExtractTypeInfo(PyObject* type)
	{
		ExportEntry* ret = (ExportEntry*)((char*)type - offsetof(ExportEntry, ClassObj));
		return ret->_header == _EntHeader ? ret : 0;
	}

	//////////////////////////////////////////////////////////////////////////

	ExportEntry* CScriptManager::FindExportedBase(PyTypeObject *type)
	{
		ExportEntry* e = ExtractTypeInfo((PyObject*)type);
		if(!e && type->tp_base)
			e = FindExportedBase(type->tp_base);

		return e;
	}

	//////////////////////////////////////////////////////////////////////////

	void* CScriptManager::PrepareInstancePointer(InstanceObject* inst_info, const user_type* ownerType)
	{
		size_t offset = user_type::calculate_offset(*inst_info->object_type->Type, *ownerType);
		return adjustptr(inst_info->instance, offset);
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace
