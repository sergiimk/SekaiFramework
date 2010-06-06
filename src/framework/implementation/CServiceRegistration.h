/*========================================================
* CServiceRegistration.h
* @author Sergey Mikhtonyuk
* @date 23 November 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _CSERVICEREGISTRATION_H__
#define _CSERVICEREGISTRATION_H__

#include "Services.h"
#include "module/implementations.h"
#include "CServiceReference.h"
#include <set>

using namespace module;

namespace Framework
{
	/// Service registration object
	/** @ingroup Framework */
	class NOVTABLE CServiceRegistration : 
		public module::ComRootObject<module::MultiThreadModel>,
		public IServiceRegistration
	{
	public:
		
		DECLARE_IMPLEMENTATION(CServiceRegistration)
	
		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(IServiceRegistration)
		END_INTERFACE_MAP()

		CServiceRegistration();

		void FinalConstruct(guid const& riid, IUnknown* pObject, CBundle* bundle);

		void Finalize();

		const guid& getID() const;

		com_ptr<IBundle> getBundle() const;

		IUnknown* getServiceObject(ServiceUsage* usg);

		void ungetServiceObject(ServiceUsage* usg);

		virtual com_ptr<IServiceReference> getReference();

		virtual void Unregister();

	private:
		typedef std::set<CBundle*> TServiceUsers;

		guid m_id;
		TServiceUsers m_users;
		IUnknown* m_object;
		CBundle* m_bundle;
		CServiceReference* m_reference;
	};

} // namespace

#endif // _CSERVICEREGISTRATION_H__
