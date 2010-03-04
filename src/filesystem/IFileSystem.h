/*========================================================
* IFileSystem.h
* @author Sergey Mikhtonyuk
* @date 19 November 2008
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/

#ifndef _IFILESYSTEM_H__
#define _IFILESYSTEM_H__

#include "module/interfaces.h"
#include "module/intellectual.h"
#include "common/IAdapterFactory.h"
#include "FileSystem_fwd.h"
#include <string>

namespace FileSystem
{

	/// IFileSystem interface
	/** Facade interface from which you begin working 
	 *  with resource handles 
	 *
	 *  @ingroup FileSystem */
	sf_interface IFileSystem : public Module::IUnknown
	{
		sf_uuid("afc9ed7f-1158-48bc-99c1-1853cb0e8c62")

		/// Returns resource by specified path
		virtual Module::com_ptr<IResource> GetResource(const std::string& path, bool searchArchives = false) = 0;

		/// Retrieves current folder
		virtual Module::com_ptr<IFolder> CurrentFolder() = 0;


		/// Used to register adapter factory for the IFile interface
		/** @see IAdapterFactory */
		virtual void RegisterFileAdapterFactory(IAdapterFactory *pFactory) = 0;

		/// Creates file adapter by interface ID
		virtual Module::HResult CreateFileAdapter(IFile* file, SF_RIID uid, void **ppAdapter) = 0;


		/// Returns parent folder of path
		virtual std::string PathGetParentFolder(const char* path) const = 0;
		/// Combines two paths
		virtual std::string PathCombine(const char* path1, const char* path2) const = 0;
		/// Makes full path from relative
		virtual std::string PathGetFull(const char* path) const = 0;
	};
	
} // namespace


#endif // _IFILESYSTEM_H__