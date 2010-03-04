/*========================================================
* FileSystem.h
* @author Sergey Mikhtonyuk
* @date 19 November 2008
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
/** @defgroup FileSystem FileSystem
 *  Platform-independent file system library */
#ifndef _FILESYSTEM_H__
#define _FILESYSTEM_H__

#include "IFile.h"
#include "IFolder.h"
#include "IArchive.h"
#include "IFileSystem.h"
#include "IXMLFileAdapter.h"
#include "IINIFileAdapter.h"
#include "FSExceptions.h"
#include "IFSTraverser.h"

namespace FileSystem
{
	
	// {64a9d3c2-228c-403d-8711-5ca47d1cb76f} 
	static const Module::GUID CLSID_CFileSystem = 
	{ 0x64a9d3c2, 0x228c, 0x403d, { 0x87, 0x11, 0x5c, 0xa4, 0x7d, 0x1c, 0xb7, 0x6f } };


} // namespace

#endif // _FILESYSTEM_H__
