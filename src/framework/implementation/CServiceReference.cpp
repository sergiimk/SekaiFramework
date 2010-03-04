/*========================================================
* CServiceReference.cpp
* @author Sergey Mikhtonyuk
* @date 06 December 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "CServiceReference.h"
#include "CServiceRegistration.h"
#include "CBundle.h"

namespace Framework
{

	//////////////////////////////////////////////////////////////////////////

	CServiceReference::CServiceReference()
		: m_service(0)
	{
	}

	//////////////////////////////////////////////////////////////////////////

	CServiceReference::~CServiceReference()
	{
	}

	//////////////////////////////////////////////////////////////////////////

	void CServiceReference::FinalConstruct(CServiceRegistration* service)
	{
		m_service = service;
	}

	//////////////////////////////////////////////////////////////////////////

	CServiceRegistration* CServiceReference::getRegistration()
	{
		return m_service;
	}

	//////////////////////////////////////////////////////////////////////////

	void CServiceReference::Finalize()
	{
		m_service = 0;
	}

	//////////////////////////////////////////////////////////////////////////

	com_ptr<IBundle> CServiceReference::getBundle()
	{
		/// \todo synchronize ???
		return m_service 
			? m_service->getBundle() 
			: com_ptr<IBundle>();
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace
