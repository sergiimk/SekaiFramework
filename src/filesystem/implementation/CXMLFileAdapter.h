/*========================================================
* CXMLFileAdapter.h
* @author Sergey Mikhtonyuk
* @date 24 November 2008
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _CXMLFILEADAPTER_H__
#define _CXMLFILEADAPTER_H__

#include "IXMLFileAdapter.h"
#include "common/IAdapterFactory.h"
#include "module/implementations.h"
#include "module/intellectual.h"

namespace FileSystem
{
	/// Implementation of XML adapter interface
	/** This is just a wrapper class to integrate TinyXML
	  * into the system 
	  *
	  * @ingroup FileSystem */
	class NOVTABLE CXMLFileAdapter : 
		public Module::ComRootObject<Module::MultiThreadModel>,
		public IXMLFileAdapter
	{
	public:
		DECLARE_IMPLEMENTATION(CXMLFileAdapter)
	
		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(IXMLFileAdapter)
		END_INTERFACE_MAP()

		~CXMLFileAdapter();

		void			FinalConstruct(IFile* pFile);
	
		bool			IsInitialized();
		IFile*			WrappedFile();
		void			Parse();
		TiXmlDocument&	GetDoc();

	protected:
		Module::com_ptr<IFile> mFile;
		TiXmlDocument mDocument;
	};



	/// Adapter factory for IXMLFileAdapter
	/** @ingroup FileSystem */
	class NOVTABLE CXMLFileAdapterFactory : 
		public Module::ComRootObject<>,
		public IAdapterFactory
	{
	public:
		DECLARE_IMPLEMENTATION(CXMLFileAdapterFactory)
	
		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(IAdapterFactory)
		END_INTERFACE_MAP()
	
		Module::GUID**	SourceInterfaceList();
		Module::GUID**	DestInterfaceList();
		Module::HResult	GetAdapter(Module::IUnknown* object, SF_RIID iid, void **ppAdapter);
	};

} // namespace

#endif // _CXMLFILEADAPTER_H__