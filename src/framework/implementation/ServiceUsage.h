/*========================================================
* ServiceUsage.h
* @author Sergey Mikhtonyuk
* @date 08 December 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _SERVICEUSAGE_H__
#define _SERVICEUSAGE_H__

#include "module/interfaces.h"
#include "Impl_fwd.h"

using namespace Module;

namespace Framework
{
	/// Tracks usage of the service
	/** @ingroup Framework */
	class ServiceUsage
	{
	public:
		ServiceUsage(CServiceRegistration* registration, CBundle* user);

		~ServiceUsage();

		IUnknown* getService();
		
		bool ungetService();

		CServiceRegistration* getRegistration() const;

		CBundle* getBundle() const;

		int getUseCount() const;

		void Reset();

	private:
		CServiceRegistration* m_registration;
		CBundle* m_bundle;
		int m_useCount;
	};

} // namespace

#endif // _SERVICEUSAGE_H__
