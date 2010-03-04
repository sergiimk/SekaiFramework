/*========================================================
* CScriptFunction.cpp
* @author Sergey Mikhtonyuk
* @date 14 July 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "CScriptFunction.h"

namespace ScriptPy
{
	//////////////////////////////////////////////////////////////////////////

	CScriptFunction::CScriptFunction()
		: mCallable(0)
	{ }

	//////////////////////////////////////////////////////////////////////////

	CScriptFunction::~CScriptFunction()
	{
		Py_XDECREF(mCallable);
	}

	//////////////////////////////////////////////////////////////////////////

	void CScriptFunction::FinalConstruct(PyObject* callable)
	{
		ASSERT_STRICT(callable);
		mCallable = callable;
		Py_INCREF(mCallable);
	}

	//////////////////////////////////////////////////////////////////////////

	void CScriptFunction::Invoke(Reflection::ValueTypePair* args, size_t nargs, Reflection::ValueTypePair* ret)
	{

		CScriptManager::sInstance->InvokeCallable(mCallable, args, nargs, ret);
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace