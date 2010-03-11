#include "module/module.h"
#include "module/intellectual.h"
#include "filesystem/FileSystem.h"
#include "misc.h"

#define BOOST_TEST_MODULE FileSystem test
#include <boost/test/unit_test.hpp>
#include <iostream>

using namespace FileSystem;
using namespace Module;

ModuleHandle module(SHARED_LIB_NAME("filesystem"));


BOOST_AUTO_TEST_SUITE( my_suite1 );


BOOST_AUTO_TEST_CASE( TestForSingleton )
{
	ModuleHandle m2(SHARED_LIB_NAME("filesystem"));

	com_ptr<IFileSystem> fs1;
	BOOST_REQUIRE(SF_SUCCEEDED(create_instance(fs1.wrapped(), CLSID_CFileSystem, module)));

	com_ptr<IFileSystem> fs2;
	BOOST_REQUIRE(SF_SUCCEEDED(create_instance(fs2.wrapped(), CLSID_CFileSystem, module)));

	BOOST_CHECK_EQUAL(fs1, fs2);
}


BOOST_AUTO_TEST_CASE( TestHandles )
{
	com_ptr<IFileSystem> fs;
	BOOST_CHECK(SF_SUCCEEDED(create_instance(fs.wrapped(), CLSID_CFileSystem, module)));

	com_ptr<IFile> fh = fs->GetResource("../../test/filesystem.test/testmain.cpp");
	BOOST_CHECK(fh);

	BOOST_CHECK_NE(fh->FullPath().find("/testmain.cpp"), -1);

	com_ptr<IFolder> fld = fh->Parent();
	BOOST_CHECK(fld);

	BOOST_CHECK_NE(fld->FullPath().find("/filesystem.test"), -1);
	BOOST_CHECK_EQUAL(fld->BaseName(), std::string("filesystem.test"));
}

BOOST_AUTO_TEST_CASE( TestFolderChildren )
{
	com_ptr<IFileSystem> fs;
	BOOST_CHECK(SF_SUCCEEDED(create_instance(fs.wrapped(), CLSID_CFileSystem, module)));

	com_ptr<IFolder> pFld = fs->GetResource("../../test/filesystem.test");
	BOOST_CHECK(pFld);

	const std::vector<IResource*>& children = pFld->GetChildren();
	com_ptr<IResource> pFound;
	for(size_t i = 0; i < children.size(); ++i)
		if(children[i]->FullPath().find("testmain.cpp") != std::string::npos)
			pFound = children[i];

	BOOST_CHECK(pFound);
}


BOOST_AUTO_TEST_CASE( TestFileReading )
{
	com_ptr<IFileSystem> fs;
	BOOST_CHECK(SF_SUCCEEDED(create_instance(fs.wrapped(), CLSID_CFileSystem, module)));

	com_ptr<IFolder> pFld1 = fs->GetResource("../../test/filesystem.test/tests");
	BOOST_CHECK(pFld1);

	com_ptr<IFile> pFile = pFld1->FindChild("testXML.xml");
	BOOST_CHECK(pFile);

	std::fstream& ifs = pFile->Stream();

	BOOST_CHECK(ifs.is_open());

	char c;
	while(ifs.get(c));

	ifs.close();
}


BOOST_AUTO_TEST_CASE( TestXMLAdapter )
{
	com_ptr<IFileSystem> fs;
	BOOST_CHECK(SF_SUCCEEDED(create_instance(fs.wrapped(), CLSID_CFileSystem, module)));

	com_ptr<IFile> pFile = fs->GetResource("../../test/filesystem.test/tests/testXML.xml");
	BOOST_CHECK(pFile);

	com_ptr<IXMLFileAdapter> pXMLAdapter;
	BOOST_CHECK(SF_SUCCEEDED(fs->CreateFileAdapter(pFile, UUID_PPV(IXMLFileAdapter, pXMLAdapter.wrapped()))));
	BOOST_CHECK(pXMLAdapter);

	BOOST_CHECK_EQUAL(pXMLAdapter->IsInitialized(), false);
	pXMLAdapter->Parse();
	BOOST_CHECK_EQUAL(pXMLAdapter->IsInitialized(), true);

	TiXmlDocument& doc = pXMLAdapter->GetDoc();

    CTestVisitor v;
	doc.Accept(&v);
}



