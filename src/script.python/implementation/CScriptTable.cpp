/*========================================================
* CScriptTable.cpp
* @author Sergey Mikhtonyuk
* @date 31 Jan 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "CScriptTable.h"

namespace ScriptPy
{
	//////////////////////////////////////////////////////////////////////////

	CScriptTable::CScriptTable()
		: m_object(0)
	{
	}

	//////////////////////////////////////////////////////////////////////////

	CScriptTable::~CScriptTable()
	{
		Py_XDECREF(m_object);
	}

	//////////////////////////////////////////////////////////////////////////

	void CScriptTable::FinalConstruct(PyObject* obj)
	{
		m_object = obj;
		ASSERT_STRICT(PyDict_Check(obj));
		Py_INCREF(m_object);
	}

	//////////////////////////////////////////////////////////////////////////

	bool CScriptTable::HasEntryRaw(const reflection::value_type_pair &attr_key)
	{
		PyObject* py_key = script_cast(attr_key);

		if(!py_key)
			return false;

		int res = PyDict_Contains(m_object, py_key);

		Py_DECREF(py_key);

		ASSERT_SOFT(res != -1);
		return res == 1;
	}

	//////////////////////////////////////////////////////////////////////////

	bool CScriptTable::GetEntryRaw(const reflection::value_type_pair& attr_key, reflection::value_type_pair& out_val)
	{
		PyObject* py_key = script_cast(attr_key);

		if(!py_key)
			return false;

		PyObject* py_item = PyDict_GetItem(m_object, py_key);
		Py_DECREF(py_key);

		if (py_item)
		{
			bool ret = script_cast(py_item, out_val);
			Py_DECREF(py_item);
			return ret;
		}
		else
		{
			return false;
		}

	}

	//////////////////////////////////////////////////////////////////////////
}
