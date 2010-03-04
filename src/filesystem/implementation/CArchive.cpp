/*========================================================
* CArchive.cpp
* @author Sergey Mikhtonyuk
* @date 21 December 2008
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/

#include "CArchive.h"
#include "CArchFolder.h"
#include "CArchFile.h"
#include "CFileSystem.h"
#include "IFSTraverser.h"
#include "module/intellectual.h"
#include <algorithm>

namespace FileSystem
{
	//////////////////////////////////////////////////////////////////////////

	CArchive::~CArchive()
	{
		if(mChildren.size())
			std::for_each(mChildren.begin(), mChildren.end(), boost::mem_fn(&Module::IUnknown::Release));

		if(mItems.size())
			std::for_each(mItems.begin(), mItems.end(), boost::mem_fn(&Module::IUnknown::Release));
	}

	//////////////////////////////////////////////////////////////////////////

	void CArchive::Accept(IFSTraverser* traverser)
	{
		bool con = traverser->VisitArchive(this);
		if(con)
		{
			GetChildren();
			std::for_each(mChildren.begin(), mChildren.end(), std::bind2nd(std::mem_fun(&IResource::Accept), traverser));
		}
		traverser->LeaveArchive(this);
	}

	//////////////////////////////////////////////////////////////////////////

	const std::vector<IResource*>& CArchive::GetChildren()
	{
		if(!mChildren.size())
		{
			InitItems();
			BuildHierarchy(mPath.string(), mChildren);
		}
		return mChildren;
	}

	//////////////////////////////////////////////////////////////////////////

	Module::com_ptr<IResource> CArchive::FindChild(const std::string &name)
	{
		Module::com_ptr<IResource> ret;

		GetChildren();
		for(size_t i = 0; i < mChildren.size(); ++i)
		{
			boost::filesystem::path p(mChildren[i]->FullPath());
			if(p.filename() == name)
				ret = mChildren[i];
		}
		return ret;
	}

	//////////////////////////////////////////////////////////////////////////

	Module::com_ptr<IResource> CArchive::FindItem(const std::string &name)
	{
		Module::com_ptr<IResource> ret;

		GetChildren();
		for(size_t i = 0; i < mItems.size(); ++i)
		{
			std::string sp = mItems[i]->FullPath().substr(mPath.string().size() + 1);
			if(sp == name)
				ret = mItems[i];
		}
		return ret;
	}

	//////////////////////////////////////////////////////////////////////////

	void CArchive::InitItems()
	{
		// Loading archive info
		ArchiveGuard arch(mPath.string().c_str());
		unz_global_info gi;
		unzGetGlobalInfo(arch.file, &gi);

		// Reserving space for items
		mItems.reserve(gi.number_entry);

		if(unzGoToFirstFile(arch.file) != UNZ_OK) return;
		unz_file_info fi;
		std::vector<char> fnbuf(100);

		// Iterating through children and creating resource wrappers
		do
		{
			// Getting resource info
			unzGetCurrentFileInfo(arch.file, &fi, &fnbuf[0], (unsigned long)(fnbuf.size() - 1), 0, 0, 0, 0);
			if(fi.size_filename >= (fnbuf.size() - 1))
			{
				fnbuf.resize(fi.size_filename + 50);
				unzGetCurrentFileInfo(arch.file, &fi, &fnbuf[0], (unsigned long)(fnbuf.size() - 1), 0, 0, 0, 0);
			}


			// Forming name and path
			bool isFolder = fnbuf[fi.size_filename - 1] == '/';
			if(isFolder)
				fnbuf[fi.size_filename - 1] = 0;

			std::string itName(&fnbuf[0]);
			boost::filesystem::path p(mPath);
			p /= boost::filesystem::path(itName);

			IResource* loaded;
			mFileSystem->TryGetResource(p, &loaded);


			if(!loaded)
			{
				// Resolving file or folder
				if(isFolder)
				{
					CArchFolder* fld;
					create_instance_impl<CArchFolder>(&fld);
					fld->FinalConstruct(mFileSystem, mPath, p);
					loaded = fld;
				}
				else
				{
					CArchFile* file;
					create_instance_impl<CArchFile>(&file);
					file->FinalConstruct(mFileSystem, mPath, p, unzGetOffset(arch.file));
					loaded = file;
				}
				mFileSystem->AddHandle(p.string(), loaded);
			}

			// Ref count == 1 now
			mItems.push_back(loaded);
		}
		while(unzGoToNextFile(arch.file) != UNZ_END_OF_LIST_OF_FILE);

	}

	//////////////////////////////////////////////////////////////////////////

	// Recursively builds hierarchy of items inside the archive
	void CArchive::BuildHierarchy(const std::string &fldPath, std::vector<IResource*> &children)
	{
		for(size_t i = 0; i != mItems.size(); ++i)
		{
			const std::string& fullpath = mItems[i]->FullPath();

			if(fullpath.size() <= fldPath.size())
				continue;

			std::pair<int, int> p = GetSubpathBouds(fldPath, fullpath);

			if(p.second < p.first)
				continue;

			bool top = true;
			for(int j = p.first; j != p.second; ++j)
				if(fullpath[j] == '/')
					top = false;

			if(top)
			{
				// Adding top-level child
				mItems[i]->AddRef();
				children.push_back(mItems[i]);

				// If it is folder - recursion
				if(Module::com_ptr<IFolder> f = mItems[i])
					BuildHierarchy(fullpath, static_cast<CArchFolder*>(mItems[i])->mChildren);
			}
		}
	}

	//////////////////////////////////////////////////////////////////////////

	std::pair<int, int> CArchive::GetSubpathBouds(const std::string &base, const std::string &chld)
	{
		if(base.end() != std::mismatch(base.begin(), base.end(), chld.begin()).first)
			return std::make_pair(0, -1);

		return std::make_pair((int)base.size() + 1, (int)chld.size());
	}

} // namespace
