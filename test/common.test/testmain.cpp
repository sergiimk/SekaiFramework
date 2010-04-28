/*========================================================
* testmain.cpp
* @author Sergey Mikhtonyuk
* @date 09 December 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include <algorithm>

#include "common/containers.h"
#include "common/stack_string.h"
#include "common/cow_wrappers.h"

#define BOOST_TEST_MODULE CommonTest
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE( CommonTestSuit );

BOOST_AUTO_TEST_CASE( ArrayTest )
{
}

	//////////////////////////////////////////////////////////////////////////

	BOOST_AUTO_TEST_SUITE( StackAllocationTest );

	BOOST_AUTO_TEST_CASE( StackStringTest )
	{
		// simple creation
		const char* source1 = "test string";
		stack_string<> stack1(source1);
		BOOST_CHECK(stack1->compare(source1) == 0);

		// std::string creation
		std::string source2("yet another string");
		stack_string<> stack2(source2);
		BOOST_CHECK_EQUAL(stack2->length(), source2.length());
		BOOST_CHECK(std::equal(stack2->begin(), stack2->end(), source2.begin()));

		std::string asdf;
	}

	BOOST_AUTO_TEST_CASE( StackStringReallocateTest )
	{
		// simple creation
		const char* source = "a very test string";
		stack_string<> stack(source);

		// check stack
		BOOST_CHECK(stack.isOnStack());

		// reallocate
		stack->reserve(1024);

		BOOST_CHECK(!stack.isOnStack());
	}

	BOOST_AUTO_TEST_CASE( COWWrappersTest )
	{
		typedef cow_wrapper< std::vector<int> > wrapper;

		wrapper c1;
		c1->push_back(10);

		// Prevents COW to kick in to early
		wrapper const& cc1(c1);

		auto c2 = c1.get_snapshot();
		BOOST_CHECK_EQUAL(&*cc1, &*c2);
		BOOST_CHECK_EQUAL(cc1->size(), 1);
		BOOST_CHECK_EQUAL(c2->size(), 1);

		c1->push_back(20);
		BOOST_CHECK_NE(&*cc1, &*c2);
		BOOST_CHECK_EQUAL(c1->size(), 2);
		BOOST_CHECK_EQUAL(c2->size(), 1);
	}

	BOOST_AUTO_TEST_SUITE_END();

	//////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_SUITE_END();