/*========================================================
* CArchFolder.cpp
* @author Sergey Mikhtonyuk
* @date 27 December 2008
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/

#include "CArchFolder.h"
#include "CArchive.h"
#include "CFileSystem.h"
#include "IFSTraverser.h"
#include <algorithm>

namespace FileSystem
{
	//////////////////////////////////////////////////////////////////////////

	void CArchFolder::FinalConstruct(CFileSystem *fs, const boost::filesystem::path &arch, 
		const boost::filesystem::path &path)
	{
		mArchive = arch;
		mFileSystem = fs;
		mPath = path;
	}

	//////////////////////////////////////////////////////////////////////////

	CArchFolder::~CArchFolder()
	{
		mFileSystem->CloseHandle(mPath.string());

		if(mChildren.size())
			std::for_each(mChildren.begin(), mChildren.end(), boost::mem_fn(&Module::IUnknown::Release));
	}

	//////////////////////////////////////////////////////////////////////////

	std::string CArchFolder::BaseName()
	{
		return mPath.filename();
	}

	//////////////////////////////////////////////////////////////////////////

	const std::string& CArchFolder::FullPath()
	{
		return mPath.string();
	}

	//////////////////////////////////////////////////////////////////////////

	bool CArchFolder::IsAccessible()
	{
		return boost::filesystem::exists(mArchive);
	}

	//////////////////////////////////////////////////////////////////////////

	Module::com_ptr<IResource> CArchFolder::Parent()
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

	IFileSystem* CArchFolder::FileSystem()
	{
		return mFileSystem;
	}

	//////////////////////////////////////////////////////////////////////////

	void CArchFolder::Accept(IFSTraverser* traverser)
	{
		bool con = traverser->VisitFolder(this);
		if(con)
		{
			GetChildren();
			std::for_each(mChildren.begin(), mChildren.end(), 
				std::bind2nd(std::mem_fun(&IResource::Accept), traverser));
		}
		traverser->LeaveFolder(this);
	}

	//////////////////////////////////////////////////////////////////////////

	const std::vector<IResource*>& CArchFolder::GetChildren()
	{
		return mChildren;
	}

	//////////////////////////////////////////////////////////////////////////

	Module::com_ptr<IResource> CArchFolder::FindChild(const std::string &name)
	{
		Module::com_ptr<IResource> ret;

		for(size_t i = 0; i < mChildren.size(); ++i)
		{
			boost::filesystem::path p(mChildren[i]->FullPath());
			if(p.filename() == name)
				ret = mChildren[i];
		}
		return ret;
	}

	//////////////////////////////////////////////////////////////////////////	

} // namespace
