/*========================================================
* IResource.h
* @author Sergey Mikhtonyuk
* @date 19 November 2008
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/

#ifndef _IRESOURCE_H__
#define _IRESOURCE_H__

#include "module/interfaces.h"
#include "module/intellectual.h"
#include "FileSystem_fwd.h"
#include <string>


namespace FileSystem
{
	/// IResource interface
	/** Base interface for all resources 
	 *  @ingroup  FileSystem */
	sf_interface IResource : Module::IUnknown
	{
		sf_uuid("b072a13c-3298-4a19-ac48-946bbbe05873")

		/// Returns parent resource
		virtual Module::com_ptr<IResource> Parent() = 0;

		/// Returns base name of resource (like file or folder name without preceding path)
		virtual std::string BaseName() = 0;
		
		/// Returns full resource path, paths are persistent between the sessions
		virtual const std::string& FullPath() = 0;

		/// Determines if this resource is accessible and you can perform complex operations on it
		virtual bool IsAccessible() = 0;

		/// Pass traverser through resource tree
		virtual void Accept(IFSTraverser* traverser) = 0;
	};	

} // namespace

#endif // _IRESOURCE_H__