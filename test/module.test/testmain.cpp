/*========================================================
* testmain.cpp
* @author Sergey Mikhtonyuk
* @date 23 July 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "testclasses.h"
#include "module/intellectual.h"
#include "module/exception.h"
#include <sstream>
#include <map>

using namespace Module;

SF_IMPLEMENT_EXCEPTION(TestException, Exception)

#define BOOST_TEST_MODULE SM_lib_test
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE( SMTest );

BOOST_AUTO_TEST_CASE( TestGUIDBinding )
{
	const GUID& g = uuid_of(ITest);
	GUID g2;
	g2.FromString("835ca580-8bc7-40a7-913e-49bbb4987085");

	BOOST_CHECK(g == g2);
}

BOOST_AUTO_TEST_CASE( TestGUIDFromString )
{
	// {a1efa033-613e-4110-90ce-992b81cf751f}
	GUID g = { 0xa1efa033, 0x613e, 0x4110, { 0x90, 0xce, 0x99, 0x2b, 0x81, 0xcf, 0x75, 0x1f } };

	GUID g2;
	bool res = g2.FromString("{a1efa033-613e-4110-90ce-992b81cf751f}");
	BOOST_CHECK(res);
	BOOST_CHECK(g == g2);

	GUID g3;
	res = g3.FromString("a1efa033-613e-4110-90ce-992b81cf751f");
	BOOST_CHECK(res);
	BOOST_CHECK(g == g3);

	std::istringstream ss("{a1efa033-613e-4110-90ce-992b81cf751f}");
	GUID g4;
	BOOST_CHECK(!(!(ss >> g4)));
	BOOST_CHECK(g == g3);
}

BOOST_AUTO_TEST_CASE( TestGUIDToString )
{
	// {a1efa033-613e-4110-90ce-992b81cf751f}
	GUID g = { 0xa1efa033, 0x613e, 0x4110, { 0x90, 0xce, 0x99, 0x2b, 0x81, 0xcf, 0x75, 0x1f } };
	const char* gs = "A1EFA033-613E-4110-90CE-992B81CF751F";

	char buf[37];
	g.ToString(buf);

	BOOST_CHECK(strcmp(buf, gs) == 0);

	std::ostringstream ss;
	ss << g;
	BOOST_CHECK_EQUAL(ss.str(), gs);
}

BOOST_AUTO_TEST_CASE( TestCreation )
{
	CTest* tc;
	create_instance_impl<CTest>(&tc);
	static_cast<ITest*>(tc)->Release();

	ITest* tc2;
	create_instance<CTest>(&tc2);
	tc2->Release();

	IClassFactory* tc3;
	create_instance<CTest>(&tc3);
	BOOST_CHECK(tc3 == 0);
}

BOOST_AUTO_TEST_CASE( TestCasting )
{
	ITest* tc;
	create_instance<CTest>(&tc);

	ITest2* tc2;
	interface_cast<ITest2>(tc, &tc2);
	BOOST_CHECK(tc2 != 0);
	tc2->Release();

	IClassFactory* tc3;
	interface_cast<IClassFactory>(tc, &tc3);
	BOOST_CHECK(tc3 == 0);

	tc->Release();
}

BOOST_AUTO_TEST_CASE( TestChaining )
{
	ITest2* t3;
	create_instance<CTest2>(&t3);

	BOOST_CHECK(t3);

	ITest2* t2;
	interface_cast<ITest2>(t3, &t2);

	BOOST_CHECK(t2);

	t2->Release();
	t3->Release();
}

BOOST_AUTO_TEST_CASE( TestComPtr )
{
	com_ptr<ITest> tc;
	create_instance<CTest>(tc);
	BOOST_CHECK(tc);

	com_ptr<ITest2> tc2;
	create_instance<CTest>(tc2);
	BOOST_CHECK(tc2);

	IClassFactory* t;
	interface_cast<IClassFactory>(tc2, &t);
	BOOST_CHECK(!t);

	com_ptr<IClassFactory> tc3;
	create_instance<CTest>(tc3);
	BOOST_CHECK(!tc3);
}

BOOST_AUTO_TEST_CASE( TestGUIDCompare )
{
	GUID g1;
	g1.FromString("00000001-0000-0000-0000-000000000000");
	GUID g2;
	g2.FromString("00000000-1000-0000-0000-000000000000");

	bool b1 = g1 < g2;
	bool b2 = g2 < g1;
	BOOST_CHECK_EQUAL( b1, !b2 );

	// Compare same guids
	bool b3 = g1 < g1;
	BOOST_CHECK_EQUAL( b3, false );
}

BOOST_AUTO_TEST_CASE( TestOnStackObjects )
{
	CTest2 t;

	t.AddRef();
	t.Release();

	t.Foo();

	ITest* pt;
	interface_cast<ITest>(static_cast<ITest*>(&t), &pt);
	BOOST_CHECK(pt);
}

BOOST_AUTO_TEST_CASE( TestException )
{
	try
	{
		Exception e("D'oh", "!", 10);
		e.rethrow();

		BOOST_CHECK(false);
	}
	catch(Exception& ex)
	{
		BOOST_CHECK(strcmp(ex.message(), "D'oh !") == 0);
	}
}

BOOST_AUTO_TEST_SUITE_END();