BOOST_AUTO_TEST_CASE( TestINIAdapter )
{
	com_ptr<IFileSystem> fs;
	BOOST_CHECK(SF_SUCCEEDED(create_instance(fs.wrapped(), CLSID_CFileSystem, module)));

	com_ptr<IFile> pFile = fs->GetResource("../../test/filesystem.test/tests/testINI.ini");
	BOOST_CHECK(pFile);

	com_ptr<IINIFileAdapter> pINIAdapter;
	BOOST_CHECK(SF_SUCCEEDED(fs->CreateFileAdapter(pFile, UUID_PPV(IINIFileAdapter, pINIAdapter.wrapped()))));
	BOOST_CHECK(pINIAdapter);

	BOOST_CHECK_EQUAL(pINIAdapter->IsInitialized(), false);
	pINIAdapter->Parse();
	BOOST_CHECK_EQUAL(pINIAdapter->IsInitialized(), true);
}



BOOST_AUTO_TEST_CASE( TestReadAll )
{
	com_ptr<IFileSystem> fs;
	BOOST_CHECK(SF_SUCCEEDED(create_instance(fs.wrapped(), CLSID_CFileSystem, module)));

	com_ptr<IFile> pFile = fs->GetResource("../../test/filesystem.test/tests/testXML.xml");
	BOOST_CHECK(pFile);

	char *buf;
	std::ios::streamoff size;
	pFile->ReadFile(&buf, size);

	BOOST_CHECK_NE((int)size, 0);

	delete[] buf;
}

BOOST_AUTO_TEST_CASE( TestArchives )
{
	com_ptr<IFileSystem> fs;
	BOOST_CHECK(SF_SUCCEEDED(create_instance(fs.wrapped(), CLSID_CFileSystem, module)));

	com_ptr<IFile> stxt2 = fs->GetResource("../../test/filesystem.test/tests/test_arch.zip/sub/sub.txt", true);
	BOOST_CHECK(stxt2);

	com_ptr<IResource> pRes = fs->GetResource("../../test/filesystem.test/tests/test_arch.zip");
	BOOST_CHECK(pRes);

	// Test interface map
	com_ptr<IArchive> pArch = pRes;
	{
		com_ptr<IResourceContainer> pResCont = pRes;
		com_ptr<IFile> pFile = pRes;
		BOOST_CHECK(pRes); BOOST_CHECK(pResCont); BOOST_CHECK(pFile); BOOST_CHECK(pArch);
	}

	// Navigation test
	com_ptr<IFolder> sub = pArch->FindChild("sub");
	BOOST_CHECK(sub);

	com_ptr<IFile> stxt = sub->FindChild("sub.txt");
	BOOST_CHECK(stxt);

	// Unpack test
	char *buf;
	std::ios::streamoff size;
	stxt->ReadFile(&buf, size);

	BOOST_CHECK_NE((int)size, 0);

	delete[] buf;

	BOOST_CHECK_EQUAL(stxt, stxt2);
}

BOOST_AUTO_TEST_CASE( testTravers )
{
	class _testTraverser : public IFSTraverser
	{
		bool VisitFolder(IFolder* fld)
		{
			return true;
		}
		void LeaveFolder(IFolder* fld)
		{
		}
		bool VisitArchive(IArchive* arch)
		{
			return true;
		}
		void LeaveArchive(IArchive* arch)
		{
		}
		void VisitFile(IFile* file)
		{
		}
	} tr;

	com_ptr<IFileSystem> fs;
	BOOST_CHECK(SF_SUCCEEDED(create_instance(fs.wrapped(), CLSID_CFileSystem, module)));

	com_ptr<IResource> pRes = fs->GetResource("../../test/filesystem.test/tests");
	BOOST_CHECK(pRes);

	pRes->Accept(&tr);
}

BOOST_AUTO_TEST_SUITE_END();
