/*========================================================
* IFile.h
* @author Sergey Mikhtonyuk
* @date 19 November 2008
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/

#ifndef _IFILE_H__
#define _IFILE_H__

#include "IResource.h"
#include "FileSystem_fwd.h"
#include <fstream>
#include <boost/function.hpp>


namespace FileSystem
{
	/// IFile interface
	/** Extends IResource with file operations,
	 *  leaf in IResource hierarchy
	 *
	 *  @ingroup FileSystem */
	sf_interface IFile : public IResource
	{
		sf_uuid("131dcbbc-0920-4a2d-a463-1f29fe96fc89")

		/// File system object
		virtual IFileSystem* FileSystem() = 0;

		/// Gets file extension
		virtual const std::string& Extension() = 0;

		/// Returns file stream
		virtual std::fstream& Stream(std::ios_base::openmode mode = std::ios::in) = 0;

		/// Reads all file to dynamically allocated buffer
		virtual void ReadFile(char **ppBuffer, std::ios::streamoff &size) = 0;
	};


} // namespace

#endif // _IFILE_H__
