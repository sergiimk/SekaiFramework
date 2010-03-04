/*========================================================
* IResourceContainer.h
* @author Sergey Mikhtonyuk
* @date 19 November 2008
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/

#ifndef _IRESOURCECONTAINER_H__
#define _IRESOURCECONTAINER_H__

#include "IResource.h"
#include <vector>

namespace FileSystem
{

	/// IResourceContainer interface
	/** Composite class of IResource hierarchy
	 *  @ingroup  FileSystem */
	sf_interface IResourceContainer : public IResource
	{
		sf_uuid("3a52847a-c631-4309-ab37-58c1819d62b9")

		/// Retrieves null-terminated list of child resources
		virtual const std::vector<IResource*>& GetChildren() = 0;
	};


} // namespace

#endif // _IRESOURCECONTAINER_H__