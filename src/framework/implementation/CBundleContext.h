/*========================================================
* CBundleContext.h
* @author Sergey Mikhtonyuk
* @date 21 November 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _CBUNDLECONTEXT_H__
#define _CBUNDLECONTEXT_H__

#include "IBundleContext.h"
#include "module/implementations.h"
#include "Impl_fwd.h"
#include <boost/thread.hpp>
#include <vector>

using namespace module;

namespace Framework
{

	/// Implementation of bundle context
	/** @ingroup Framework */
	class NOVTABLE CBundleContext 
		: public ComRootObject<module::MultiThreadModel>
		, public IBundleContext
	{
		DECLARE_IMPLEMENTATION(CBundleContext)

		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(IBundleContext)
		END_INTERFACE_MAP()

		CBundleContext();
		void FinalConstruct(CSystemBundle* systemBundle, CBundle* bundle);
		void DropListeners();
		void Finalize();
		void CheckValid() const;

		virtual com_ptr<IBundle> getBundle();
		virtual com_ptr<IBundle> getBundle(size_t id);
		virtual void getBundles(IDynArray<com_ptr<IBundle> >& bundles);
		virtual com_ptr<IBundle> InstallBundle(const char* location);
		virtual com_ptr<IServiceRegistration> RegisterService(guid const& riid, IUnknown* object);
		virtual com_ptr<IServiceReference> getServiceReference(guid const& riid);
		virtual com_ptr<IUnknown> getService(IServiceReference* reference);
		virtual bool ungetService(IServiceReference* reference);

		virtual void AddBundleListener(IBundleListener* listener);
		virtual void RemoveBundleListener(IBundleListener* listener);
		virtual void AddFrameworkListener(IFrameworkListener* listener);
		virtual void RemoveFrameworkListener(IFrameworkListener* listener);
		virtual void AddServiceListener(IServiceListener* listener);
		virtual void RemoveServiceListener(IServiceListener* listener);

	private:
		typedef std::vector<IFrameworkListener*> TFwkLnr;
		typedef std::vector<IBundleListener*> TBndlLnr;
		typedef std::vector<IServiceListener*> TSvcLnr;
		
		TFwkLnr m_frameworkListeners;
		TBndlLnr m_bundleListeners;
		TSvcLnr m_serviceListeners;

		typedef boost::mutex::scoped_lock scoped_lock;
		boost::mutex m_lock;

		CSystemBundle* m_systemBundle;
		CBundle* m_bundle;
	};

} // namespace

#endif // _CBUNDLECONTEXT_H__
