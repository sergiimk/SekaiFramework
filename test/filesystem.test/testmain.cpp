/*========================================================
* testmain.cpp
* @author Sergey Mikhtonyuk
* @date 20 Mar 2010
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "filesystem/filesystem.h"

#define BOOST_TEST_MODULE FileSystem test
#include <boost/test/unit_test.hpp>
#include <iostream>

using namespace filesystem;

BOOST_AUTO_TEST_SUITE( PathTestSuite );

BOOST_AUTO_TEST_CASE( TestConstructPath )
{
	path p("test_path");
	BOOST_CHECK_THROW(path p2("te|<>\"?*st"), Module::InvalidArgumentException);
}

BOOST_AUTO_TEST_CASE( TestCmp )
{
	path p1("test/");
	path p2("test");
	BOOST_CHECK_EQUAL(p1, p2);

#if defined OS_WINDOWS
	BOOST_CHECK_EQUAL(p1, "TeSt");
#endif
}

BOOST_AUTO_TEST_CASE( TestJoin )
{
	path p1;
	p1 += "test";
	BOOST_CHECK(strcmp(p1.c_str(), "test") == 0);

	path p2;
	p2 += "/test";
	BOOST_CHECK(strcmp(p2.c_str(), "/test") == 0);

	path p3("asdf/");
	p3 += "test";
	BOOST_CHECK(strcmp(p3.c_str(), "asdf\\test") == 0);

	path p4("asdf/");
	p4 += "/test/";
	BOOST_CHECK(strcmp(p4.c_str(), "asdf\\test") == 0);

	path p5;
	p5 += "/";
	BOOST_CHECK(strcmp(p5.c_str(), "/") == 0);
}

BOOST_AUTO_TEST_CASE( TestAttrs )
{
	path p1("../../test/filesystem.test/tests");
	BOOST_CHECK( p1.exists() );
	BOOST_CHECK( p1.is_directory() );
	BOOST_CHECK( !p1.is_file() );

	path p2 = p1 + "testINI.ini";
	BOOST_CHECK( p2.exists() );
	BOOST_CHECK( !p2.is_directory() );
	BOOST_CHECK( p2.is_file() );
}

BOOST_AUTO_TEST_CASE( TestSlices )
{
	path p("/abc/def/ghi.j");
	BOOST_CHECK_EQUAL( p.basename(), "ghi.j" );
	BOOST_CHECK_EQUAL( p.dirname(), "/abc/def" );
	--p;
	--p;
	BOOST_CHECK_EQUAL( p, "/abc" );
	--p;
	BOOST_CHECK_EQUAL( p, "/" );
}

BOOST_AUTO_TEST_CASE( TestExt )
{
	path p1("asdf/fdsa.ext");
	BOOST_CHECK( strcmp(".ext", p1.extension()) == 0 );

	path p2("asdf/fdsaext");
	BOOST_CHECK( strcmp("", p2.extension()) == 0 );
}

BOOST_AUTO_TEST_CASE( TestAbs )
{
	path p1 = path::current_dir();
	path p2(".");

	BOOST_CHECK( !p2.is_absolute() );
	p2.absolute();
	BOOST_CHECK( p2.is_absolute() );

	BOOST_CHECK_EQUAL(p1, p2);
}

BOOST_AUTO_TEST_CASE( TestRelPath )
{
	path p1("/common/asdf/fdsa");
	path p2("/common/fdsa/asdf");
	
	BOOST_CHECK_EQUAL(path::common_prefix(p1, p2), "/common");

	path p3 = path::current_dir();
	p3 += "asdf/fdsa";
	p3.absolute();
	p3.relative();
	BOOST_CHECK_EQUAL(p3, "asdf/fdsa");

	path p4 = path::current_dir();
	p4 += "../asdf/fdsa";
	p4.absolute();
	p4.relative();
	BOOST_CHECK_EQUAL(p4, "../asdf/fdsa");
}

BOOST_AUTO_TEST_CASE( TestNormalization )
{
	path p("AbCd/teSt");
	p.normcase();
#if defined OS_WINDOWS
	BOOST_CHECK(strcmp(p.c_str(), "abcd/test") == 0);
#else
	BOOST_CHECK(strcmp(p.c_str(), "AbCd/teSt") == 0);
#endif

	path p2("test//../../asdf/");
	p2.normpath();
	BOOST_CHECK_EQUAL(p2, "../asdf");

	path p3("/test/..//asdf/");
	p3.normpath();
	BOOST_CHECK_EQUAL(p3, "/asdf");
}

BOOST_AUTO_TEST_CASE( TestFwdIterators )
{
	path p("/..//something/right_one.yep");
	
	const char sep[] = { *path::separators(), '\0' };

	path::iterator it = p.begin();
	BOOST_CHECK(strcmp(it.element(), sep) == 0);
	BOOST_CHECK( it != p.end() );

	BOOST_CHECK( ++it );
	BOOST_CHECK(strcmp(it.element(), "..") == 0);

	BOOST_CHECK( ++it );
	BOOST_CHECK(strcmp(it.element(), "something") == 0);

	BOOST_CHECK( ++it );
	BOOST_CHECK(strcmp(it.element(), "right_one.yep") == 0);
	BOOST_CHECK( it != p.end() );

	BOOST_CHECK( ! ++it );
	BOOST_CHECK(strcmp(it.element(), "") == 0);
	BOOST_CHECK( it == p.end() );

#if defined OS_WINDOWS
	path p1("C:\\test\\");
	
	it = p1.begin();
	BOOST_CHECK(strcmp(it.element(), "C:") == 0);

	BOOST_CHECK( ++it );
	BOOST_CHECK(strcmp(it.element(), "test") == 0);
	
	BOOST_CHECK( ! ++it );
	BOOST_CHECK( it == p1.end() );
#endif
}

BOOST_AUTO_TEST_CASE( TestRevIterators )
{
	path p("/../something//right_one.yep");

	const char sep[] = { *path::separators(), '\0' };
	
	path::iterator it = p.end();
	BOOST_CHECK(strcmp(it.element(), "") == 0);

	BOOST_CHECK( --it );
	BOOST_CHECK(strcmp(it.element(), "right_one.yep") == 0);

	BOOST_CHECK( --it );
	BOOST_CHECK(strcmp(it.element(), "something") == 0);

	BOOST_CHECK( --it );
	BOOST_CHECK(strcmp(it.element(), "..") == 0);
	BOOST_CHECK( it != p.begin() );

	BOOST_CHECK( --it );
	BOOST_CHECK(strcmp(it.element(), sep) == 0);
	BOOST_CHECK( it == p.begin() );
}

BOOST_AUTO_TEST_CASE( TestDirIterators )
{
	path p("../../test/filesystem.test/");

	directory_iterator dir = p.list_dir();
	
	bool found = false;
	while(dir)
	{
		if(dir.current() == "tests")
			found = true;
		dir++; // post on purpose
	}

	BOOST_CHECK(found);
}

BOOST_AUTO_TEST_CASE( TestConvenience )
{
	path p1 = path::temp_dir();
	path p2 = path::temp_file_name(p1, "sekai");
}

BOOST_AUTO_TEST_SUITE_END();
