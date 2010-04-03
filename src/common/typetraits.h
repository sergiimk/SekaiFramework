/*========================================================
* TypeTraits.h
* @author Sergey Mikhtonyuk
* @date 05 April 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _TYPETRAITS_H__
#define _TYPETRAITS_H__

//////////////////////////////////////////////////////////////////////////

template<class T> struct t_strip
{ 
	typedef T plain;
	typedef T nomod;
	typedef T noref; 
	typedef T noptr; 
	typedef T ref2ptr;
	static const bool is_const = false; 
	static const bool is_ptr = false;
	static const bool is_ref = false;
};

template<class T> struct t_strip<T&>
{ 
	typedef T plain;
	typedef T& nomod;
	typedef T noref; 
	typedef T& noptr; 
	typedef T* ref2ptr; 
	static const bool is_const = false; 
	static const bool is_ptr = false;
	static const bool is_ref = true;
};

template<class T> struct t_strip<T*>
{ 
	typedef T plain; 
	typedef T* nomod;
	typedef T* noref; 
	typedef T noptr; 
	typedef T* ref2ptr; 
	static const bool is_const = false; 
	static const bool is_ptr = true; 
	static const bool is_ref = false;
};

template<class T> struct t_strip<const T&>
{ 
	typedef T plain; 
	typedef T& nomod;
	typedef T noref; 
	typedef T& noptr; 
	typedef T* ref2ptr; 
	static const bool is_const = true; 
	static const bool is_ptr = false; 
	static const bool is_ref = true;
};

template<class T> struct t_strip<const T*>
{ 
	typedef T plain; 
	typedef T* nomod;
	typedef T* noref; 
	typedef T noptr; 
	typedef T* ref2ptr; 
	static const bool is_const = true;
	static const bool is_ptr = true;
	static const bool is_ref = false;
};

//////////////////////////////////////////////////////////////////////////

/// Returns the offset between classes
template<class base, class derived>
inline size_t classoffset() { return (size_t)(static_cast<base*>((derived*)8)) - 8; }

/// Adjusts the pointer by specified offset
inline void* adjustptr(void* pThis, size_t offset) { return (char*)pThis + offset; }

//////////////////////////////////////////////////////////////////////////

#endif // _TYPETRAITS_H__
