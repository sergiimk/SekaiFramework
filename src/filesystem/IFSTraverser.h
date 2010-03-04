/*========================================================
* IFSTraverser.h
* @author Sergey Mikhtonyuk
* @date 03 May 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _IFSTRAVERSER_H__
#define _IFSTRAVERSER_H__


namespace FileSystem
{
	//////////////////////////////////////////////////////////////////////////
	struct IFolder;
	struct IFile;
	struct IArchive;
	//////////////////////////////////////////////////////////////////////////


	/// Eases the operations with tree structure of file system
	/** @ingroup FileSystem */
	sf_interface IFSTraverser
	{
		/// Called on enter to folder
		/** @return false if you want to stop traversing this branch */
		virtual bool VisitFolder(IFolder* fld) = 0;

		/// Allows depth-first traversing
		virtual void LeaveFolder(IFolder* fld) = 0;

		/// Called on enter to archive
		/** @return false if you want to stop traversing this branch */
		virtual bool VisitArchive(IArchive* arch) = 0;

		/// Allows depth-first traversing
		virtual void LeaveArchive(IArchive* arch) = 0;

		/// Called to process the file
		virtual void VisitFile(IFile* file) = 0;
	};

} // namespace

#endif	// _IFSTRAVERSER_H__