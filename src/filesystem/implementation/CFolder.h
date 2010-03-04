/*========================================================
* CFolder.h
* @author Sergey Mikhtonyuk
* @date 19 November 2008
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _CFOLDER_H__
#define _CFOLDER_H__

#include "IFolder.h"
#include "module/implementations.h"
#include <boost/filesystem.hpp>
#include <vector>


namespace FileSystem
{
	class CFileSystem;



	/// Implementation of IFolder interface
	/** Implements composite pattern
	 *  @ingroup FileSystem */
	class NOVTABLE CFolder : 
		public Module::ComRootObject<Module::MultiThreadModel>,
		public IFolder
	{
	public:
		DECLARE_IMPLEMENTATION(CFolder)

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
		
		void FinalConstruct(CFileSystem *fs, const boost::filesystem::path &path);
		virtual ~CFolder();

	protected:
		CFileSystem* mFileSystem;
		boost::filesystem::path mPath;
		std::vector<IResource*> mChildren;
	};	

} // namespace

#endif // _CFOLDER_H__