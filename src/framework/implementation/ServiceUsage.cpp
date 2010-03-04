/*========================================================
* ServiceUsage.cpp
* @author Sergey Mikhtonyuk
* @date 08 December 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "ServiceUsage.h"
#include "CServiceRegistration.h"

namespace Framework
{
	//////////////////////////////////////////////////////////////////////////

	ServiceUsage::ServiceUsage(CServiceRegistration* registration, CBundle* bundle)
		: m_registration(registration)
		, m_bundle(bundle)
		, m_useCount(0)
	{ }

	//////////////////////////////////////////////////////////////////////////

	ServiceUsage::~ServiceUsage()
	{
		ASSERT_SOFT(!m_useCount);
		Reset();
	}

	//////////////////////////////////////////////////////////////////////////

	IUnknown* ServiceUsage::getService()
	{
		++m_useCount;
		return m_registration->getServiceObject(this);
	}

	//////////////////////////////////////////////////////////////////////////

	bool ServiceUsage::ungetService()
	{
		if(!m_useCount)
			return false;

		if(!(--m_useCount))
			m_registration->ungetServiceObject(this);

		return true;
	}

	//////////////////////////////////////////////////////////////////////////

	CServiceRegistration* ServiceUsage::getRegistration() const
	{
		return m_registration;
	}

	//////////////////////////////////////////////////////////////////////////

	CBundle* ServiceUsage::getBundle() const
	{
		return m_bundle;
	}

	//////////////////////////////////////////////////////////////////////////

	int ServiceUsage::getUseCount() const
	{
		return m_useCount;
	}

	//////////////////////////////////////////////////////////////////////////

	void ServiceUsage::Reset()
	{
		if(m_useCount != 0)
		{
			m_useCount = 0;
			m_registration->ungetServiceObject(this);
		}
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace
