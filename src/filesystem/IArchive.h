/*========================================================
* IArchive.h
* @author Sergey Mikhtonyuk
* @date 21 December 2008
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _IARCHIVE_H__
#define _IARCHIVE_H__

#include "IResourceContainer.h"
#include "FileSystem_fwd.h"


namespace FileSystem
{
	/// Interface to archive files
	/** Archives are fully transparent, so you can use them as usual folder,
	  * this is also great when you work with resources, you can work
	  * with them stored in a folder or in an archive uniformly, pack and unpack them
	  * without changing the loading code 
	  *
	  * @ingroup FileSystem */
	sf_interface IArchive : public IResourceContainer
	{
		sf_uuid("bc9dcbc4-2a0b-49ba-b242-02e988dd613d")

		/// Returns child with specified name (child is a top level file or folder in archive)
		virtual Module::com_ptr<IResource> FindChild(const std::string& name) = 0;

		/// Returns item with specified name
		virtual Module::com_ptr<IResource> FindItem(const std::string& name) = 0;
	};


} // namespace


#endif // _IARCHIVE_H__