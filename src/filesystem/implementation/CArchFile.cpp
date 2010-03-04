/*========================================================
* CArchFile.cpp
* @author Sergey Mikhtonyuk
* @date 21 December 2008
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/

#include "CArchFile.h"
#include "CArchive.h"
#include "CFileSystem.h"
#include "IFSTraverser.h"

namespace FileSystem
{
	//////////////////////////////////////////////////////////////////////////

	void CArchFile::FinalConstruct(CFileSystem *fs, const boost::filesystem::path &arch,
		const boost::filesystem::path &path, unsigned long offset)
	{
		mFileSystem = fs;
		mArchive = arch;
		mPath = path;
		mExtension =  boost::filesystem::extension(mPath);
		mOffset = offset;
	}

	//////////////////////////////////////////////////////////////////////////

	CArchFile::~CArchFile()
	{
		mFileSystem->CloseHandle(mPath.string());
	}

	//////////////////////////////////////////////////////////////////////////

	Module::com_ptr<IResource> CArchFile::Parent()
	{
		Module::com_ptr<IResource> ret;

		/// \todo improve logic of "has parent" check
		if(mPath.has_parent_path())
		{
			boost::filesystem::path pp = mPath.parent_path();
			if(pp.string()[pp.string().length() - 1] != ':')
				mFileSystem->GetResource(pp, ret.wrapped());
		}
		return ret;
	}

	//////////////////////////////////////////////////////////////////////////

	bool CArchFile::IsAccessible()
	{
		return true;
	}

	//////////////////////////////////////////////////////////////////////////

	IFileSystem* CArchFile::FileSystem()
	{
		return mFileSystem;
	}

	//////////////////////////////////////////////////////////////////////////

	std::string CArchFile::BaseName()
	{
		return mPath.filename();
	}

	//////////////////////////////////////////////////////////////////////////

	const std::string& CArchFile::FullPath()
	{
		return mPath.string();
	}

	//////////////////////////////////////////////////////////////////////////

	void CArchFile::Accept(IFSTraverser* traverser)
	{
		traverser->VisitFile(this);
	}

	//////////////////////////////////////////////////////////////////////////

	const std::string& CArchFile::Extension()
	{
		return mExtension;
	}

	//////////////////////////////////////////////////////////////////////////

	std::fstream& CArchFile::Stream(std::ios_base::openmode mode)
	{
		throw 1;
		//ASSERT(IsAccessible())
		//return std::fstream(FullPath().c_str(), mode);
	}

	// This non-member function is used to prevent async reading on deleted file handle
	static void ReadFile_Exec(unsigned long offset, const std::string &arch, char **ppBuffer, std::ios::streamoff &size)
	{
		*ppBuffer = 0; size = 0;
		ArchiveGuard g(arch.c_str());

		if(unzSetOffset(g.file, offset) != UNZ_OK) return;

		unz_file_info fi;
		if(unzGetCurrentFileInfo(g.file, &fi, 0, 0, 0, 0, 0, 0) != UNZ_OK) return;
		*ppBuffer = new char[size = fi.uncompressed_size];

		if(unzOpenCurrentFile(g.file) != UNZ_OK) return;
		unzReadCurrentFile(g.file, *ppBuffer, fi.uncompressed_size);
		unzCloseCurrentFile(g.file);
	}

	//////////////////////////////////////////////////////////////////////////

	void CArchFile::ReadFile(char **ppBuffer, std::ios::streamoff &size)
	{
		ReadFile_Exec(mOffset, mArchive.string(), ppBuffer, size);
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace
