/*========================================================
* directory_iterator.h
* @author Sergey Mikhtonyuk
* @date 21 Mar 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _DIRECTORY_ITERATOR_H__
#define _DIRECTORY_ITERATOR_H__

#include "filesystem_fwd.h"

namespace filesystem
{
	/// Iterates over directory entries
	/** @ingroup filesystem */
	class FILESYSTEM_API directory_iterator
	{
	public:

		directory_iterator(const path& p);

		directory_iterator(const directory_iterator& other);

		~directory_iterator();

		directory_iterator& operator=(const directory_iterator& rhs);

		/// Returns true if iterator is valid, false when reached the end
		operator bool() const;

		/// Step to the next directory entry
		directory_iterator& operator++();

		/// Step to the next directory entry
		directory_iterator operator++(int);

		/// Returns name of current entry
		path current() const;

	private:
		struct directory_iterator_impl;
		directory_iterator_impl* m_impl;
	};
	
} // namespace

#endif //_DIRECTORY_ITERATOR_H__
