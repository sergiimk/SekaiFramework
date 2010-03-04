/*========================================================
* CArchFolder.h
* @author Sergey Mikhtonyuk
* @date 27 December 2008
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _CARCHFOLDER_H__
#define _CARCHFOLDER_H__

#include "IFolder.h"
#include "module/implementations.h"
#include <boost/filesystem.hpp>

namespace FileSystem
{
	class CArchive;
	class CFileSystem;



	/// Implementation of IFolder interface for folder in archive
	/** @ingroup FileSystem */
	class NOVTABLE CArchFolder : 
		public Module::ComRootObject<Module::MultiThreadModel>,
		public IFolder
	{
		friend class CArchive;
	public:
		DECLARE_IMPLEMENTATION(CArchFolder)

		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(IFolder)
			INTERFACE_ENTRY(IResourceContainer)
			INTERFACE_ENTRY(IResource)
		END_INTERFACE_MAP()

		bool							IsAccessible();
		Module::com_ptr<IResource>	Parent();
		std::string						BaseName();
		const std::string&				FullPath();
		void							Accept(IFSTraverser* traverser);

		const std::vector<IResource*>&	GetChildren();

		IFileSystem*					FileSystem();
		Module::com_ptr<IResource>	FindChild(const std::string &name);

		void				FinalConstruct(	CFileSystem *fs, const boost::filesystem::path &arch, 
											const boost::filesystem::path &path);
		virtual ~CArchFolder();

	protected:
		CFileSystem*			mFileSystem;
		boost::filesystem::path mArchive;
		boost::filesystem::path mPath;
		std::vector<IResource*> mChildren;
	};	


} // namespace

#endif // _CARCHFOLDER_H__