/*========================================================
* IINIFileAdapter.h
* @author Sergey Mikhtonyuk
* @date 24 November 2008
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _IINIFILEADAPTER_H__
#define _IINIFILEADAPTER_H__

#include "IFile.h"
#include "module/interfaces.h"
#include "tinyxml/tinyxml.h"
#include <map>

namespace FileSystem
{
	/// File adapter interface for INI
	/** @ingroup FileSystem */
	sf_interface IINIFileAdapter : public Module::IUnknown
	{
		sf_uuid("5d64c487-1787-4603-8553-ae05485ba236")

		typedef std::map<std::string, std::string> TSection;
		typedef std::map<std::string, TSection*> TFileMap;

		/// Determines if document is already parsed
		virtual bool IsInitialized() = 0;

		/// Returns the file, wrapped by adapter
		virtual IFile* WrappedFile() = 0;

		/// Returns the INI-file map
		virtual TFileMap& FileMap() = 0;

		/// Initiate the file parsing
		virtual void Parse() = 0;
	};	

} // namespace

#endif // _IINIFILEADAPTER_H__