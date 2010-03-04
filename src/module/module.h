/*========================================================
* Module.h
* @author Sergey Mikhtonyuk
* @date 02 May 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _MODULE_ACCESS_H__
#define _MODULE_ACCESS_H__

#include "implementations.h"
#include "intellectual.h"

namespace Module
{
	//////////////////////////////////////////////////////////////////////////

	/// Module managing class
	/** Used to easily load the module and gain access to module map
	*  @ingroup Module */
	class ModuleHandle
	{
		typedef detail::MODULE_MAP_ENTRY* (*GET_MAP_FUNC)();
		typedef void (*INIT_FUNC)();
		typedef void (*SHUTDOWN_FUNC)();

	public:

		//////////////////////////////////////////////////////////////////////////
		class iterator
		{
			friend class ModuleHandle;

		public:
			bool operator ==(const iterator& rhs) const { return m_pEntry == rhs.m_pEntry; }
			bool operator !=(const iterator& rhs) const { return !(*this == rhs); }
			iterator& operator++() { ASSERT_STRICT(m_pEntry); ++m_pEntry; checkEnd(); return *this; }
			iterator operator++(int) { iterator ret(*this); ++*this; return ret; }
			const GUID* ClassID() const { return m_pEntry->pClsid; }
			Reflection::Type* ReflectedType() const { return (m_pEntry->pTypeOf) ? m_pEntry->pTypeOf() : 0; }

			iterator() : m_pEntry(0) { }
			iterator(const iterator& other) : m_pEntry(other.m_pEntry) { }

		private:
			iterator(detail::MODULE_MAP_ENTRY* entry) : m_pEntry(entry) { }
			void checkEnd() { if(!m_pEntry->pClsid) m_pEntry = 0; }
			detail::MODULE_MAP_ENTRY* m_pEntry;
		};
		//////////////////////////////////////////////////////////////////////////

		/// Creates uninitialized module object
		ModuleHandle();

		/// Creates and initializes module object
		ModuleHandle(const char* moduleName);

		/// Creates a 'weak' module handle that don't control library lifetime
		ModuleHandle(GET_MAP_FUNC mapFunc);

		/// Copy Ctor, only creates 'weak' handles
		ModuleHandle(const ModuleHandle& other);

		/// Assignment operation only degrades to 'weak' handles
		ModuleHandle& operator=(const ModuleHandle& rhs);

		/// Unloads the package
		virtual ~ModuleHandle();

		/// Used to bind module object to some dll and extract module map accessor
		HResult Init(const char* moduleName);

		/// Initializes the 'weak' module handle
		void Init(GET_MAP_FUNC mapFunc);

		/// Calls module shutdown routine
		void Shutdown();

		/// Unloads the binary
		void Unload();

		/// Checks if module is loaded and module map extracted
		bool IsLoaded() const;

		/// Returns a 'weak' module handle
		ModuleHandle GetWeakHandle() const;

		/// Returns iterator to the first element of map
		iterator MapBegin() const;

		/// Returns iterator to the last element of map
		iterator MapEnd() const;

		/// Creates instance of the class and tries to cast it to desired interface
		/** @param clsid CLS_ID of the class to create
		*  @param riid Interface ID of interface to cast to
		*  @param outObj location where to put the interface pointer */
		HResult CreateInstance(SF_RIID clsid, SF_RIID riid, void** outObj) const;

		/// Creates first found implementation of specified interface
		/**@param riid Interface ID of desired interface
		* @param outObj location where to put the interface pointer */
		HResult CreateInstance(SF_RIID riid, void** outObj) const;

		/// Searches the module map for reflection for the specified class
		/** @param clsid ID of the implementation class */
		Reflection::Type* GetType(SF_RIID clsid) const;

	private:

		void*			mModule;			///< Module handle
		INIT_FUNC		mInitFunc;			///< Init function
		SHUTDOWN_FUNC	mShutdownFunc;		///< Init function
		GET_MAP_FUNC	mGetModuleMap;		///< Map access
	};

} // namespace


//////////////////////////////////////////////////////////////////////////


/// Creates implementation from specified module (refCount == 1)
/** @ingroup Module */
template<class Itf>
Module::HResult create_instance(Itf** outObj, SF_RIID clsid, const Module::ModuleHandle& module)
{
	return module.CreateInstance(clsid, UUID_PPV(Itf, outObj));
}

/// Creation helper for com_ptr
/** @ingroup Module */
template<class Itf>
Module::HResult create_instance(Module::com_ptr<Itf>& ptr, SF_RIID clsid, const Module::ModuleHandle& module)
{
	return module.CreateInstance(clsid, UUID_PPV(Itf, ptr.wrapped()));
}

/// Creates implementation from specified module (refCount == 1)
/** @ingroup Module */
inline Module::HResult create_instance(void** outObj, SF_RIID iid, SF_RIID clsid, const Module::ModuleHandle& module)
{
	return module.CreateInstance(clsid, iid, outObj);
}

/// Creates first found implementation of specified interface (refCount == 1)
/** @ingroup Module */
template<class Itf>
Module::HResult create_instance(Itf** outObj, const Module::ModuleHandle& module)
{
	return module.CreateInstance(UUID_PPV(Itf, outObj));
}

/// Creation helper for com_ptr
/** @ingroup Module */
template<class Itf>
Module::HResult create_instance(Module::com_ptr<Itf>& ptr, const Module::ModuleHandle& module)
{
	return module.CreateInstance(UUID_PPV(Itf, ptr.wrapped()));
}

/// Creates first found implementation of specified interface (refCount == 1)
/** @ingroup Module */
inline Module::HResult create_instance(void** outObj, SF_RIID iid, const Module::ModuleHandle& module)
{
	return module.CreateInstance(iid, outObj);
}

//////////////////////////////////////////////////////////////////////////

#endif // _MODULE_ACCESS_H__
