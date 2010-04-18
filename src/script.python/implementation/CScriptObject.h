/*========================================================
* CScriptObject.h
* @author Sergey Mikhtonyuk
* @date 07 Feb 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _CSCRIPTOBJECT_H__
#define _CSCRIPTOBJECT_H__

#include "IScriptObject.h"
#include "CScriptManager.h"

namespace ScriptPy
{
	/// Implementation of script object interface
	/** @ingroup Py */
	class NOVTABLE CScriptObject : 
		public module::ComRootObject<>,
		public IScriptObject
	{
	public:
		
		DECLARE_IMPLEMENTATION(CScriptObject)
	
		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(IScriptObject)
		END_INTERFACE_MAP()
	
		CScriptObject();

		~CScriptObject();

		void FinalConstruct(PyObject* obj);

		virtual bool HasMember(const char* mem_name);

		virtual bool GetMember(const char* mem_name, SScriptAny& out_mem);

	private:

		PyObject* m_object;
	};
}

#endif //_CSCRIPTOBJECT_H__
