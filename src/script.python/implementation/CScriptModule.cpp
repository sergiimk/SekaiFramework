/*========================================================
* CScriptModule.cpp
* @author Sergey Mikhtonyuk
* @date 08 July 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "CScriptModule.h"
#include "CScriptManager.h"
#include "reflection/reflection.h"

#if !defined(PYTHON26) && !defined(PYTHON31)
#error "Python version is not specified"
#endif

namespace ScriptPy
{
	using namespace Reflection;

	//////////////////////////////////////////////////////////////////////////

	CScriptModule::CScriptModule(const char *name)
		: mName(name)
	{
	#ifdef PYTHON31
		// Fill module defs
		PyModuleDef moduledef = { PyModuleDef_HEAD_INIT, name, 0, -1, 0, 0, 0, 0, 0 };
		mPyModuleDef = moduledef;

		// Init underlying Py module
		mPyModule = PyModule_Create(&mPyModuleDef);
		PyDict_SetItemString(PyImport_GetModuleDict(), name, mPyModule);
		mPyModuleDict = PyModule_GetDict(mPyModule);
		mPyModuleName = PyUnicode_FromString(name);
	#elif defined(PYTHON26)
		mPyModule = Py_InitModule(name, 0);
		mPyModuleDict = PyModule_GetDict(mPyModule);
		mPyModuleName = PyString_FromString(name);
	#endif
	}

	//////////////////////////////////////////////////////////////////////////

	CScriptModule::~CScriptModule()
	{
		TExportMap::iterator it = mEntries.begin();
		while(it != mEntries.end())
		{
			delete it->second;
			++it;
		}

		for(size_t i = 0; i != mAttributeStorage.size(); ++i)
		{
			delete[] mAttributeStorage[i];
		}

		Py_DECREF(mPyModuleName);
	}

	//////////////////////////////////////////////////////////////////////////

	void CScriptModule::SetModuleHandle(const Module::ModuleHandle &module)
	{
		mModuleHandle = module;
	}

	//////////////////////////////////////////////////////////////////////////

	const Module::ModuleHandle& CScriptModule::GetModuleHandle() const
	{
		return mModuleHandle;
	}

	//////////////////////////////////////////////////////////////////////////

	const char* CScriptModule::ModuleName() const
	{
		return mName;
	}

	//////////////////////////////////////////////////////////////////////////

	ExportEntry* CScriptModule::ExportType(Reflection::UserType *type)
	{
		if(RL_T_ENUM != type->Tag())
		{
			ExportEntry* ent = CreateClassObject(type);

			if(ent)
			{
				int res = PyModule_AddObject(mPyModule, ent->Name, (PyObject*)&ent->ClassObj);
				ASSERT_STRICT(res == 0);
			}
			return ent;
		}
		else
		{
			EnumerationDescriptor* enumDesc =
				static_cast<EnumerationDescriptor*>(
				type->FindService(RL_DESC_SERVICE_ENUMERATION));

			if(!enumDesc)
				return 0;

			size_t num = enumDesc->NumEntries();

			for(size_t i = 0; i != num; ++i)
			{
				int ret = PyModule_AddIntConstant(mPyModule, enumDesc->getName(i), (long)enumDesc->getValue(i));
				ASSERT_STRICT(ret == 0);
			}

			return 0;
		}
	}

	//////////////////////////////////////////////////////////////////////////

	ExportEntry* CScriptModule::FindExportedType(const char* typeName) const
	{
		TExportMap::const_iterator it = mEntries.find(typeName);
		return it == mEntries.end() ? 0 : it->second;
	}

	//////////////////////////////////////////////////////////////////////////

	ExportEntry* CScriptModule::CreateClassObject(UserType *type)
	{
		ExportEntry* base_class = 0;

		// GetFirst base class
		assert(type->getBaseTypeNumber() <= 1);
		if(type->getBaseTypeNumber())
		{
			UserType* base = type->getBaseTypeDescriptor(0)->getBaseType();

			// Check if exist (using hint for in-module lookup)
			THintMap::const_iterator it = mHintMap.find(base);
			if(it == mHintMap.end())
				base_class = ExportType(base);
			else
				base_class = it->second;
		}

		ExportEntry* ent = CreateClass(type, base_class);

		AddMethods(type, ent);

		return ent;
	}

	//////////////////////////////////////////////////////////////////////////

	ExportEntry* CScriptModule::CreateClass(UserType* type, ExportEntry* base_class)
	{
		ExportEntry* ent = new ExportEntry;
		type->Name(ent->Name, _EntNameBufLen);
		type->FullName(ent->FullName, _EntNameBufLen);
		ent->Type = type;
		ent->Module = this;
		ent->BaseType = base_class;

		ent->ClassObj.tp_name		= ent->Name;
		ent->ClassObj.tp_basicsize	= sizeof(InstanceObject);
		ent->ClassObj.tp_dictoffset	= offsetof(InstanceObject, inst_dictionary);
		ent->ClassObj.tp_flags		= Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE;
		ent->ClassObj.tp_new		= &CScriptManager::callback_new;
		ent->ClassObj.tp_init		= &CScriptManager::callback_init;
		ent->ClassObj.tp_dealloc	= &CScriptManager::callback_dealloc;
		ent->ClassObj.tp_base		= base_class ? &base_class->ClassObj : 0;
		ent->ClassObj.tp_getattro	= &PyObject_GenericGetAttr;
		ent->ClassObj.tp_setattro	= &PyObject_GenericSetAttr;
		ent->ClassObj.tp_getset		= CreateAttributes(type);
		ent->ClassObj.tp_str		= &CScriptManager::callback_tostring;
		ent->ClassObj.tp_richcompare= &CScriptManager::callback_richcompare;
		ent->ClassObj.tp_hash		= &CScriptManager::callback_hash;

		Py_INCREF(&ent->ClassObj);

		// Ready the type
		if (PyType_Ready(&ent->ClassObj) < 0)
		{
			delete ent;
			return 0;
		}

		mEntries.insert(std::make_pair(ent->FullName, ent));
		mHintMap.insert(std::make_pair(ent->Type, ent));

		return ent;
	}

	//////////////////////////////////////////////////////////////////////////

	void CScriptModule::AddMethods(UserType* type, ExportEntry* entry)
	{
		const size_t nMethods = type->getMethodNumber();

		for(size_t m = 0; m != nMethods; ++m)
		{
			Reflection::MethodDescriptor* method = type->getMethodDescriptor(m);
			PyObject* self = PyLong_FromSize_t(reinterpret_cast<size_t>(method));

			CreateMethod(method->getName(), entry->ClassObj.tp_dict, self, CScriptManager::callback_invoke, method->getDocString());

			Py_DECREF(self);
		}
	}

	//////////////////////////////////////////////////////////////////////////

	void CScriptModule::CreateMethod( const char* name,
									  PyObject* dictionary,
									  PyObject* self,
									  PyCFunction handler,
									  const char* docString /*= 0*/ )
	{
		PyMethodDef def = { name, handler, METH_VARARGS, docString };
		mMethodDefStorage.push_back(def);

		PyObject *func = PyCFunction_New(&mMethodDefStorage.back(), self);
	#ifdef PYTHON31
		PyObject *method = PyInstanceMethod_New(func);
	#elif defined(PYTHON26)
		PyObject *method = PyMethod_New(func, 0, 0);
	#endif
		PyDict_SetItemString(dictionary, name, method);

		Py_DECREF(func);
		Py_DECREF(method);
	}

	//////////////////////////////////////////////////////////////////////////

	PyGetSetDef* CScriptModule::CreateAttributes(UserType* type)
	{
		const size_t nFields = type->getFieldNumber();
		const size_t nAcc = type->getAccessorNumber();

		if(0 == nFields + nAcc)
			return 0;

		PyGetSetDef* attrs = new PyGetSetDef[nFields + nAcc + 1];
		memset(&attrs[nFields + nAcc], 0, sizeof(PyGetSetDef));

		mAttributeStorage.push_back(attrs);

		for(size_t f = 0; f != nFields; ++f)
			FillAttributeDesc(attrs[f], type->getFieldDescriptor(f));

		for(size_t a = 0; a != nAcc; ++a)
			FillAttributeDesc(attrs[nFields + a], type->getAccessorDescriptor(a));

		return attrs;
	}

	//////////////////////////////////////////////////////////////////////////

	void CScriptModule::FillAttributeDesc(PyGetSetDef& def, DataDescriptor* data)
	{
		def.name = (char*)data->getName();
		def.doc = (char*)data->getDocString();
		def.get = &CScriptManager::callback_attribute_get;
		def.set = &CScriptManager::callback_attribute_set;
		def.closure = data;
	}

	//////////////////////////////////////////////////////////////////////////

	bool CScriptModule::ExportVariable(const char* varName, PyObject* pyvalue)
	{
		int ret = PyModule_AddObject(mPyModule, varName, pyvalue);
		ASSERT_STRICT(ret != -1);
		return ret == 0;
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace
