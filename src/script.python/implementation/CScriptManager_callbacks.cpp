/*========================================================
* CScriptManager_callbacks.cpp
* @author Sergey Mikhtonyuk
* @date 06 July 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "CScriptManager.h"
#include "reflection/reflection.h"

#if !defined(PYTHON26) && !defined(PYTHON31)
#error "Python version is not specified"
#endif

namespace ScriptPy
{
	//////////////////////////////////////////////////////////////////////////
	using namespace Reflection;
	//////////////////////////////////////////////////////////////////////////

	struct SInvokeArgs
	{
		void* values[DELEG_MAX_INVOKE_PARAMS];
		Type* types[DELEG_MAX_INVOKE_PARAMS];
		char builtin_buf[DELEG_MAX_INVOKE_PARAMS * sizeof(long long)];

		void clear()
		{
			memset(values, 0, sizeof(void*) * DELEG_MAX_INVOKE_PARAMS);
			memset(types, 0, sizeof(void*) * DELEG_MAX_INVOKE_PARAMS);
			memset(builtin_buf, 0, DELEG_MAX_INVOKE_PARAMS * sizeof(long long));
		}
	};

	//////////////////////////////////////////////////////////////////////////

	bool CScriptManager::PackFunctionArguments(Type* types[], size_t ntypes, SInvokeArgs& args, PyObject* pyargs, size_t startIndex)
	{
		for(size_t i = startIndex; i != ntypes; ++i)
		{
			PyObject* arg_i = PyTuple_GetItem(pyargs, i);
			args.types[i] = types[i];

			if(IsBuiltIn(args.types[i]))
			{
				if(!sInstance->ConvertToBuiltinValue(args.types[i]->Tag(), &args.builtin_buf[i * sizeof(long long)], arg_i))
					return false;

				args.values[i] = &args.builtin_buf[i * sizeof(long long)];
			}
			else if(IsUserDefined(args.types[i]))
			{
				args.values[i] = ExtractInstanceInfo(arg_i)->instance;
			}
			else if(IsPointerToBuiltin(args.types[i]))
			{
				NOT_IMPLEMENTED();
			}
			else if(IsPointerToUserDefined(args.types[i]))
			{
				args.values[i] = &ExtractInstanceInfo(arg_i)->instance;
			}
		}
		return true;
	}


	PyObject* CScriptManager::callback_invoke(PyObject *self, PyObject *args)
	{
		MethodDescriptor* method = ExtractMethodInfo(self);
		FunctionType* method_t = method->getType();
		const size_t numArgs = method_t->getArgumentNumber();

		// Validate params
		if(PyTuple_Size(args) != numArgs)
		{
			PyErr_SetString(PyExc_TypeError, "Invalid number of arguments");
			return 0;
		}

		InstanceObject* instance_info = ExtractInstanceInfo(PyTuple_GetItem(args, 0));
		ExportEntry* export_entry = instance_info->object_type;

		//////////////////////////////////////////////////////////////////////////

		if(!instance_info->instance)
		{
			PyErr_SetString(PyExc_RuntimeError, "Invoking method on not initialized object");
			return 0;
		}

		// Prepare parameters ////////////////////////////////////////////////////
		SInvokeArgs inv_args;
		inv_args.clear();

		// Instance
		void* class_instance = PrepareInstancePointer(instance_info, method->getOwnerClass());
		inv_args.values[0] = &class_instance;

		// Create args
		if(!PackFunctionArguments(method_t->getArgumentTypes(), numArgs, inv_args, args, 1))
		{
			PyErr_SetString(PyExc_TypeError, "Invalid arguments");
			return 0;
		}

		// Return value //////////////////////////////////////////////////////////
		void* retval = 0;
		Type* retval_t = method->getType()->getReturnType();
		char builtin_buf[8] = { 0 };
		if(retval_t->Tag() == RL_T_VOID)
		{
		}
		else if(IsBuiltIn(retval_t))
		{
			retval = builtin_buf;
		}
		else if(IsUserDefined(retval_t))
		{
			retval = retval_t->CreateInstance();
			ASSERT_STRICT(retval);
		}
		else if(IsPointerToBuiltin(retval_t))
		{
			NOT_IMPLEMENTED();
		}
		else if(IsPointerToUserDefined(retval_t))
		{
			retval = builtin_buf;
		}


		// Make call /////////////////////////////////////////////////////////////
		method->Invoke(inv_args.values, retval);
		//////////////////////////////////////////////////////////////////////////


		// Convert ret val ///////////////////////////////////////////////////////
		if(retval) {
			PyObject* pyRet = 0;

			if(IsBuiltIn(retval_t)) {
				pyRet = sInstance->CreateBuiltinScriptObject(retval_t->Tag(), retval);
			}
			else if(IsUserDefined(retval_t)) {
				pyRet = sInstance->CreateUserDefScriptObject(retval_t, retval, export_entry->Module, SIT_OWNED);
			}
			else if(IsPointerToBuiltin(retval_t)) {
				NOT_IMPLEMENTED();
			}
			else if(IsPointerToUserDefined(retval_t))
			{
				pyRet = sInstance->CreateUserDefScriptObject(static_cast<PointerType*>(retval_t)->getPointedType(),
					*(void**)builtin_buf, export_entry->Module, SIT_SHARED);
			}

			if(!pyRet)
				PyErr_SetString(PyExc_RuntimeError, "Failed to marshal the return value");
			return pyRet;
		}

		Py_INCREF(Py_None);
		return Py_None;
	}


	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	PyObject* CScriptManager::callback_attribute_get(PyObject *self, void *closure)
	{
		PyObject* retVal = 0;

		// Get class type
		InstanceObject *instance_info = ExtractInstanceInfo(self);
		ExportEntry *export_entry = instance_info->object_type;

		if(!instance_info->instance)
		{
			PyErr_SetString(PyExc_RuntimeError, "Invoking method on not initialized object");
			return 0;
		}

		ASSERT_STRICT(closure);
		DataDescriptor* data = static_cast<DataDescriptor*>(closure);
		Type* dataType = data->getType();

		void* class_instance = PrepareInstancePointer(instance_info, data->getOwnerClass());

		if(IsBuiltIn(dataType))
		{
			char buffer[8] = { 0 }; // Buffer for return value
			data->getValue(class_instance, buffer);
			retVal = sInstance->CreateBuiltinScriptObject(dataType->Tag(), buffer);
		}
		else if(IsUserDefined(dataType))
		{
			void* pVal = dataType->CreateInstance();
			data->getValue(class_instance, pVal);
			retVal = sInstance->CreateUserDefScriptObject(dataType, pVal, export_entry->Module, SIT_OWNED);
		}
		else if(IsPointerToBuiltin(dataType))
		{
			NOT_IMPLEMENTED();
		}
		else if(IsPointerToUserDefined(dataType))
		{
			void* ptr;
			data->getValue(class_instance, &ptr);
			retVal = sInstance->CreateUserDefScriptObject(static_cast<PointerType*>(dataType)->getPointedType(),
				ptr, export_entry->Module, SIT_SHARED);
		}

		if(!retVal)
			PyErr_SetString(PyExc_AttributeError, data->getName());

		return retVal;
	}

	//////////////////////////////////////////////////////////////////////////

	int CScriptManager::callback_attribute_set(PyObject *self, PyObject *value, void *closure)
	{
		// Get class type
		InstanceObject *instance_info = ExtractInstanceInfo(self);
		ExportEntry *export_entry = instance_info->object_type;

		if(!instance_info->instance)
		{
			PyErr_SetString(PyExc_RuntimeError, "Invoking method on not initialized object");
			return 0;
		}

		ASSERT_STRICT(closure);
		DataDescriptor* data = static_cast<DataDescriptor*>(closure);
		Type* dataType = data->getType();

		void* class_instance = PrepareInstancePointer(instance_info, data->getOwnerClass());

		if(IsBuiltIn(dataType))
		{
			char buffer[8] = { 0 };
			sInstance->ConvertToBuiltinValue(dataType->Tag(), buffer, value);
			data->setValue(class_instance, buffer);
		}
		else if(IsUserDefined(dataType))
		{
			data->setValue(class_instance, ExtractInstanceInfo(value)->instance);
		}
		else if(IsPointerToBuiltin(dataType))
		{
			NOT_IMPLEMENTED();
		}
		else if(IsPointerToUserDefined(dataType))
		{
			data->setValue(class_instance, &ExtractInstanceInfo(value)->instance);
		}

		return 0;
	}

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	PyObject* CScriptManager::callback_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
	{
		// type is a field in ExportEntry, so we can get it using offset
		ExportEntry* ent = ExtractTypeInfo((PyObject*)type);

		if(!ent) // case when __new__ was called by subclass
			ent = FindExportedBase(type->tp_base);

		// Allocate instance object
		InstanceObject* inst_info = (InstanceObject*)type->tp_alloc(type, 0);
		inst_info->instance = 0;
		inst_info->ctor = 0;
		inst_info->inst_type = SIT_OWNED;
		inst_info->object_type = ent;

		return (PyObject*)inst_info;
	}

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	int CScriptManager::callback_init(PyObject *self, PyObject *args, PyObject *kwds)
	{
		InstanceObject *instance_info = ExtractInstanceInfo(self);
		ExportEntry *ent = instance_info->object_type;

		// __init__ can be called to reset object
		if(instance_info->instance)
		{
			instance_info->ctor->DestroyInstance(instance_info->instance);
			instance_info->instance = 0;
			instance_info->ctor = 0;
		}

		// Compose parameters
		size_t nargs = PyTuple_Size(args);
		SInvokeArgs inv_args;
		inv_args.clear();

		ConstructDescriptor* constructor = 0;

		size_t nServices = ent->Type->getServiceNumber();
		for(size_t ctor = 0; ctor != nServices; ++ctor)
		{
			TypeDescriptor* desc = ent->Type->getServiceDescriptor(ctor);
			if(desc->getDescriptorType() != RL_DESC_SERVICE_CONSTRUCT)
				continue;

			ConstructDescriptor* ct = static_cast<ConstructDescriptor*>(desc);
			if(ct->GetCtorType()->getArgumentNumber() != nargs)
				continue;

			if(!PackFunctionArguments(ct->GetCtorType()->getArgumentTypes(), nargs, inv_args, args, 0))
			{
				inv_args.clear();
				continue;
			}

			constructor = ct;
		}

		if(!constructor)
		{
			PyErr_SetString(PyExc_TypeError, "No suitable constructor found");
			return -1;
		}

		// Create new class instance
		instance_info->instance = constructor->CreateInstance(inv_args.values);
		if(!instance_info->instance)
		{
			PyErr_SetString(PyExc_TypeError, "Failed to crate class instance");
			return -1;
		}

		// Save the ctor to use corresponding destructor later
		instance_info->ctor = constructor;

		return 0;
	}

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	// Called when object destructor is executed
	void CScriptManager::callback_dealloc(PyObject *self)
	{
		PyTypeObject* type = self->ob_type;
		InstanceObject* inst_info = (InstanceObject*)self;
		ExportEntry* entry = inst_info->object_type;

		// Only owned instances should be destroyed
		if(inst_info->inst_type == SIT_OWNED)
		{
			if(inst_info->ctor)
				inst_info->ctor->DestroyInstance(inst_info->instance);
			else
				entry->Type->DestroyInstance(inst_info->instance);
		}

		// Destroy instance descriptor
		type->tp_free(inst_info);
	}

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	// Called when to string conversion is called
	PyObject* CScriptManager::callback_tostring(PyObject *self)
	{
		InstanceObject *inst = ExtractInstanceInfo(self);

		if(!inst->instance)
		{
			PyErr_SetString(PyExc_RuntimeError, "Invoking method on not initialized object");
			return 0;
		}

		char buff[1024];

		if(!inst->object_type->Type->ToString(inst->instance, buff, 1024))
		{
			PyObject* repr = PyObject_Repr(self);
			return repr;
		}

		return PyUnicode_FromString(buff);
	}

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	PyObject * CScriptManager::callback_richcompare(PyObject *self, PyObject *other, int op)
	{
		PyTypeObject *type_self = self->ob_type;
		PyTypeObject *type_other = other->ob_type;

		ExportEntry *ent_self = ExtractTypeInfo((PyObject*)type_self);
		ExportEntry *ent_other = ExtractTypeInfo((PyObject*)type_other);

		InstanceObject *inst_self = ent_self ? ExtractInstanceInfo(self) : 0;
		InstanceObject *inst_other = ent_other ? ExtractInstanceInfo(other) : 0;

		PyObject *ret = 0;

		switch(op)
		{
		case Py_EQ:
			ret = (inst_self && inst_other && inst_self->instance == inst_other->instance) ?
			Py_True : Py_False;
			break;
		case Py_NE:
			ret = (inst_self && inst_other && inst_self->instance == inst_other->instance) ?
			Py_False : Py_True;
			break;
		default:
			ret = Py_NotImplemented;
		};

		Py_XINCREF(ret);
		return ret;
		return 0;
	}

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	long CScriptManager::callback_hash(PyObject *self)
	{
		InstanceObject *inst_self = ExtractInstanceInfo(self);
		return reinterpret_cast<long>(inst_self->instance);
	}

	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

} // namespace
