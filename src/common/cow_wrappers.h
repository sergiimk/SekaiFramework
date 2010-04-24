/*========================================================
* cow_list.h
* @author Sergey Mikhtonyuk
* @date 21 April 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _COW_LIST_H__
#define _COW_LIST_H__

#include <vector>
#include <memory>

//////////////////////////////////////////////////////////////////////////

// This class holds the array of elements
// and can give out read-only handles to that array.
// Once the handle is given it will hold a snapshot of the list
// with exactly same elements that were in the list at that time
// even if the changes were made to the original list
template<class T>
class cow_wrapper
{
public:
	typedef T type;
	typedef std::shared_ptr<type> shared_type;

	//////////////////////////////////////////////////////////////////////////

	/// Provides read-only access to wrapped object
	class snapshot
	{
	public:
		snapshot(const cow_wrapper<T>& w)
			: m_object(w.m_object)
		{ }

		const type& operator*() const
		{
			return *m_object.get();
		}

		const type* operator->() const
		{
			return m_object.get();
		}

	private:
		shared_type m_object;
	};

	//////////////////////////////////////////////////////////////////////////

	cow_wrapper() 
		: m_object(new type()) 
	{ }

	template<class P1>
	cow_wrapper(P1&& p1) 
		: m_object(new type(std::forward<P1>(p1))) 
	{ }

	template<class P1, class P2>
	cow_wrapper(P1&& p1, P2&& p2) 
		: m_object(new type(std::forward<P1>(p1), std::forward<P2>(p2))) 
	{ }

	template<class P1, class P2, class P3>
	cow_wrapper(P1&& p1, P2&& p2, P3&& p3) 
		: m_object(new type(std::forward<P1>(p1), std::forward<P2>(p2), std::forward<P3>(p3))) 
	{ }

	snapshot get_snapshot() const
	{
		return snapshot(*this);
	}

	type& operator*()
	{
		pre_modify();
		return *m_object.get();
	}

	type* operator->()
	{
		pre_modify();
		return m_object.get();
	}

	const type& operator*() const
	{
		return *m_object.get();
	}

	const type* operator->() const
	{
		return m_object.get();
	}

private:

	void pre_modify()
	{
		if(m_object.unique())
			return;
		type* old = m_object.get();
		m_object.reset(new type(*old));
	}

	shared_type m_object;
};

//////////////////////////////////////////////////////////////////////////

template<class T, class Cont = std::vector<T> >
class cow_container
{
public:
	cow_container() { }
	cow_container(const cow_container& other) : m_wrapper(*other.m_wrapper) { }
	size_t size() const { return m_wrapper->size(); }
private:
	cow_wrapper<Cont> m_wrapper;
};

//////////////////////////////////////////////////////////////////////////

#endif
