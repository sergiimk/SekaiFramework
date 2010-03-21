/*========================================================
* stack_container.h
* @author Davydov Max
* @date 24 February 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _STACK_CONTAINER_H___
#define _STACK_CONTAINER_H___

#include <memory>

//////////////////////////////////////////////////////////////////////////

/// Stack based allocator
/** This allocator can be used with STL containers to provide a stack buffer
* from which to allocate memory and overflows onto the heap. This stack buffer
* would be allocated on the stack and allows us to avoid heap operations in
* some situations.
*
* STL likes to make copies of allocators, so the allocator itself can't hold
* the data. Instead, we make the creator responsible for creating a
* StackAllocator::Source which contains the data. Copying the allocator
* merely copies the pointer to this shared source, so all allocators created
* based on our allocator will share the same stack buffer.
*
* This stack buffer implementation is very simple. The first allocation that
* fits in the stack buffer will use the stack buffer. Any subsequent
* allocations will not use the stack buffer, even if there is unused room.
* This makes it appropriate for array-like containers, but the caller should
* be sure to reserve() in the container up to the stack buffer size. Otherwise
* the container will allocate a small array which will "use up" the stack
* buffer.
*
* Based on http://src.chromium.org/svn/trunk/src/base/stack_container.h from Chromium project
*
* @ingroup Common */
template<class T, size_t stack_capacity>
class stack_allocator : public std::allocator<T>
{
public:
	typedef typename std::allocator<T>::pointer pointer;
	typedef typename std::allocator<T>::size_type size_type;

	// Backing store for the allocator. The container owner is responsible for
	// maintaining this for as long as any containers using this allocator are
	// live.
	struct Source
	{
		Source() : m_isStackBufferUsed(false)
		{ }

		// Casts the buffer in its right type.
		T* stack_buffer()
		{
			return reinterpret_cast<T*>(m_stackBuffer);
		}

		const T* stack_buffer() const
		{
			return reinterpret_cast<const T*>(m_stackBuffer);
		}


		//
		// IMPORTANT: Take care to ensure that stack_buffer_ is aligned
		// since it is used to mimic an array of T.
		// Be careful while declaring any unaligned types (like bool)
		// before m_stackBuffer.
		//

		// The buffer itself. It is not of type T because we don't want the
		// constructors and destructors to be automatically called. Define a POD
		// buffer of the right size instead.
		char m_stackBuffer[sizeof(T[stack_capacity])];

		// Set when the stack buffer is used for an allocation. We do not track
		// how much of the buffer is used, only that somebody is using it.
		bool m_isStackBufferUsed;
	};


	// Used by containers when they want to refer to an allocator of type U.
	template<class U>
	struct rebind
	{
		typedef stack_allocator<U, stack_capacity> other;
	};


	// For the straight up copy c-tor, we can share storage.
	stack_allocator(const stack_allocator<T, stack_capacity>& rhs)
		: std::allocator<T>(), m_source(rhs.m_source)
	{ }

	// ISO C++ requires the following constructor to be defined,
	// and std::vector in VC++2008SP1 Release fails with an error
	// in the class _Container_base_aux_alloc_real (from <xutility>)
	// if the constructor does not exist.
	// For this constructor, we cannot share storage; there's
	// no guarantee that the Source buffer of Ts is large enough
	// for Us.
	// TODO: If we were fancy pants, perhaps we could share storage
	// iff sizeof(T) == sizeof(U).
	template<class U, size_t other_capacity>
	stack_allocator(const stack_allocator<U, other_capacity>& other)
		: m_source(NULL)
	{ }

	// Empty ctor to fix build bug in GCC
	stack_allocator() 
		: m_source(NULL)
	{ }

	// Main ctor
	explicit stack_allocator(Source* source) : m_source(source)
	{ }


	// Actually do the allocation. Use the stack buffer if nobody has used it yet
	// and the size requested fits. Otherwise, fall through to the standard allocator.
	pointer allocate(size_type n, void* hint = 0)
	{
		if (m_source != NULL && !m_source->m_isStackBufferUsed
			&& n <= stack_capacity) {
				m_source->m_isStackBufferUsed = true;
				return m_source->stack_buffer();
		}
		else
		{
			return std::allocator<T>::allocate(n, hint);
		}
	}

