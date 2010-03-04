/*========================================================
* CINIFileAdapter.cpp
* @author Sergey Mikhtonyuk
* @date 24 November 2008
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/

#include "CINIFileAdapter.h"
#include "IFileSystem.h"
#include "FSExceptions.h"
#include <fstream>
#include <sstream>

namespace FileSystem
{
	//////////////////////////////////////////////////////////////////////////
	
	void CINIFileAdapter::FinalConstruct(IFile *pFile)
	{
		mFile = pFile;
	}

	//////////////////////////////////////////////////////////////////////////

	CINIFileAdapter::~CINIFileAdapter()
	{
		for(TFileMap::iterator it = mFileMap.begin(); it != mFileMap.end(); ++it)
			delete it->second;
	}

	//////////////////////////////////////////////////////////////////////////

	bool CINIFileAdapter::IsInitialized()
	{
		return mFileMap.size() != 0;
	}

	//////////////////////////////////////////////////////////////////////////

	IFile* CINIFileAdapter::WrappedFile()
	{
		return mFile;
	}

	//////////////////////////////////////////////////////////////////////////

	void CINIFileAdapter::Parse()
	{
		char *buf;
		std::ios::streamoff size;
		mFile->ReadFile(&buf, size);

		std::string line;
		std::istringstream ss(std::string(buf, (size_t)size));
		std::string sectionName;
		TSection* currentSection = 0;
		delete[] buf;

		while(true)
		{
			// Save current section before leaving
			if(ss.eof())
			{
				if(currentSection)
					mFileMap.insert(std::make_pair(sectionName, currentSection));
				break;
			}

			// Read line
			std::getline(ss, line);

			TrimLine(line);

			// if empty or comment
			if(line.length() == 0 || line[0] == ';' || line[0] == '#')
				continue;

			// is section
			if(line[0] == '[' && line[line.length() - 1] == ']')
			{
				if(currentSection)
					mFileMap.insert(std::make_pair(sectionName, currentSection));

				currentSection = new TSection();
				sectionName = line.substr(1, line.length() - 2);
			}

			// found the attribute
			else if(!currentSection || !AddAttribute(currentSection, line))
				throw FSParsingException("bad INI format");
		}
	}

	//////////////////////////////////////////////////////////////////////////

	void CINIFileAdapter::TrimLine(std::string& line)
	{
		line.erase(0, line.find_first_not_of("\r\n\t ") );
		line.erase( line.find_last_not_of("\r\n\t ") + 1 , line.npos );
	}

	//////////////////////////////////////////////////////////////////////////

	bool CINIFileAdapter::AddAttribute(TSection *section, std::string &attribute)
	{
		size_t delimiterPosition = attribute.find('=');

		if(delimiterPosition == std::string::npos) return false;

		std::string name = attribute.substr(0, delimiterPosition);
		std::string value = attribute.substr(delimiterPosition + 1);

		TrimLine(name);
		TrimLine(value);

		section->insert(std::make_pair(name, value));

		return true;
	}

	//////////////////////////////////////////////////////////////////////////

	Module::GUID** CINIFileAdapterFactory::SourceInterfaceList()
	{
		static const Module::GUID* pGuids[] = { &uuid_of(IFile), 0 };
		return (Module::GUID**)&pGuids[0];
	}

	//////////////////////////////////////////////////////////////////////////
	
	Module::GUID** CINIFileAdapterFactory::DestInterfaceList()
	{
		static const Module::GUID* pGuids[] = { &uuid_of(IINIFileAdapter), 0 };
		return (Module::GUID**)&pGuids[0];
	}

	//////////////////////////////////////////////////////////////////////////

	Module::HResult CINIFileAdapterFactory::GetAdapter(Module::IUnknown *object, const Module::GUID &iid, void **ppAdapter)
	{
		if(iid != uuid_of(IINIFileAdapter))
			return SF_E_NOINTERFACE;

		Module::com_ptr<IFile> pFile(object);

		if(!pFile) 
			return SF_E_INVALIDARG;

		CINIFileAdapter *pAdapter;
		create_instance_impl<CINIFileAdapter>(&pAdapter);
		pAdapter->FinalConstruct(pFile);

		*ppAdapter = static_cast<IINIFileAdapter*>(pAdapter);
		return SF_S_OK;
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace
