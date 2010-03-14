/*========================================================
* CFile.cpp
* @author Sergey Mikhtonyuk
* @date 19 November 2008
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/

#include "CFile.h"
#include "IFolder.h"
#include "CFileSystem.h"
#include "IFSTraverser.h"
#include <boost/bind.hpp>
#include "module/intellectual.h"


namespace FileSystem
{
	//////////////////////////////////////////////////////////////////////////

	void CFile::FinalConstruct(CFileSystem *fs, const boost::filesystem::path &path)
	{
		mFileSystem = fs;
		mPath = path;
		mExtension =  boost::filesystem::extension(mPath);
	}

	//////////////////////////////////////////////////////////////////////////

	CFile::~CFile()
	{
		mFileSystem->CloseHandle(mPath.string());
	}

	//////////////////////////////////////////////////////////////////////////

	Module::com_ptr<IResource> CFile::Parent()
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

	bool CFile::IsAccessible()
	{
		return boost::filesystem::exists(mPath);
	}

	//////////////////////////////////////////////////////////////////////////

	IFileSystem* CFile::FileSystem()
	{
		return mFileSystem;
	}

	//////////////////////////////////////////////////////////////////////////

	std::string CFile::BaseName()
	{
		return mPath.filename();
	}

	//////////////////////////////////////////////////////////////////////////

	const std::string& CFile::FullPath()
	{
		return mPath.string();
	}

	//////////////////////////////////////////////////////////////////////////

	void CFile::Accept(IFSTraverser* traverser)
	{
		traverser->VisitFile(this);
	}

	//////////////////////////////////////////////////////////////////////////

	const std::string& CFile::Extension()
	{
		return mExtension;
	}

	//////////////////////////////////////////////////////////////////////////

	std::fstream& CFile::Stream(std::ios_base::openmode mode)
	{
		assert(IsAccessible());
		assert(!mFileStream.is_open());
		mFileStream.open(FullPath().c_str(), mode);
		return mFileStream;
	}

	//////////////////////////////////////////////////////////////////////////

	// This non-member function is used to prevent async reading on deleted file handle
	static void ReadFile_Exec(const std::string& filename, char **ppBuffer, std::ios::streamoff &size)
	{
		std::fstream fs(filename.c_str(), std::ios::in | std::ios::ate);
		if(!fs.is_open()) { *ppBuffer = 0; return; }

		size = fs.tellg();
		fs.seekg(0, std::ios::beg);

		*ppBuffer = new char[(size_t)size];
		fs.read(*ppBuffer, size);
	}

	//////////////////////////////////////////////////////////////////////////

	void CFile::ReadFile(char **ppBuffer, std::ios::streamoff &size)
	{
		ReadFile_Exec(FullPath(), ppBuffer, size);
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace
