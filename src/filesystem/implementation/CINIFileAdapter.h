/*========================================================
* CINIFileAdapter.h
* @author Sergey Mikhtonyuk
* @date 24 November 2008
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _CINIFILEADAPTER_H__
#define _CINIFILEADAPTER_H__

#include "IINIFileAdapter.h"
#include "common/IAdapterFactory.h"
#include "module/implementations.h"
#include "module/intellectual.h"

namespace FileSystem
{
	/// Implementation of INI adapter interface
	/** @ingroup FileSystem */
	class NOVTABLE CINIFileAdapter : 
		public Module::ComRootObject<Module::MultiThreadModel>,
		public IINIFileAdapter
	{
	public:
		DECLARE_IMPLEMENTATION(CINIFileAdapter)
	
		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(IINIFileAdapter)
		END_INTERFACE_MAP()

		~CINIFileAdapter();
	
		bool		IsInitialized();
		IFile*		WrappedFile();
		void		Parse();
		TFileMap&	FileMap() { return mFileMap; }

		void FinalConstruct(IFile* pFile);
		void TrimLine(std::string& line);
		bool AddAttribute(TSection *section, std::string &attribute);

	protected:
		Module::com_ptr<IFile> mFile;
		TFileMap			mFileMap;
	};



	/// Adapter factory for IINIFileAdapter
	/** @ingroup FileSystem */
	class NOVTABLE CINIFileAdapterFactory : 
		public Module::ComRootObject<>,
		public IAdapterFactory
	{
	public:
		DECLARE_IMPLEMENTATION(CINIFileAdapterFactory)
	
		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(IAdapterFactory)
		END_INTERFACE_MAP()
	
		Module::GUID**	SourceInterfaceList();
		Module::GUID**	DestInterfaceList();
		Module::HResult	GetAdapter(Module::IUnknown* object, SF_RIID iid, void **ppAdapter);
	};

} // namespace

#endif // _CINIFILEADAPTER_H__