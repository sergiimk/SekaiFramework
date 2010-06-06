/*========================================================
* module.h
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

namespace module
{
	//////////////////////////////////////////////////////////////////////////

	/// Module managing class
	/** Used to easily load the module and gain access to module map
	*  @ingroup module */
	class MODULE_API ModuleHandle
	{
	public:
		typedef detail::MODULE_MAP_ENTRY* (*GET_MAP_FUNC)();
		typedef void (*INIT_FUNC)(std::error_code* ec);
		typedef void (*SHUTDOWN_FUNC)();

		//////////////////////////////////////////////////////////////////////////

		class iterator
		{
			friend class ModuleHandle;

		public:
			bool operator ==(const iterator& rhs) const { return m_pEntry == rhs.m_pEntry; }
			bool operator !=(const iterator& rhs) const { return !(*this == rhs); }
			iterator& operator++() { ASSERT_STRICT(m_pEntry); ++m_pEntry; checkEnd(); return *this; }
			iterator operator++(int) { iterator ret(*this); ++*this; return ret; }
			const guid* ClassID() const { return m_pEntry->pClsid; }
			reflection::user_type* ReflectedType() const { return (m_pEntry->pTypeOf) ? m_pEntry->pTypeOf() : 0; }

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

		/// Can be used to create a handle to current module
		ModuleHandle(GET_MAP_FUNC mapFunc);

		/// Increases the reference count of module
		ModuleHandle(const ModuleHandle& other);

		/// Increases the reference count of module
		ModuleHandle& operator=(const ModuleHandle& rhs);

		/// Unloads the package
		virtual ~ModuleHandle();

		/// Used to bind module object to some dll and extract module map accessor
		std::error_code Init(const char* moduleName);

		/// Calls module shutdown routine, legal when only one handle left
		void Shutdown();

		/// Releases the module reference, if refcount reached zero the binary will be unloaded
		void Release();

		/// Checks if module is loaded and module map extracted
		bool IsLoaded() const;

		/// Returns iterator to the first element of map
		iterator MapBegin() const;

		/// Returns iterator to the last element of map
		iterator MapEnd() const;

		/// Creates instance of the class and tries to cast it to desired interface
		/** @param clsid CLS_ID of the class to create
		*  @param riid Interface ID of interface to cast to
		*  @param outObj location where to put the interface pointer */
		std::error_code CreateInstance(guid const& clsid, guid const& riid, void** outObj) const;

		/// Creates first found implementation of specified interface
		/**@param riid Interface ID of desired interface
		* @param outObj location where to put the interface pointer */
		std::error_code CreateInstance(guid const& riid, void** outObj) const;

		/// Searches the module map for reflection for the specified class
		/** @param clsid ID of the implementation class */
		reflection::user_type* GetType(guid const& clsid) const;

	private:

		struct ModuleHandleImpl;
		ModuleHandleImpl* m_impl;
	};

} // namespace


//////////////////////////////////////////////////////////////////////////


/// Creates implementation from specified module (refCount == 1)
/** @ingroup module */
template<class Itf>
std::error_code create_instance(Itf** outObj, module::guid const& clsid, const module::ModuleHandle& m)
{
	return m.CreateInstance(clsid, UUID_PPV(Itf, outObj));
}

/// creation helper for com_ptr
/** @ingroup module */
template<class Itf>
std::error_code create_instance(module::com_ptr<Itf>& ptr, module::guid const& clsid, const module::ModuleHandle& m)
{
	return m.CreateInstance(clsid, UUID_PPV(Itf, ptr.wrapped()));
}

/// creates implementation from specified module (refCount == 1)
/** @ingroup module */
inline std::error_code create_instance(void** outObj, module::guid const& iid, module::guid const& clsid, const module::ModuleHandle& m)
{
	return m.CreateInstance(clsid, iid, outObj);
}

/// creates first found implementation of specified interface (refCount == 1)
/** @ingroup module */
template<class Itf>
std::error_code create_instance(Itf** outObj, const module::ModuleHandle& m)
{
	return m.CreateInstance(UUID_PPV(Itf, outObj));
}

/// creation helper for com_ptr
/** @ingroup module */
template<class Itf>
std::error_code create_instance(module::com_ptr<Itf>& ptr, const module::ModuleHandle& m)
{
	return m.CreateInstance(UUID_PPV(Itf, ptr.wrapped()));
}

/// creates first found implementation of specified interface (refCount == 1)
/** @ingroup module */
inline std::error_code create_instance(void** outObj, module::guid const& iid, const module::ModuleHandle& m)
{
	return m.CreateInstance(iid, outObj);
}

//////////////////////////////////////////////////////////////////////////

#endif // _MODULE_ACCESS_H__
