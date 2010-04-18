/*========================================================
* CScriptTable.h
* @author Sergey Mikhtonyuk
* @date 31 Jan 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _CSCRIPTTABLE_H__
#define _CSCRIPTTABLE_H__

#include "IScriptTable.h"
#include "module/implementations.h"
#include "CScriptManager.h"

namespace ScriptPy
{
	/// Implementation of abstract table interface
	/** @ingroup Py */
	class NOVTABLE CScriptTable : 
		public module::ComRootObject<>,
		public IScriptTable
	{
	public:
		
		DECLARE_IMPLEMENTATION(CScriptTable)
	
		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(IScriptTable)
		END_INTERFACE_MAP()

		CScriptTable();

		~CScriptTable();

		void FinalConstruct(PyObject* obj);
	
		virtual bool HasEntryRaw(const reflection::value_type_pair& attr_key);

		virtual bool GetEntryRaw(const reflection::value_type_pair& attr_key, reflection::value_type_pair& out_val);

	private:

		PyObject* m_object;
	};
}

#endif //_CSCRIPTTABLE_H__
