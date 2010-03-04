/*========================================================
* CFolder.cpp
* @author Sergey Mikhtonyuk
* @date 19 November 2008
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/

//#include "Logging/ILogger.h"
#include "CFolder.h"
#include "CFileSystem.h"
#include "IFSTraverser.h"
#include <algorithm>
#include <boost/mem_fn.hpp>

namespace  FileSystem
{
	//////////////////////////////////////////////////////////////////////////

	void CFolder::FinalConstruct(CFileSystem *fs, const boost::filesystem::path &path)
	{
		mFileSystem = fs;
		mPath = path;
	}

	//////////////////////////////////////////////////////////////////////////

	CFolder::~CFolder()
	{
		mFileSystem->CloseHandle(mPath.string());
		if(mChildren.size())
			std::for_each(mChildren.begin(), mChildren.end(), boost::mem_fn(&Module::IUnknown::Release));
	}

	//////////////////////////////////////////////////////////////////////////

	std::string CFolder::BaseName()
	{
		return mPath.filename();
	}

	//////////////////////////////////////////////////////////////////////////

	const std::string& CFolder::FullPath()
	{
		return mPath.string();
	}

	//////////////////////////////////////////////////////////////////////////

	bool CFolder::IsAccessible()
	{
		return boost::filesystem::exists(mPath);
	}

	//////////////////////////////////////////////////////////////////////////

	Module::com_ptr<IResource> CFolder::Parent()
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

	void CFolder::Accept(IFSTraverser* traverser)
	{
		bool con = traverser->VisitFolder(this);
		if(con)
		{
			GetChildren();
			std::for_each(mChildren.begin(), mChildren.end(), std::bind2nd(std::mem_fun(&IResource::Accept), traverser));
		}
		traverser->LeaveFolder(this);
	}

	//////////////////////////////////////////////////////////////////////////

	IFileSystem* CFolder::FileSystem()
	{
		return mFileSystem;
	}

	//////////////////////////////////////////////////////////////////////////

	const std::vector<IResource*>& CFolder::GetChildren()
	{
		if(!mChildren.size())
		{
			boost::filesystem::directory_iterator it(mPath), end_iter;

			while(it != end_iter)
			{
				IResource *pResource;
				mFileSystem->GetResource(it->path(), &pResource);

				if(!pResource)
				{
					//LogWarningAlways("Can't load folders child: %s", it->path().string().c_str());
					++it;
					continue;
				}

				// Folder caches it's children
				mChildren.push_back(pResource);
				++it;
			}
		}
		return mChildren;
	}

	//////////////////////////////////////////////////////////////////////////

	Module::com_ptr<IResource> CFolder::FindChild(const std::string &name)
	{
		Module::com_ptr<IResource> chld;
		GetChildren();
		for(size_t i = 0; i < mChildren.size(); ++i)
		{
			boost::filesystem::path p(mChildren[i]->FullPath());
			if(p.filename() == name)
				chld = mChildren[i];
		}
		return chld;
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace
