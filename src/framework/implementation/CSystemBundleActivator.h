/*========================================================
* CSystemBundleActivator.h
* @author Sergey Mikhtonyuk
* @date 07 December 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _CSYSTEMBUNDLEACTIVATOR_H__
#define _CSYSTEMBUNDLEACTIVATOR_H__

#include "IBundleActivator.h"
#include "module/implementations.h"
#include "module/intellectual.h"
#include "Impl_fwd.h"

#include "Listeners.h"

using namespace Module;

namespace Framework
{
	/// Activator that registers FileSystem service
	/** @ingroup Framework  */
	class NOVTABLE CSystemBundleActivator : 
		public Module::ComRootObject<Module::MultiThreadModel>,
		public IBundleActivator,
		public IServiceListener
	{
	public:

		DECLARE_IMPLEMENTATION(CSystemBundleActivator)

		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(IBundleActivator)
		END_INTERFACE_MAP()

		CSystemBundleActivator();
		void FinalConstruct(CSystemBundle* systemBundle);

		virtual void Start(IBundleContext* context);

		virtual void Stop(IBundleContext* context);

		virtual void ServiceChanged(const SServiceEvent& evnt);

	private:

		void LoadCoreBundles();

		void LoadInstalledBundles();

		void SaveBundleRegistryState();

		void StopAllBundles();

		void ReleaseCoreServices();

	private:
		IBundleContext* m_context;
		CSystemBundle* m_systemBundle;
		com_ptr<IServiceReference> m_logRef;
	};

} // namespace

#endif // _CSYSTEMBUNDLEACTIVATOR_H__
