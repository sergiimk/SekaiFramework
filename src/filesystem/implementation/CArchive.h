/*========================================================
* CArchive.h
* @author Sergey Mikhtonyuk
* @date 21 December 2008
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _CARCHIVE_H__
#define _CARCHIVE_H__

#include "IArchive.h"
#include "CFile.h"
#include "zlib/unzip.h"
#include <vector>

namespace FileSystem
{
	/// Implements both IArchive and IFile interfaces
	/** @ingroup FileSystem */
	class NOVTABLE CArchive : 
		public CFile,
		public IArchive
	{
	public:
		DECLARE_IMPLEMENTATION_DERIVED(CArchive, CFile)
	
		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(IArchive)
			INTERFACE_ENTRY(IResourceContainer)
			INTERFACE_ENTRY_CHAIN(CFile)
		END_INTERFACE_MAP()

		bool							IsAccessible()	{ return CFile::IsAccessible(); }
		Module::com_ptr<IResource>	Parent()		{ return CFile::Parent(); }
		std::string						BaseName()		{ return CFile::BaseName(); }
		const std::string&				FullPath()		{ return CFile::FullPath(); }
		void							Accept(IFSTraverser* traverser);

		const std::vector<IResource*>&	GetChildren();
		Module::com_ptr<IResource>	FindChild(const std::string& name);
		Module::com_ptr<IResource>	FindItem(const std::string& name);

		void							InitItems();
		void							BuildHierarchy(const std::string &fldPath, std::vector<IResource*> &children);
		std::pair<int, int>				GetSubpathBouds(const std::string &base, const std::string &chld);
		virtual ~CArchive();

	protected:
		std::vector<IResource*> mChildren;
		std::vector<IResource*> mItems;
	};


	/*=======================================================================
	=  Guard
	==============*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
	struct ArchiveGuard
	{
		ArchiveGuard(const char *p) : file(unzOpen(p)) { }
		~ArchiveGuard() { unzClose(file); }
		unzFile file;
	};


} // namespace

#endif // _CARCHIVE_H__