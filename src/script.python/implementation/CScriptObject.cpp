/*========================================================
* CScriptObject.cpp
* @author Sergey Mikhtonyuk
* @date 07 Feb 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "CScriptObject.h"

namespace ScriptPy
{
	//////////////////////////////////////////////////////////////////////////

	CScriptObject::CScriptObject()
		: m_object(0)
	{
	}

	//////////////////////////////////////////////////////////////////////////

	void CScriptObject::FinalConstruct(PyObject* obj)
	{
		ASSERT_STRICT(obj);
		m_object = obj;
		Py_INCREF(m_object);
	}

	//////////////////////////////////////////////////////////////////////////

	CScriptObject::~CScriptObject()
	{
		Py_XDECREF(m_object);
	}

	//////////////////////////////////////////////////////////////////////////

	bool CScriptObject::HasMember(const char *mem_name)
	{
		int res = PyObject_HasAttrString(m_object, mem_name);
		ASSERT_SOFT(res != -1);
		return res == 1;
	}

	//////////////////////////////////////////////////////////////////////////

	bool CScriptObject::GetMember(const char* mem_name, SScriptAny& out_val)
	{
		PyObject* member = PyObject_GetAttrString(m_object, mem_name);

		if(!member) 
			return false;

		bool ret = CScriptManager::sInstance->MakeAny(member, out_val);
		Py_DECREF(member);

		return ret;
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace
