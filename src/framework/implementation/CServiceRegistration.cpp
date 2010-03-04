/*========================================================
* CServiceRegistration.cpp
* @author Sergey Mikhtonyuk
* @date 23 November 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "CServiceRegistration.h"
#include "CBundle.h"

namespace Framework
{
	//////////////////////////////////////////////////////////////////////////

	CServiceRegistration::CServiceRegistration()
		: m_object(0)
		, m_bundle(0)
		, m_reference(0)
	{ }

	//////////////////////////////////////////////////////////////////////////

	void CServiceRegistration::FinalConstruct(const GUID &riid, IUnknown *pObject, CBundle* bundle)
	{
		m_id = riid;

		m_object = pObject;
		m_object->AddRef();

		m_bundle = bundle;

		create_instance_impl(&m_reference);
		m_reference->FinalConstruct(this);
	}

	//////////////////////////////////////////////////////////////////////////

	const GUID& CServiceRegistration::getID() const
	{
		return m_id;
	}

	//////////////////////////////////////////////////////////////////////////

	com_ptr<IBundle> CServiceRegistration::getBundle() const
	{
		return m_bundle;
	}

	//////////////////////////////////////////////////////////////////////////

	IUnknown* CServiceRegistration::getServiceObject(ServiceUsage* usg)
	{
		if(usg && usg->getUseCount() == 1)
			m_users.insert(usg->getBundle());

		return m_object;
	}

	//////////////////////////////////////////////////////////////////////////

	void CServiceRegistration::ungetServiceObject(Framework::ServiceUsage *usg)
	{
		m_users.erase(usg->getBundle());
	}

	//////////////////////////////////////////////////////////////////////////

	com_ptr<IServiceReference> CServiceRegistration::getReference()
	{
		return m_reference;
	}

	//////////////////////////////////////////////////////////////////////////

	void CServiceRegistration::Unregister()
	{
		if(m_reference == 0)
			throw "IllegalStateException";

		m_object->Release();
		m_object = 0;

		// Protect from being deleted until done
		com_ptr_impl<CServiceRegistration> protect(this);

		m_bundle->UnregisterService(this);

		while(!m_users.empty())
			(*m_users.begin())->ForceUngetService(this);

		m_reference->Finalize();
		m_reference->Release();
		m_reference = 0;
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace
