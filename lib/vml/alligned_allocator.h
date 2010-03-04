/*========================================================
* alligned_allocator.h
* @author Sergey Mikhtonyuk
* @date 30 April 2009
=========================================================*/
#ifndef _ALLIGNEDALLOCATOR_H__
#define _ALLIGNEDALLOCATOR_H__

#include <xmmintrin.h>

namespace VML
{
	//////////////////////////////////////////////////////////////////////////

	#ifdef _DEBUG
		#define _CHECK_ALIGN(data, allign) assert(reinterpret_cast<size_t>(&data) % allign == 0);
	#endif

	/// Allocates aligned chunk of data
	inline void* aligned_malloc(size_t size, size_t align)
	{
		return _mm_malloc(size, align);
	}

	/// Frees chunk allocated with aligned_malloc
	inline void aligned_free(void* ptr)
	{
		_mm_free(ptr);
	}
	//////////////////////////////////////////////////////////////////////////



	/// Used to allocate objects with strict alignment requirements, such as SSE types
	/** By default alignment is 16 bytes
	 *  
	 *  @ingroup VML_SSE */
	template<typename T>
	class AlignedAllocator
	{
	public:
		//////////////////////////////////////////////////////////////////////////

		static const size_t	align_border = 16;

		//////////////////////////////////////////////////////////////////////////
		
		typedef T*			pointer;
		typedef const T*	const_pointer;
		typedef T&			reference;
		typedef const T&	const_reference;
		typedef T			value_type;
		typedef size_t		size_type;
		typedef ptrdiff_t	difference_type;

		//////////////////////////////////////////////////////////////////////////

		template<typename U> struct rebind 
		{
			typedef AlignedAllocator<U> other;
		};

		//////////////////////////////////////////////////////////////////////////

		AlignedAllocator() throw() {}
		
		AlignedAllocator( const AlignedAllocator& ) throw() {}
		
		template<typename U> 
		AlignedAllocator(const AlignedAllocator<U>&) throw() {}

		//////////////////////////////////////////////////////////////////////////
		
		pointer			address(reference x)		const {return &x;}

		const_pointer	address(const_reference x)	const {return &x;}

		//////////////////////////////////////////////////////////////////////////

		/// Allocates memory for n objects
		pointer allocate( size_type n ) 
		{
			return (pointer)_mm_malloc( n * sizeof( T ), align_border );
		}


		#if defined (COMPILER_MSC)
		/// Required by some Microsoft's STL containers
		char* _Charalloc( size_type size )
		{
			return (char*)aligned_malloc( n * sizeof( T ), align_border );
		}
		#endif


		/// Free memory
		void deallocate( pointer p, size_type ) 
		{
			aligned_free( p );
		}

		/// Largest value for which method allocate might succeed
		size_type max_size() const throw() 
		{
			return ( (~size_t( 0 )) - 128 ) / sizeof( T );
		}

		/// Copy-construct value placed at p.
		void construct( pointer p, const T& value )
		{
			// Placement new
			new ( static_cast<void*>( p ) ) T(value);
		}

		/// Calls destructor of object pointed by p
		void destroy( pointer p ) 
		{
			p->~T();
		}
	};

	//////////////////////////////////////////////////////////////////////////

	/// Void specialization (see ISO C++ Standard section 20.4.1)
	/** @ingroup VML_SSE */
	template<> 
	class AlignedAllocator<void> 
	{
	public:
		typedef void*		pointer;
		typedef const void*	const_pointer;
		typedef void		value_type;
		
		template<typename U>
		struct rebind 
		{
			typedef AlignedAllocator<U> other;
		};
	};

	//////////////////////////////////////////////////////////////////////////

	template<typename T, typename U>
	inline bool operator==( const AlignedAllocator<T>&, const AlignedAllocator<U>& )
	{
		return true;
	}

	template<typename T, typename U>
	inline bool operator!=( const AlignedAllocator<T>&, const AlignedAllocator<U>& ) 
	{
		return false;
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace

#endif	// _ALLIGNEDALLOCATOR_H__