	// Free: when trying to free the stack buffer, just mark it as free. For
	// non-stack-buffer pointers, just fall though to the standard allocator.
	void deallocate(pointer p, size_type n)
	{
		if (m_source != NULL && p == m_source->stack_buffer())
			m_source->m_isStackBufferUsed = false;
		else
			std::allocator<T>::deallocate(p, n);
	}

	// Is true, if allocator currently uses stack
	bool isOnStack() const
	{
		if(m_source == NULL)
			return false;

		return m_source->m_isStackBufferUsed;
	}

private:
	Source* m_source;
};

//////////////////////////////////////////////////////////////////////////

/// Internal stack based container wrapper for vector and other containers except strings
/** A wrapper around STL containers that maintains a stack-sized buffer that the
  * initial capacity of the vector (or other container) is based on.
  * Growing the container beyond the stack capacity will transparently overflow onto the heap.
  * The container must support reserve().
  * WATCH OUT: container should not try to reserve more space at initial reserve() than
  * specified with stack_capacity (like basic_string does), that will cause on-heap allocation.

  * WATCH OUT: the ContainerType MUST use the proper stack_allocator for this
  * type. This object is really intended to be used only internally. You'll want
  * to use the wrappers below for different types.
  *
  * @ingroup Common */
template<typename TContainerType, size_t stack_capacity>
class stack_container
{
public:
	typedef TContainerType ContainerType;
	typedef typename ContainerType::value_type ContainedType;
	typedef stack_allocator<ContainedType, stack_capacity> Allocator;

	// Allocator must be constructed before the container!
	stack_container() : m_allocator(&m_stackSource), m_container(m_allocator)
	{
		// Make the container use the stack allocation by reserving our buffer size
		// before doing anything else.
		m_container.reserve(stack_capacity);
	}

	// Getters for the actual container.
	//
	// Danger: any copies of this made using the copy constructor must have
	// shorter lifetimes than the source. The copy will share the same allocator
	// and therefore the same stack buffer as the original. Use std::copy to
	// copy into a "real" container for longer-lived objects.
	ContainerType& container() { return m_container; }
	const ContainerType& container() const { return m_container; }

	// Is true, if container is currently on stack
	bool isOnStack() const
	{
		return m_allocator.isOnStack();
	}

	// Support operator-> to get to the container. This allows nicer syntax like:
	//   StackContainer<...> foo;
	//   std::sort(foo->begin(), foo->end());
	ContainerType* operator->() { return &m_container; }
	const ContainerType* operator->() const { return &m_container; }
	ContainerType& operator*() { return m_container; }
	const ContainerType& operator*() const { return m_container; }

protected:
	// Allocator must be constructed before the container!
	stack_container(size_t resrved_capacity) : m_allocator(&m_stackSource), m_container(m_allocator)
	{
		// Make the container use the stack allocation by reserving our buffer size
		// before doing anything else.
		m_container.reserve(resrved_capacity);
	}

	typename Allocator::Source m_stackSource;
	Allocator m_allocator;
	ContainerType m_container;

private:
	/// disallow copy ctor and operator=
	stack_container(const stack_container&);
	const stack_container& operator=(const stack_container&);
};

//////////////////////////////////////////////////////////////////////////

/// Internal stack based container wrapper for strings
/** A wrapper around STL containers that maintains a stack-sized buffer that the
  * initial capacity of the string is based on. Growing the container beyond the
  * stack capacity will transparently overflow onto the heap. The container must
  * support reserve().
  * Reservs enough space to hold string of stack_capacity size and trailing 0 char

  * WATCH OUT: the ContainerType MUST use the proper stack_allocator for this
  * type. This object is really intended to be used only internally. You'll want
  * to use the wrappers below for different types.
  *
  * @ingroup Common */
template<class TContainerType, size_t stack_capacity, size_t reserved_capacity>
class stack_string_container : public stack_container<TContainerType, stack_capacity>
{
public:
	// Allocator must be constructed before the container!
	stack_string_container() : stack_container<TContainerType, stack_capacity>(reserved_capacity)
	{
	}

private:
	// disallow copy ctor and operator=
	stack_string_container(const stack_string_container&);
	const stack_string_container& operator=(const stack_string_container&);
};

//////////////////////////////////////////////////////////////////////////

#endif // _STACK_CONTAINER_H___
