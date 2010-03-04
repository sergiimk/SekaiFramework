/*========================================================
* CBundleRepository.h
* @author Sergey Mikhtonyuk
* @date 21 November 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _CBUNDLEREPOSITORY_H__
#define _CBUNDLEREPOSITORY_H__

#include "IBundle.h"
#include "common/containers.h"
#include "Impl_fwd.h"
#include "CEventListenerQueue.h"
#include "common/stringutils.h"
#include "platform/hash_map.h"
#include <boost/thread.hpp>

using namespace Module;

namespace Framework
{
	/// Bundle registry
	/** @ingroup Framework */
	class CBundleRepository
	{
	public:

		CBundleRepository();

		~CBundleRepository();

		void Init(CSystemBundle* systemBundle);

		com_ptr<IBundle> CreateNewBundle(const char* location);

		com_ptr<IBundle> getBundle(size_t bundleId) const;

		com_ptr<IBundle> getBundle(const char* location) const;

		void getBundles(IDynArray<com_ptr<IBundle> >& bundles) const;

		void RemoveBundle(IBundle* bundle);

		const CEventListenerQueue& getListeners() const;

		const CEventListenerQueue& getSyncListeners() const;

		void AddListener(IBundleListener* listener);

		void RemoveListener(IBundleListener* listener);

	private:
		typedef std::hash_map<size_t, CBundle*> TBundleById;
		typedef std::hash_map<const char*, CBundle*, cstr_hash, cstrcmp_eq> TBundleByLocation;

		TBundleById m_bundlesById;
		TBundleByLocation m_bundlesByLocation;
		
		CEventListenerQueue m_listeners;
		CEventListenerQueue m_syncListeners;

		size_t m_lastBundleId;
		CSystemBundle* m_systemBundle;

		typedef boost::shared_lock<boost::shared_mutex> read_lock;
		typedef boost::unique_lock<boost::shared_mutex> write_lock;
		mutable boost::shared_mutex m_lock;
	};

} // namespace

#endif // _CBUNDLEREPOSITORY_H__
