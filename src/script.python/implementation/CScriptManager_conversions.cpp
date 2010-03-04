/*========================================================
* CScriptManager_conversions.cpp
* @author Sergey Mikhtonyuk
* @date 06 July 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "CScriptManager.h"
#include "reflection/reflection.h"
#include "CScriptModule.h"
#include "CScriptFunction.h"
#include "CScriptTable.h"
#include "CScriptObject.h"

#ifdef PYTHON31
	#define PYINTEGER_FROMLONG(v) 	PyLong_FromLong(v)
	#define PYINTEGER_FROMSIZE_T(v) PyLong_FromSize_t(v)
	#define PYINTEGER_CHECK(v)		PyLong_Check(v)
	#define PYINTEGER_ASLONG(v)		PyLong_AsLong(v)
#elif defined(PYTHON26)
	#define PYINTEGER_FROMLONG(v) PyInt_FromLong(v)
	#define PYINTEGER_FROMSIZE_T(v) PyInt_FromLong(v)
	#define PYINTEGER_CHECK(v)		PyInt_Check(v)
	#define PYINTEGER_ASLONG(v)		PyInt_AsLong(v)
#endif



namespace ScriptPy
{
	using namespace Reflection;

	//////////////////////////////////////////////////////////////////////////

	bool CScriptManager::MakeAny(PyObject* obj, SScriptAny& val)
	{
		val.clear();

		if(!obj)
			return false;

		if(PYINTEGER_CHECK(obj))
			val = SScriptAny((int) PYINTEGER_ASLONG(obj));
		else if(PyFloat_Check(obj))
			val = SScriptAny((float) PyFloat_AsDouble(obj));
		else if(PyDict_Check(obj))
		{
			CScriptTable* tbl;
			create_instance_impl(&tbl);

			tbl->FinalConstruct(obj);
			val = SScriptAny(tbl);

			tbl->Release();
		}
		else if(PyCallable_Check(obj))
		{
			CScriptFunction* pFunc;
			create_instance_impl(&pFunc);

			pFunc->FinalConstruct(obj);
			val = SScriptAny(pFunc);

			pFunc->Release();
		}
		else
		{
			CScriptObject* pObj;
			create_instance_impl(&pObj);

			pObj->FinalConstruct(obj);
			val = SScriptAny(pObj);

			pObj->Release();
		}

		return true;
	}

	//////////////////////////////////////////////////////////////////////////

	bool CScriptManager::IsBuiltIn(const Reflection::Type* t)
	{
		return	(t->ArchType() == RL_ARCH_BUILTIN ||
				(t->ArchType() == RL_ARCH_POINTER &&
				static_cast<const PointerType*>(t)->getPointedType()->Tag() == RL_T_CHAR));
	}

	bool CScriptManager::IsUserDefined(const Reflection::Type* t)
	{
		return t->ArchType() == RL_ARCH_USERDEFINED;
	}

	bool CScriptManager::IsPointerToBuiltin(const Reflection::Type* t)
	{
		return t->ArchType() == RL_ARCH_POINTER && static_cast<const PointerType*>(t)->getPointedType()->ArchType() == RL_ARCH_BUILTIN;
	}

	bool CScriptManager::IsPointerToUserDefined(const Reflection::Type* t)
	{
		return t->ArchType() == RL_ARCH_POINTER && static_cast<const PointerType*>(t)->getPointedType()->ArchType() == RL_ARCH_USERDEFINED;
	}

	//////////////////////////////////////////////////////////////////////////

	PyObject* CScriptManager::CreateBuiltinScriptObject(Reflection::ETypeTag type, void* pVal)
	{
		PyObject* ret = 0;
		switch(type)
		{
		case RL_T_BOOL:
			ret = PYINTEGER_FROMSIZE_T(*(bool*)pVal ? 1 : 0);
			break;
		case RL_T_INT:
			ret = PYINTEGER_FROMLONG(*(int*)pVal);
			break;
		case RL_T_UINT:
			ret = PYINTEGER_FROMLONG(*(unsigned int*)pVal);
			break;
		case RL_T_LONG:
			ret = PYINTEGER_FROMLONG(*(long*)pVal);
			break;
		case RL_T_ULONG:
			ret = PYINTEGER_FROMLONG(*(unsigned long*)pVal);
			break;
		case RL_T_FLOAT:
			ret = PyFloat_FromDouble(*(float*)pVal);
			break;
		case RL_T_DOUBLE:
			ret = PyFloat_FromDouble(*(double*)pVal);
			break;
		case RL_T_POINTER:
			// Strings
		#ifdef PYTHON31
			ret = PyUnicode_FromString(*(char**)pVal);
		#elif defined(PYTHON26)
			ret = PyString_FromString(*(char**)pVal);
		#endif
			break;
		}
		return ret;
	}

	//////////////////////////////////////////////////////////////////////////

	bool CScriptManager::ConvertToBuiltinValue(Reflection::ETypeTag type, void* pValOut, PyObject* v)
	{
		switch(type)
		{
		case RL_T_BOOL:
			if(!PYINTEGER_CHECK(v)) return false;
			*(bool*)pValOut = PYINTEGER_ASLONG(v) ? true : false;
			return true;
		case RL_T_INT:
			if(!PYINTEGER_CHECK(v)) return false;
			*(int*)pValOut = PYINTEGER_ASLONG(v);
			return true;
		case RL_T_UINT:
			if(!PYINTEGER_CHECK(v)) return false;
			*(unsigned int*)pValOut = PYINTEGER_ASLONG(v);
			return true;
		case RL_T_LONG:
			if(!PYINTEGER_CHECK(v)) return false;
			*(long*)pValOut = PYINTEGER_ASLONG(v);
			return true;
		case RL_T_ULONG:
			if(!PYINTEGER_CHECK(v)) return false;
			*(unsigned long*)pValOut = PYINTEGER_ASLONG(v);
			return true;
		case RL_T_FLOAT:
			if(PyFloat_Check(v)) {
				*(float*)pValOut = (float)PyFloat_AS_DOUBLE(v);
				return true;
			}
			else if(PyIndex_Check(v)) {
				*(float*)pValOut = (float)PYINTEGER_ASLONG(v);
				return true;
			}
			return false;
		case RL_T_DOUBLE:
			if(PyFloat_Check(v)) {
				*(double*)pValOut = PyFloat_AS_DOUBLE(v);
				return true;
			}
			else if(PYINTEGER_CHECK(v)) {
				*(double*)pValOut = PYINTEGER_ASLONG(v);
				return true;
			}
		case RL_T_POINTER:
			// Strings
			/*if(!PyUnicode_Check(v)) return false;
			*(char**)pValOut = (char*)PyUnicode_AS_DATA(v);
			return true;*/
		#ifdef PYTHON31
			NOT_IMPLEMENTED();
		#elif defined(PYTHON26)
			if(!PyString_Check(v)) return false;
			*(char**)pValOut = PyString_AsString(v);
			return true;
		#endif

		}
		return false;
	}

	//////////////////////////////////////////////////////////////////////////

	PyObject* CScriptManager::CreateUserDefScriptObject(const Reflection::Type* type, void* pVal, CScriptModule* moduleHint, InstanceType inst_t)
	{
		// Print the type name
		char buf[_EntNameBufLen];
		type->FullName(buf, _EntNameBufLen);

		// Find exported type by name, use the hint first
		ExportEntry* typeEntry = FindExportedType(buf, moduleHint);
		PyTypeObject *typeObj = &typeEntry->ClassObj;

		if(!typeEntry)
			return 0;

		// Create instance object (same as __new__)
		InstanceObject* inst_info = (InstanceObject*)typeObj->tp_alloc(typeObj, 0);
		inst_info->instance = pVal;
		inst_info->ctor = 0;
		inst_info->inst_type = inst_t;
		inst_info->object_type = typeEntry;
		return (PyObject*)inst_info;
	}

	//////////////////////////////////////////////////////////////////////////

	bool CScriptManager::ConvertObject(PyObject* v, ValueTypePair& ret)
	{
		const Type *dataType = ret.pType;
		ASSERT_STRICT(ret.pType);

		if(IsBuiltIn(dataType))
		{
			ConvertToBuiltinValue(dataType->Tag(), ret.pValue, v);
			return true;
		}
		else if(IsUserDefined(dataType))
		{
			*(void**)ret.pValue = ExtractInstanceInfo(v)->instance;
			return true;
		}
		else if(IsPointerToBuiltin(dataType))
		{
			assert(false);
			return false;
		}
		else if(IsPointerToUserDefined(dataType))
		{
			*(void**)ret.pValue = &ExtractInstanceInfo(v)->instance;
			return true;
		}

		return false;
	}

	//////////////////////////////////////////////////////////////////////////\

	PyObject* CScriptManager::ConvertToObject(const ValueTypePair& v)
	{
		const Type *dataType = v.pType;

		if(IsBuiltIn(dataType))
		{
			return CreateBuiltinScriptObject(dataType->Tag(), v.pValue);
		}
		else if(IsUserDefined(dataType))
		{
			return CreateUserDefScriptObject(dataType, v.pValue, 0, SIT_OWNED);
		}
		else if(IsPointerToBuiltin(dataType))
		{
			assert(false);
			return 0;
		}
		else if(IsPointerToUserDefined(dataType))
		{
			return CreateUserDefScriptObject(
				static_cast<const PointerType*>(dataType)->getPointedType(),
				*(void**)v.pValue,
				0,
				SIT_SHARED);
		}
		// Unreachable
		assert(false);
		return 0;
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace
