/*========================================================
* path.h
* @author Sergey Mikhtonyuk
* @date 20 Mar 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _SF_PATH_H__
#define _SF_PATH_H__

#include "filesystem_fwd.h"
#include <iosfwd>

namespace filesystem
{

	/// Performs path operations in platform independent manner
	/** Path object can be directly used in pimpl configuration
	  * or will be used indirectly by filesystem service in other 
	  * configuration types.
	  *
	  * @ingroup FileSystem */
	class FILESYSTEM_API path
	{
	public:

		class iterator;
		friend class iterator;

		/// Empty path ctor
		path();

		/// Initializes path with a string
		path(const char* p);

		/// Copies other path
		path(const path& other);

		/// Assignment
		path& operator=(const path& rhs);

		/// Destructor
		~path();


		/// C-string representation
		const char* c_str() const;

		/// Iterator to first path element
		iterator begin() const;

		/// Iterator to one after last path element
		iterator end() const;


		
		/// Joins path
		path operator+(const path& rhs) const;

		/// Joins path
		path& operator+=(const path& rhs);

		/// Same as the dirname()
		path& operator--();

		/// Same as the dirname()
		path operator--(int);

		/// Compare paths for equality
		bool operator==(const path& rhs) const;

		/// Compare paths for non equality
		bool operator!=(const path& rhs) const;



		/// Converts path to an absolute
		void absolute();

		/// Converts path to a relative according to current directory
		void relative();

		/// Converts path to a relative according to specified directory
		void relative(const path& dir);

		/** On Unix and Mac OS X the path is unchanged, on case-insensitive 
		  * file systems it converts the path to lowercase. */
		void normcase();

		/// Normalize a pathname
		/** This collapses redundant separators and up-level references.
		  * Also can change meaning of the path that contains symbolic links */
		void normpath();

		/// Return the base name of pathname path
		path basename() const;

		/// Return the directory name of pathname path
		path dirname() const;



		/// Return true if path refers to an existing path
		bool exists() const;

		/// Checks if path is absolute
		bool is_absolute() const;

		/// Return true if path is an existing file, follows symbolic links
		bool is_file() const;
		
		/// Return true if path is an existing directory, follows symbolic links
		bool is_directory() const;

		/// Return true if path refers to a directory entry that is a symbolic link
		bool is_link() const;



		/// Returns directory iterator
		directory_iterator list_dir() const;



		/// Path separators
		/** First character is always an OS default separator,
		  * it can be followed by any number of alternative separators. */
		static const char* separators();

		/// Returns string that contains symbols that cannot be used in directory and path names
		static const char* invalid_symbols();

		/// Returns absolute path to working directory
		/** When possible prefer relative '.' path */
		static path current_dir();

		/// Expands user home directory
		/** On Unix and Windows, return the argument with an initial 
		  * component of ~ or ~user replaced by that user‘s home directory.
		  * 
		  * On Unix, an initial ~ is replaced by the environment variable 
		  * HOME if it is set; otherwise the current user’s home directory 
		  * is looked up in the password directory through the built-in module pwd.
		  * An initial ~user is looked up directly in the password directory.
		  * 
		  * On Windows, HOME and USERPROFILE will be used if set, otherwise a 
		  * combination of HOMEPATH and HOMEDRIVE will be used. 
		  * An initial ~user is handled by stripping the last directory component 
		  * from the created user path derived above. */
		static path expanduser(const char* usr);

		/// path iterator
		/// \todo make stl-compliant
		class FILESYSTEM_API iterator
		{
		public:
			friend class path;

			iterator(const iterator& other);
			~iterator();

			iterator&	operator=(const iterator& rhs);
			iterator&	operator++();
			iterator	operator++(int);
			iterator&	operator--();
			iterator	operator--(int);
			operator	bool() const;
			bool		operator==(const iterator& rhs) const;
			bool		operator!=(const iterator& rhs) const;

			const char* element() const;

		private:
			iterator(const path& parent, size_t position);
			
			struct iterator_impl;
			iterator_impl* m_impl;
		};

	private:
		struct path_impl;
		path_impl* m_impl;
	};

	//////////////////////////////////////////////////////////////////////////

	FILESYSTEM_API std::ostream& operator<<(std::ostream& os, const path& p);

	FILESYSTEM_API std::istream& operator>>(std::istream& is, path& p);

	//////////////////////////////////////////////////////////////////////////
	
} // namespace

#endif //_SF_PATH_H__
