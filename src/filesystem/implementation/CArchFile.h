/*========================================================
* CArchFile.h
* @author Sergey Mikhtonyuk
* @date 21 December 2008
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _CARCHFILE_H__
#define _CARCHFILE_H__

#include "IFile.h"
#include "module/implementations.h"
#include <boost/filesystem.hpp>

namespace FileSystem
{
	class CArchive;
	class CFileSystem;



	/// Implementation of IFile interface for file in archive
	/** @ingroup FileSystem */
	class NOVTABLE CArchFile :
		public Module::ComRootObject<Module::MultiThreadModel>,
		public IFile
	{
	public:
		DECLARE_IMPLEMENTATION(CArchFile)

		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(IFile)
			INTERFACE_ENTRY(IResource)
		END_INTERFACE_MAP()

		bool							IsAccessible();
		Module::com_ptr<IResource>	Parent();
		std::string						BaseName();
		const std::string&				FullPath();
		void							Accept(IFSTraverser* traverser);

		IFileSystem*					FileSystem();
		const std::string&				Extension();
		std::fstream&					Stream(std::ios_base::openmode mode);
		void							ReadFile(char **ppBuffer, std::ios::streamoff &size);

		void				FinalConstruct(	CFileSystem *fs, const boost::filesystem::path &arch,
											const boost::filesystem::path &path, unsigned long offset);

		virtual ~CArchFile();

	protected:
		unsigned long			mOffset;
		std::string				mExtension;
		boost::filesystem::path mPath;
		boost::filesystem::path mArchive;
		CFileSystem*			mFileSystem;
	};

} // namespace

#endif // _CARCHFILE_H__
