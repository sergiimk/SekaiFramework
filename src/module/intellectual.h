/*========================================================
* Intellectual.h
* @author Sergey Mikhtonyuk
* @date 24 November 2008
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _INTELLECTUAL_H__
#define _INTELLECTUAL_H__

#include "platform/platform.h"

namespace module
{

	//////////////////////////////////////////////////////////////////////////

	namespace detail
	{

		/// This tricky class protects you from calling AddRef/Release on pointer wrapped by com_ptr
		/** @ingroup module */
		template <class T>
		class no_refcnt_ptr: public T
		{
		private:
			virtual unsigned long AddRef() = 0;
			virtual unsigned long Release() = 0;
		};

		//////////////////////////////////////////////////////////////////////////

		static inline IUnknown* _ComPtrAssign(IUnknown** pp, IUnknown* lp)
		{
			if (lp != 0) lp->AddRef();
			if (*pp) (*pp)->Release();
			*pp = lp;
			return lp;
		}

		static inline IUnknown* _ComQIPtrAssign(IUnknown** pp, IUnknown* lp, SF_RIID riid)
		{
			IUnknown* pTemp = *pp;
			*pp = 0;
			if (lp != 0) lp->QueryInterface(riid, reinterpret_cast<void**>(pp));
			if (pTemp) pTemp->Release();

			return *pp;
		}

	} // detail


	//////////////////////////////////////////////////////////////////////////


	/// Base class for intellectual pointers
	/** @ingroup module */
	template <class T>
	class com_ptr_impl
	{
	protected:
		T* p;

	public:
		typedef T							interface_type;
		typedef T*							pointer_type;
		typedef detail::no_refcnt_ptr<T>*	safe_pointer_type;


		/// Empty ctor
		com_ptr_impl() : p(0) { }

		/// Construct around pointer
		com_ptr_impl(T* lp) : p(lp) { if (p != 0) p->AddRef(); }

		/// Copy ctor
		com_ptr_impl(const com_ptr_impl<T>& other) : p(other.p) { if (p != 0) p->AddRef(); }

		/// Move ctor
		com_ptr_impl(com_ptr_impl&& other) : p(other.p) { other.p = 0; }

		/// Destructor
		~com_ptr_impl() { if (p) p->Release(); }



		/// To pointer conversion
		operator T*() const { return p; }

		/// Dereferencing
		T& operator*() const { ASSERT_STRICT(p!=0); return *p; }

		/// Pointer to pointer
		T** wrapped() { ASSERT_STRICT(p==0); return &p; }

		/// 
		safe_pointer_type operator->() const { ASSERT_STRICT(p!=0); return (safe_pointer_type)p; }

		/// Negation
		bool operator!() const { return (p == 0); }

		/// Less operator
		bool operator<(T* pT) const { return p < pT; }

		/// Equality
		bool operator==(T* pT) const { return p == pT; }

		/// Not equality
		bool operator!=(T* pT) const { return !operator==(pT); }

		/// Assigning pointer
		T* operator = (T* lp)
		{
			if(*this != lp)
				return static_cast<T*>(detail::_ComPtrAssign((IUnknown**)&p, lp));
			return *this;
		}

		/// Assigning intellectual pointer 
		com_ptr_impl<T>& operator = (const com_ptr_impl<T>& rhs)
		{
			if(*this != &rhs)
				return static_cast<T*>(detail::_ComPtrAssign((IUnknown**)&p, rhs));
			return *this;
		}

		/// Move assignment
		com_ptr_impl<T>& operator = (com_ptr_impl<T>&& rhs)
		{
			if(*this != &rhs)
			{
				Release();
				p = rhs.p;
				rhs.p = 0;
			}
			return *this;
		}


		/// Releases the interface and sets ptr to 0
		void Release()
		{
			T* pTemp = p;
			if (pTemp) {
				p = 0;
				pTemp->Release();
			}
		}

		/// Attach to an existing interface (doesn't call AddRef)
		void Attach(T* p2) { if (p) p->Release(); p = p2; }

		/// Detach the interface (doesn't call Release)
		T* Detach() { T* pt = p; p = 0; return pt; }
	};



	/// Base class for intellectual Com pointers
	/** @ingroup module */
	template <class T>
	class com_ptr : public com_ptr_impl<T>
	{
	public:
		typedef T							interface_type;
		typedef T*							pointer_type;
		typedef detail::no_refcnt_ptr<T>*	safe_pointer_type;

		com_ptr() { }
		com_ptr(T* lp) : com_ptr_impl<T>(lp) { }
		com_ptr(const com_ptr<T>& other) : com_ptr_impl<T>(other) { }
		com_ptr(com_ptr<T>&& other) : com_ptr_impl<T>(std::move(other)) { }

		/// Cast ctor
		com_ptr(IUnknown* pUnk)
		{
			if (pUnk)
				pUnk->QueryInterface(uuid_of(T), (void **)&p);
		}

		/// Cast ctor
		template<typename Q>
		com_ptr(const com_ptr<Q>& other)
		{
			if (other)
				other->QueryInterface(uuid_of(T), (void **)&p);
		}

		/// Assigning pointer with type casting
		T* operator = (IUnknown* lp)
		{
			if(*this != lp)
				return static_cast<T*>(detail::_ComQIPtrAssign((IUnknown**)&p, lp, uuid_of(T)));
			return *this;
		}

		/// Assigning intellectual pointer with interface querying
		template <typename Q>
		com_ptr<T>& operator = (const com_ptr<Q>& rhs)
		{
			if(!Equal(rhs))
				return static_cast<T*>(detail::_ComQIPtrAssign((IUnknown**)&p, rhs, uuid_of(T)));
			return *this;
		}

		template <typename Q>
		com_ptr<T>& operator = (com_ptr<Q>&& rhs)
		{
			Release();
			Q* ptr = rhs;
			if(ptr)
			{
				ptr->QueryInterface(UUID_PPV(T, &p));
				rhs.Release();
			}
			return *this;
		}

		/// Compares two objects
		bool Equal(IUnknown* pObj);
	};



	//////////////////////////////////////////////////////////////////////////



	/// com_ptr specialization for IUnknown
	/** @ingroup module */
	template<>
	class com_ptr<IUnknown> : public com_ptr_impl<IUnknown>
	{
	public:
		typedef IUnknown							interface_type;
		typedef IUnknown*							pointer_type;
		typedef detail::no_refcnt_ptr<IUnknown>*	safe_pointer_type;

		com_ptr() { }
		com_ptr(IUnknown* lp) : com_ptr_impl<IUnknown>(lp) { }
		com_ptr(const com_ptr<IUnknown>& other) : com_ptr_impl<IUnknown>(other) { }

		template <typename Q>
		IUnknown* operator = (const com_ptr<Q>& lp)
		{
			if(!Equal(lp))
				return detail::_ComQIPtrAssign(&p, lp, uuid_of(IUnknown));
			return *this;
		}

		bool Equal(IUnknown* pObj)
		{
			return p == pObj;
		}
	};



	template<class T>
	bool com_ptr<T>::Equal(IUnknown* pObj)
	{
		if (this->p == 0 && pObj == 0)
			return true;

		if (this->p == 0 || pObj == 0)
			return false;

		com_ptr<IUnknown> punk1;
		com_ptr<IUnknown> punk2;
		this->p->QueryInterface(UUID_PPV(IUnknown, punk1.wrapped()));
		pObj->QueryInterface(UUID_PPV(IUnknown, punk2.wrapped()));
		return punk1 == punk2;
	}



	//////////////////////////////////////////////////////////////////////////


} // namespace

//////////////////////////////////////////////////////////////////////////

/// Creation helper for com_ptr
/** @ingroup module */
template<class Impl, class Itf>
module::HResult create_instance(module::com_ptr<Itf>& ptr)
{
	return Impl::_ObjectClass::_CreateInstance(UUID_PPV(Itf, ptr.wrapped()));
}

//////////////////////////////////////////////////////////////////////////

#endif // _INTELLECTUAL_H__
