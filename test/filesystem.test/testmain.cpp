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

BOOST_AUTO_TEST_CASE( TestCmp )
{
	path p1("test/");
	path p2("test");
	BOOST_CHECK_EQUAL(p1, p2);

	p2 += "sdf";
	BOOST_CHECK_NE(p1, p2);
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
}

BOOST_AUTO_TEST_CASE( TestFwdIterators )
{
	path p("..//something/right_one.yep");
	
	path::iterator it = p.begin();
	BOOST_CHECK(strcmp(it.element(), "..") == 0);

	BOOST_CHECK( ++it );
	BOOST_CHECK(strcmp(it.element(), "something") == 0);

	BOOST_CHECK( ++it );
	BOOST_CHECK(strcmp(it.element(), "right_one.yep") == 0);
	BOOST_CHECK( it != p.end() );

	BOOST_CHECK( ! ++it );
	BOOST_CHECK(strcmp(it.element(), "") == 0);
	BOOST_CHECK( it == p.end() );
}

BOOST_AUTO_TEST_CASE( TestRevIterators )
{
	path p("/../something//right_one.yep");
	
	path::iterator it = p.end();
	BOOST_CHECK(strcmp(it.element(), "") == 0);

	BOOST_CHECK( --it );
	BOOST_CHECK(strcmp(it.element(), "right_one.yep") == 0);

	BOOST_CHECK( --it );
	BOOST_CHECK(strcmp(it.element(), "something") == 0);
	BOOST_CHECK( it != p.begin() );

	BOOST_CHECK( --it );
	BOOST_CHECK(strcmp(it.element(), "..") == 0);
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

BOOST_AUTO_TEST_SUITE_END();
