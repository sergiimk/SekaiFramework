/*========================================================
* Impl_fwd.h
* @author Sergey Mikhtonyuk
* @date 08 December 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _IMPL_FWD_H__
#define _IMPL_FWD_H__

#include <stdio.h>
#include <boost/thread.hpp>
#include "platform/platform.h"

namespace Framework
{
	extern int _s_vb_tabs;

	struct _vb_tabber
	{
		_vb_tabber() { ++_s_vb_tabs; }
		~_vb_tabber() { --_s_vb_tabs; }
	};

	#define VERBOSE(str, ...)\
	_vb_tabber __tabber;\
	for(int i = 0; i < _s_vb_tabs; ++i) printf("  ");\
	printf(str, __VA_ARGS__);\
	printf("\n");

	extern boost::thread::id fwk_thread_id;
	extern boost::thread::id launcher_thread_id;

	#define THREAD_ANY()
	#define THREAD_ANY_USER() ASSERT_STRICT(boost::this_thread::get_id() != fwk_thread_id)
	#define THREAD_LAUNCHER() ASSERT_STRICT(boost::this_thread::get_id() == launcher_thread_id)
	#define THREAD_FRAMEWORK() ASSERT_STRICT(boost::this_thread::get_id() == fwk_thread_id)

	class CFrameworkFactory;
	class CSystemBundle;
	class CSystemBundleActivator;

	class CBundleRepository;
	class CServiceRegistry;

	class CBundle;
	class CBundleContext;

	class CServiceRegistration;
	class CServiceReference;
	class ServiceUsage;

	class CEventListenerQueue;
	struct IEventDispatcher;
	struct CFrameworkEventDispatcher;
	struct CBundleEventDispatcher;
	struct CServiceEventDispatcher;
	class CEventServer;

} // namespace

#endif // _IMPL_FWD_H__
