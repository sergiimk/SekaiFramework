/*========================================================
* IXMLFileAdapter.h
* @author Sergey Mikhtonyuk
* @date 24 November 2008
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _IXMLFILEADAPTER_H__
#define _IXMLFILEADAPTER_H__

#include "IFile.h"
#include "module/interfaces.h"
#include "tinyxml/tinyxml.h"


namespace FileSystem
{
	/// File adapter interface for XML
	/** @ingroup FileSystem */
	sf_interface IXMLFileAdapter : public Module::IUnknown
	{
		sf_uuid("f4d1c8d7-c45a-4b52-9fe2-9464dcc2d588")

		/// Determines if document is already parsed
		virtual bool IsInitialized() = 0;

		/// Returns the file, wrapped by adapter
		virtual IFile* WrappedFile() = 0;

		/// Returns the root xml element
		virtual TiXmlDocument& GetDoc() = 0;

		/// Initiate the file parsing
		virtual void Parse() = 0;
	};	

} // namespace

#endif // _IXMLFILEADAPTER_H__