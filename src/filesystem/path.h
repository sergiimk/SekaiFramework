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

		//////////////////////////////////////////////////////////////////////////

		enum file_attribute
		{
			fa_directory	= 0x1, /// Object is a directory
			fa_file			= 0x2, /// Object is a file
			fa_hidden		= 0x4, /// File or directory is hidden
			fa_readonly		= 0x8, /// File or directory is read-only
			fa_not_found	= 0x10, /// File was not found
			fa_unknown		= 0x20, /// File type can't be determined
		};

		//////////////////////////////////////////////////////////////////////////

		class iterator;
		friend class iterator;

		/// Empty path ctor
		path();

		/// Initializes path with a string
		path(const char* p);

		/// Copies other path
		path(const path& other);

		/// Constructs path from range
		path(const iterator& begin, const iterator& end);

		/// Assignment
		path& operator=(const path& rhs);

		/// Destructor
		~path();


		/// Checks if path is empty
		bool empty() const;

		/// Returns path size
		size_t size() const;

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


		/// Returns path extension
		const char* extension() const;

		/// Converts path to an absolute
		void absolute();

		/// Converts path to a relative according to current directory
		void relative();

		/// Converts path to a relative according to specified directory
		void relative(const path& dir);

		/** On Unix and Mac OS X the path is unchanged, on case-insensitive 
		  * file systems it converts the path to lowercase. */
		void normcase();

		/// Normalize a path
		/** This collapses redundant separators and up-level references */
		void normpath();

		/// Return the base name of path
		path basename() const;

		/// Return the directory name of path
		path dirname() const;

		/// Cuts the path to range defined by iterators
		void slice(const iterator& begin, const iterator& end);



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

		/// Returns combination of path::file_attribute flags
		int get_attributes() const;



		/// Returns directory iterator
		directory_iterator list_dir() const;



		/// Path separators
		/** First character is always an OS default separator,
		  * it can be followed by any number of alternative separators. */
		static const char* separators();

		/// Returns true if c is an invalid symbol for file name
		static bool is_bad_filename_symbol(char c);

		/// Returns true if c is an invalid symbol for path
		static bool is_bad_path_symbol(char c);

		/// Returns common prefix of two paths
		static path common_prefix(const path& p1, const path& p2);

		/// Returns absolute path to working directory
		/** When possible prefer relative '.' path */
		static path current_dir();

		/// Returns path to directory designated for temporary files
		static path temp_dir();

		/// Generates name for a temporary file
		/** @param p path in which temp file will be located
		  * @param prefix file name prefix (up to 3 chars used on windows) **/
		static path temp_file_name(const path& p, const char* prefix);

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
			bool		operator<(const iterator& rhs) const;
			bool		operator<=(const iterator& rhs) const;
			bool		operator>(const iterator& rhs) const;
			bool		operator>=(const iterator& rhs) const;

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
