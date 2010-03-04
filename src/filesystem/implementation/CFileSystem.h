/*========================================================
* CFileSystem.h
* @author Sergey Mikhtonyuk
* @date 19 November 2008
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/

#ifndef _CFILESYSTEM_H__
#define _CFILESYSTEM_H__

#include "IFileSystem.h"
#include "module/implementations.h"
#include "common/AdapterFactoyContainer.h"
#include "common/stringutils.h"
#include "platform/hash_map.h"
#include <boost/filesystem.hpp>


namespace FileSystem
{
	struct IArchive;


	/// Implementation of IFileSystem interface
	/** Facade class that executes operation on resources
	 *  @ingroup FileSystem */
	class NOVTABLE CFileSystem :
		public Module::ComRootObject<Module::MultiThreadModel>,
		public IFileSystem
	{
	public:
		DECLARE_IMPLEMENTATION2(CFileSystem, Module::ComClassFactorySingleton)

		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(IFileSystem)
		END_INTERFACE_MAP()

		CFileSystem();
		virtual ~CFileSystem();

		// ------------------- IFileSystem members -----------------------
		Module::com_ptr<IFolder>		CurrentFolder();
		Module::com_ptr<IResource>	GetResource(const std::string& path, bool searchArchives);

		void				RegisterFileAdapterFactory(IAdapterFactory *pFactory);
		Module::HResult		CreateFileAdapter(IFile* file, SF_RIID uid, void **ppAdapter);

		std::string			PathGetParentFolder(const char* path) const;
		std::string			PathCombine(const char* path1, const char* path2) const;
		std::string			PathGetFull(const char* path) const;

		//----------------------------------------------------------------

		void		AddHandle(const std::string &path, IResource* res);
		void		GetResource(const std::string& path, IResource** ppRes);
		void		GetResource(const boost::filesystem::path &path, IResource** ppRes);
		void		TryGetResource(const boost::filesystem::path &path, IResource** ppRes);

		void		CreateFileHandle(const boost::filesystem::path &path, IFile** ppFile);
		void		CreateFolderHandle(const boost::filesystem::path &path, IFolder** ppFolder);
		void		CreateArchiveHandle(const boost::filesystem::path &path, IArchive** ppArchive);
		void		CloseHandle(const std::string &path);

	protected:
		typedef std::hash_map<std::string, IResource*, str_hash> TResourceMap;

		TResourceMap			mResourceMap;
		AdapterFactoyContainer	mFileAdapterContainer;
	};


} // namespace

#endif // _CFILESYSTEM_H__
