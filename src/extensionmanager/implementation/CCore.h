/*========================================================
* CCore.h
* @author Sergey Mikhtonyuk
* @date 09 November 2008
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _CORE_H__
#define _CORE_H__

#include "ICore.h"
#include "GlobalEnvironment.h"
#include "module/module.h"

namespace Extensions
{

	/// Core class implementation
	/** Implements facade class to all subsystems
	 *  @ingroup Extensions */
	class NOVTABLE CCore : 
		public module::ComRootObject<>,
		public ICore
	{
	public:

		DECLARE_IMPLEMENTATION2(CCore, module::ComClassFactorySingleton)

		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(ICore)
		END_INTERFACE_MAP()

		/// Ctor
		CCore();

		/// Destructor
		virtual ~CCore();

		void Initialize(const char* paramsFile);

		void StartExecution(int argc, char *argv[]);

		GlobalEnvironment* Environment() const { return pCurrentEnvironment; }

		void RegisterEnvironment(GlobalEnvironment* newEnv);

		/// Execution wrapped with exception handlers
		void	StartExecution_actual(int argc, char *argv[]);

	private:
		module::ModuleHandle mLogModule;
		GlobalEnvironment	mEnvironment;			///< Base global environment structure
		GlobalEnvironment*	pCurrentEnvironment;	///< Current environment pointer
	};

}

#endif // _CORE_H__