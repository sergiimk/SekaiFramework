/*========================================================
* SScriptAny.h
* @author Sergey Mikhtonyuk
* @date 31 Jan 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _SSCRIPTANY_H__
#define _SSCRIPTANY_H__

#include "IScriptFunction.h"
#include "IScriptTable.h"
#include "IScriptObject.h"

namespace Script
{
	/// Variant-like structure that wraps script m_value
	/** @ingroup Script */
	struct SScriptAny
	{
		enum EType
		{
			T_INT,
			T_FLOAT,
			T_FUNCTION,
			T_TABLE,
			T_OBJECT,
			T_NUM,
		};

		SScriptAny() : m_type(T_NUM) { }

		SScriptAny(int val)
			: m_type(T_INT)
		{ m_value.intVal = val; }

		SScriptAny(float val)
			: m_type(T_FLOAT)
		{ m_value.fltVal = val; }

		SScriptAny(IScriptFunction* val)
			: m_type(T_FUNCTION)
		{
			m_value.funcVal = val;

			if(m_value.funcVal)
				m_value.funcVal->AddRef();
		}

		SScriptAny(IScriptTable* val)
			: m_type(T_TABLE)
		{
			m_value.tblVal = val;

			if(m_value.tblVal)
				m_value.tblVal->AddRef();
		}

		SScriptAny(IScriptObject* val)
			: m_type(T_OBJECT)
		{
			m_value.objVal = val;

			if(m_value.objVal)
				m_value.objVal->AddRef();
		}

		SScriptAny(const SScriptAny& other)
		{
			m_type = other.m_type;
			m_value = other.m_value;
			
			addref();
		}

		SScriptAny& operator=(const SScriptAny& rhs)
		{
			clear();

			m_type = rhs.m_type;
			m_value = rhs.m_value;

			addref();
			return *this;
		}

		~SScriptAny()
		{
			clear();
		}

		EType getType() const { return m_type; }

		int asInt() { ASSERT_STRICT(m_type == T_INT); return m_value.intVal; }

		float asFloat() { ASSERT_STRICT(m_type == T_FLOAT); return m_value.fltVal; }

		IScriptFunction* asFunction() { ASSERT_STRICT(m_type == T_FUNCTION); return m_value.funcVal; }

		IScriptTable* asTable() { ASSERT_STRICT(m_type == T_TABLE); return m_value.tblVal; }

		IScriptObject* asObject() { ASSERT_STRICT(m_type == T_OBJECT); return m_value.objVal; }

		void clear()
		{
			if(m_type == T_FUNCTION && m_value.funcVal)
				m_value.funcVal->Release();
			else if(m_type == T_TABLE && m_value.tblVal)
				m_value.tblVal->Release();
			else if(m_type == T_OBJECT && m_value.objVal)
				m_value.objVal->Release();

			m_type = T_NUM;
		}

	private:

		void addref()
		{
			if(m_type == T_FUNCTION && m_value.funcVal)
				m_value.funcVal->AddRef();
			else if(m_type == T_TABLE && m_value.tblVal)
				m_value.tblVal->AddRef();
			else if(m_type == T_OBJECT && m_value.objVal)
				m_value.objVal->AddRef();
		}

	private:

		union
		{
			int intVal;
			float fltVal;
			IScriptFunction* funcVal;
			IScriptTable* tblVal;
			IScriptObject* objVal;
		} m_value;

		EType m_type;
	};
}

#endif //_SSCRIPTANY_H__
