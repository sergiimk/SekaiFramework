/*========================================================
* CServiceReference.h
* @author Sergey Mikhtonyuk
* @date 06 December 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _CSERVICEREFERENCE_H__
#define _CSERVICEREFERENCE_H__

#include "Services.h"
#include "module/implementations.h"
#include "Impl_fwd.h"

using namespace Module;

namespace Framework
{
	/// Implementation of service reference object
	/** @ingroup Framework */
	class NOVTABLE CServiceReference : 
		public Module::ComRootObject<Module::MultiThreadModel>,
		public IServiceReference
	{
	public:
		
		DECLARE_IMPLEMENTATION(CServiceReference)
	
		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(IServiceReference)
		END_INTERFACE_MAP()
	
		CServiceReference();

		~CServiceReference();

		void FinalConstruct(CServiceRegistration* service);

		CServiceRegistration* getRegistration();

		void Finalize();

		virtual com_ptr<IBundle> getBundle();

	private:
		CServiceRegistration* m_service;
	};

} // namespace

#endif // _CSERVICEREFERENCE_H__
