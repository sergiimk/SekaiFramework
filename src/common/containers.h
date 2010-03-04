/*========================================================
* Array.h
* @author Sergey Mikhtonyuk
* @date 08 December 2009
* @description These containers are intended to be used 
*  across the dll boundaries
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _CONTAINERS_H__
#define _CONTAINERS_H__

#include "platform/platform.h"
#include <vector>
#include <map>

//////////////////////////////////////////////////////////////////////////
// IArray
//////////////////////////////////////////////////////////////////////////

/// Fixed-size array interface
/** @ingroup Common */
template<class T>
class IArray
{
public:
	virtual size_t size() const = 0;
	virtual T& operator[](size_t i) = 0;
	virtual const T& operator[](size_t i) const = 0;

protected:
	IArray() { }
	virtual ~IArray() { }

private:
	IArray(const IArray& other);
	IArray& operator=(const IArray& rhs);
};

//////////////////////////////////////////////////////////////////////////

/// Fixed-size array that wraps the pointer
/** @ingroup Common */
template<class T>
class ArrayImplWrapper : public IArray<T>
{
public:

	ArrayImplWrapper(T* data, size_t size)
		: m_data(data)
		, m_size(size)
	{
		ASSERT_STRICT(data);
		ASSERT_STRICT(size);
	}

	virtual size_t size() const 
	{ 
		return m_size; 
	}

	virtual T& operator[](size_t i) 
	{ 
		ASSERT_STRICT(i < m_size);
		return m_data[i];
	}

	virtual const T& operator[](size_t i) const
	{ 
		ASSERT_STRICT(i < m_size);
		return m_data[i];
	}

private:
	T* m_data;
	size_t m_size;
};

//////////////////////////////////////////////////////////////////////////

/// Fixed-size array
/** @ingroup Common */
template<class T, int S>
class ArrayImplOwned : public ArrayImplWrapper<T>
{
public:

	ArrayImplOwned()
		: ArrayImplWrapper<T>(m_data, S)
	{ }

private:
	T m_data[S];
};

//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
// IDynArray
//////////////////////////////////////////////////////////////////////////

/// Dynamic size array interface
/** @ingroup Common */
template<class T>
class IDynArray : public IArray<T>
{
public:
	virtual size_t capacity() const = 0;
	virtual void reserve(size_t size) = 0;
	virtual void resize(size_t size) = 0;
	virtual void push_back(const T& value) = 0;
	virtual void clear() = 0;
};

//////////////////////////////////////////////////////////////////////////

template<class T, class C = std::vector<T> >
class DynArrayImplWrapper : public IDynArray<T>
{
public:
	DynArrayImplWrapper(C* container)
		: m_container(container)
	{ }

	virtual size_t size() const
	{
		return m_container->size();
	}

	virtual T& operator[](size_t i)
	{
		return (*m_container)[i];
	}

	virtual const T& operator[](size_t i) const
	{
		return (*m_container)[i];
	}

	virtual size_t capacity() const
	{
		return m_container->capacity();
	}

	virtual void reserve(size_t size)
	{
		m_container->reserve(size);
	}

	virtual void resize(size_t size)
	{
		m_container->resize(size);
	}

	virtual void push_back(const T& value)
	{
		m_container->push_back(value);
	}

	virtual void clear()
	{
		m_container->clear();
	}

private:
	C* m_container;
};

//////////////////////////////////////////////////////////////////////////

template<class T, class C = std::vector<T> >
class DynArrayImplOwned : public DynArrayImplWrapper<T, C>
{
public:
	DynArrayImplOwned()
		: DynArrayImplWrapper<T, C>(&m_container)
	{ }

private:
	C m_container;
};

//////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
// IMap
//////////////////////////////////////////////////////////////////////////

template<class Key, class Val>
class IMap
{
public:
	virtual size_t size() const = 0;
	virtual Val& operator[](const Key& key) = 0;
	virtual const Val& operator[](const Key& key) const = 0;
};

//////////////////////////////////////////////////////////////////////////

template<class Key, class Val, class C = std::map<Key, Val> >
class MapImplWrapper : public IMap<Key, Val>
{
public:
	MapImplWrapper(C* container)
		: m_container(container)
	{ }

	virtual size_t size() const
	{
		return m_container->size();
	}

	virtual Val& operator[](const Key& key)
	{
		return (*m_container)[key];
	}

	virtual const Val& operator[](const Key& key) const
	{
		return (*m_container)[key];
	}

private:
	C* m_container;
};

//////////////////////////////////////////////////////////////////////////

template<class Key, class Val, class C = std::map<Key, Val> >
class MapImplOwned : public MapImplWrapper<Key, Val, C>
{
public:
	MapImplOwned()
		: MapImplWrapper<Key, Val, C>(&m_container)
	{ }

private:
	C m_container;
};


//////////////////////////////////////////////////////////////////////////

#endif // _CONTAINERS_H__
