/*========================================================
* CFile.h
* @author Sergey Mikhtonyuk
* @date 19 November 2008
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/

#ifndef _CFILE_H__
#define _CFILE_H__

#include "IFile.h"
#include "module/implementations.h"
#include <boost/filesystem.hpp>
#include <fstream>

namespace FileSystem
{
	class CFileSystem;


	/// Implementation of IFile interface
	/** @ingroup FileSystem */
	class NOVTABLE CFile :
		public Module::ComRootObject<Module::MultiThreadModel>,
		public IFile
	{
	public:
		DECLARE_IMPLEMENTATION(CFile)

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

		void FinalConstruct(CFileSystem *fs, const boost::filesystem::path &path);
		virtual ~CFile();

	protected:
		CFileSystem*			mFileSystem;
		boost::filesystem::path mPath;
		std::string				mExtension;
		std::fstream			mFileStream;
	};



} // namespace

#endif // _CFILE_H__
