/*========================================================
* CXMLFileAdapter.cpp
* @author Sergey Mikhtonyuk
* @date 24 November 2008
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/

#include "CXMLFileAdapter.h"
#include "IFileSystem.h"
#include <fstream>

namespace FileSystem
{
	//////////////////////////////////////////////////////////////////////////

	void CXMLFileAdapter::FinalConstruct(IFile *pFile)
	{
		mFile = pFile;
	}

	//////////////////////////////////////////////////////////////////////////

	CXMLFileAdapter::~CXMLFileAdapter()
	{
	}

	//////////////////////////////////////////////////////////////////////////

	bool CXMLFileAdapter::IsInitialized()
	{
		return mDocument.FirstChild() != 0;
	}

	//////////////////////////////////////////////////////////////////////////

	IFile* CXMLFileAdapter::WrappedFile()
	{
		return mFile;
	}

	//////////////////////////////////////////////////////////////////////////

	void CXMLFileAdapter::Parse()
	{
		mDocument.LoadFile(mFile->FullPath().c_str());
	}

	//////////////////////////////////////////////////////////////////////////

	TiXmlDocument& CXMLFileAdapter::GetDoc()
	{
		return mDocument;
	}

	//////////////////////////////////////////////////////////////////////////

	Module::GUID** CXMLFileAdapterFactory::SourceInterfaceList()
	{
		static const Module::GUID* pGuids[] = { &uuid_of(IFile), 0 };
		return (Module::GUID**)&pGuids[0];
	}

	//////////////////////////////////////////////////////////////////////////

	Module::GUID** CXMLFileAdapterFactory::DestInterfaceList()
	{
		static const Module::GUID* pGuids[] = { &uuid_of(IXMLFileAdapter), 0 };
		return (Module::GUID**)&pGuids[0];
	}

	//////////////////////////////////////////////////////////////////////////

	Module::HResult CXMLFileAdapterFactory::GetAdapter(Module::IUnknown *object, const Module::GUID &iid, void **ppAdapter)
	{
		if(iid != uuid_of(IXMLFileAdapter))
			return SF_E_NOINTERFACE;

		Module::com_ptr<IFile> pFile(object);

		if(!pFile) 
			return SF_E_INVALIDARG;

		CXMLFileAdapter *pAdapter;
		create_instance_impl<CXMLFileAdapter>(&pAdapter);
		pAdapter->FinalConstruct(pFile);

		*ppAdapter = static_cast<IXMLFileAdapter*>(pAdapter);
		return SF_S_OK;
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace
