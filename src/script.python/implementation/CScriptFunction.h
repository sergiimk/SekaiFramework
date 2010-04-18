/*========================================================
* CScriptFunction.h
* @author Sergey Mikhtonyuk
* @date 14 July 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _CSCRIPTFUNCTION_H__
#define _CSCRIPTFUNCTION_H__

#include "IScriptFunction.h"
#include "module/implementations.h"
#include "CScriptManager.h"

namespace ScriptPy
{

	/// Implementation of IScriptFunction for Python
	/** @ingroup Py */
	class NOVTABLE CScriptFunction : 
		public module::ComRootObject<>,
		public Script::IScriptFunction
	{
	public:
		
		DECLARE_IMPLEMENTATION(CScriptFunction)
	
		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(IScriptFunction)
		END_INTERFACE_MAP()

		CScriptFunction();

		~CScriptFunction();

		void FinalConstruct(PyObject* callable);

		void Invoke(reflection::value_type_pair* args, size_t nargs, reflection::value_type_pair* ret);	

	private:

		PyObject* mCallable;
	};

} // namespace

#endif // _CSCRIPTFUNCTION_H__