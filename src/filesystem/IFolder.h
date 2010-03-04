/*========================================================
* IFolder.h
* @author Sergey Mikhtonyuk
* @date 19 November 2008
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/

#ifndef _IFOLDER_H__
#define _IFOLDER_H__

#include "IResourceContainer.h"
#include "FileSystem_fwd.h"

namespace FileSystem
{
	/// Composite interface of file system
	/** @ingroup FileSystem */
	sf_interface IFolder : public IResourceContainer
	{
		sf_uuid("246f0486-5bc5-414e-812c-c0bbec5664fe")

		/// File system object
		virtual IFileSystem* FileSystem() = 0;

		/// Service method for finding the child resource by its name
		virtual Module::com_ptr<IResource> FindChild(const std::string &name) = 0;
	};

} // namespace

#endif // _IFOLDER_H__