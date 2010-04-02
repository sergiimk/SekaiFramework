/*============================================================================
* test.cpp
* @author Sergey Mikhtonyuk
* @date 23 July 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/

#include "testclasses.h"

#define BOOST_TEST_MODULE Reflection test
#include <boost/test/unit_test.hpp>

using namespace reflection;


BOOST_AUTO_TEST_SUITE( reflection_test_suit );

BOOST_AUTO_TEST_CASE( create_builtin_int )
{
	builtin_type<int>* t = type_of<int>();
	BOOST_REQUIRE(t);
	BOOST_CHECK_EQUAL(t->tag(), T_INT);
	BOOST_CHECK_EQUAL(t->arch_type(), ARCH_BUILTIN);
	BOOST_CHECK_EQUAL(t->size(), sizeof(int));
}

BOOST_AUTO_TEST_CASE( create_builtin_double )
{
	double b = 3.14;
	builtin_type<double>* t = type_of(b);
	BOOST_CHECK_EQUAL(t->tag(), T_DOUBLE);
	BOOST_CHECK_EQUAL(t->arch_type(), ARCH_BUILTIN);
	BOOST_CHECK_EQUAL(t->size(), sizeof(double));
}

BOOST_AUTO_TEST_CASE( create_builtin_array )
{
	size_t arr[10];
	array_type* t = type_of(arr);
	t->name();
	BOOST_REQUIRE(t);
	BOOST_CHECK_EQUAL(t->element_type(), type_of<size_t>());
	BOOST_CHECK_EQUAL(t->length(), 10);
	BOOST_CHECK_EQUAL(t->size(), 10*sizeof(size_t));
}

BOOST_AUTO_TEST_CASE( create_builtin_pointer )
{
	pointer_type* t = type_of<float*>();
	BOOST_REQUIRE(t);
	BOOST_CHECK_EQUAL(t->pointee_type(), type_of<float>());
}

BOOST_AUTO_TEST_CASE( create_builtin_void )
{
	type* t = type_of<void>();
	BOOST_CHECK(t);
}

BOOST_AUTO_TEST_CASE( create_custom )
{
	user_type* t = type_of<Vec3>();
	BOOST_REQUIRE(t);
	/*Type* argt = type_of<int>();
	ConstructDescriptor* ctor = t->FindSuitableCtor(&argt, 1);
	BOOST_REQUIRE(ctor != 0);

	int a = 5;
	void* args[] = { &a };
	ASDF* inst = (ASDF*)ctor->CreateInstance(args);
	BOOST_REQUIRE(inst != 0);
	BOOST_CHECK_EQUAL(inst->a, 5);
	BOOST_CHECK_EQUAL(inst->f, 8);

	ctor->DestroyInstance(inst);*/
}

//////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE( name_builtin_float )
{
	builtin_type<float>* t = type_of<float>();
	BOOST_CHECK( strcmp(t->name(), "float") == 0 );
}

BOOST_AUTO_TEST_CASE( name_builtin_array_ptr )
{
	int* arr[10];
	type* t = type_of(arr);
	BOOST_CHECK(strcmp(t->name(), "int* [10]") == 0);
}
/*
BOOST_AUTO_TEST_CASE( tostring_builtin_double )
{
	double b = 3.14;
	type* td = type_of(b);

	BOOST_CHECK(td->ToString(&b, buf, buf_size));
	BOOST_CHECK(strcmp(buf, "3.14") == 0);
}

BOOST_AUTO_TEST_CASE( parse_builtin_double )
{
	double b;
	Type* td = type_of(b);
	BOOST_CHECK(td->TryParse(&b, "2.71"));
	BOOST_CHECK_EQUAL(b, 2.71);
}

BOOST_AUTO_TEST_CASE( compare_builtin )
{
	int a = 0;
	Type* ti1 = type_of<int>();
	Type* ti2 = type_of(a);
	BOOST_CHECK(ti1->Equal(ti2));

	Type* td1 = type_of<double>();
	BOOST_CHECK(!ti1->Equal(td1));
}

BOOST_AUTO_TEST_CASE( compare_user )
{
	Type* t1 = type_of<TestClass1>();
	Type* t2 = type_of<TestClass2>();
	BOOST_CHECK(!t1->Equal(t2));
	BOOST_CHECK(t2->Equal(t2));
}

BOOST_AUTO_TEST_CASE( create_enum )
{
	Type* t = type_of<TestEnum>();
	BOOST_CHECK(t);
}

BOOST_AUTO_TEST_CASE( tostring_enum )
{
	char buf[100];
	TestEnum e = VAL_2;
	Type* t = type_of<TestEnum>();
	BOOST_CHECK(t->ToString(&e, buf, 100));
	BOOST_CHECK(strcmp(buf, "VAL_2") == 0);
}

BOOST_AUTO_TEST_CASE( parse_enum )
{
	TestEnum e = VAL_2;
	Type* t = type_of<TestEnum>();
	BOOST_CHECK(t->TryParse(&e, "VAL_1"));
	BOOST_CHECK_EQUAL(e, VAL_1);
}*/

BOOST_AUTO_TEST_CASE( create_function )
{
	function_type* t = type_of(&F1);
	BOOST_CHECK(t);
}

BOOST_AUTO_TEST_CASE( invoke_function )
{
	function_type* t = type_of(&F1);
	int ret, a = 2, b = 3;
	void* args[] = { &a, &b };
	Delegate<int(int, int)> deleg = Delegate<int(int, int)>(F1);
	t->invoke(&deleg, args, &ret);
	BOOST_CHECK_EQUAL(ret, 5);
}

BOOST_AUTO_TEST_CASE( name_function )
{
	type* t = type_of(&F1);
	BOOST_CHECK(strcmp(t->name(), "int (int, int)") == 0);
}

//////////////////////////////////////////////////////////////////////////

template<class T>
struct MethodFixture1
{
	method* meth;
	function_type* methT;
	MethodFixture1(const char* name = "DoFoo")
	{
		user_type* t = type_of<T>();
		user_type::member_iterator it = t->find_member(name, true);
		meth = static_cast<method*>(&*it);
		methT = meth->get_function_type();
	}
};

template<class T>
struct MethodFixture2 : public MethodFixture1<T>
{
	MethodFixture2() : MethodFixture1<T>("DoFooInv")
	{ }
};

//////////////////////////////////////////////////////////////////////////

BOOST_FIXTURE_TEST_CASE( name_method, MethodFixture1<ITestClass> )
{
	BOOST_CHECK(strcmp(methT->name(), "int ITestClass::*(int, int)") == 0);
}

BOOST_FIXTURE_TEST_CASE( method_arguments, MethodFixture1<ITestClass> )
{
	BOOST_CHECK_EQUAL(methT->argument_count(), 3);
}

BOOST_FIXTURE_TEST_CASE( invoke_method, MethodFixture1<TestClass1> )
{
	TestClass1 tc;
	void* inst = &tc;
	int a = 10, b = 5, ret;
	void* args[] = { &inst, &a, &b };
	meth->invoke(args, &ret);
	BOOST_CHECK_EQUAL(ret, 15);
}
/*
BOOST_FIXTURE_TEST_CASE( invoke_method_of_base, MethodFixture1<TestClass2> )
{
	TestClass2 tc;
	TestClass2* inst = &tc;
	int a = 10, b = 5, ret;
	void* args[] = { &inst, &a, &b };
	method.Invoke(args, &ret);
	BOOST_CHECK_EQUAL(ret, 50);
}

BOOST_FIXTURE_TEST_CASE( invoke_method_of_middle, MethodFixture2<TestClass2> )
{
	TestClass2 tc;
	TestClass2* inst = &tc;
	int a = 10, b = 5, ret;
	void* args[] = { &inst, &a, &b };
	method.Invoke(args, &ret);
	BOOST_CHECK_EQUAL(ret, 2);
}

//////////////////////////////////////////////////////////////////////////

template<class T>
struct FieldFixture : public StringOutFixture
{
	Field field;
	FieldFixture()
	{
		UserType* t = static_cast<UserType*>(type_of<T>());
		field = t->FindField("field");
	}
};

//////////////////////////////////////////////////////////////////////////

BOOST_FIXTURE_TEST_CASE( tostring_field, FieldFixture<TestClass2> )
{
	TestClass2 tc;
	tc.field = 123;
	BOOST_CHECK(field.ToString(&tc, buf, buf_size));
	BOOST_CHECK(strcmp(buf, "123") == 0);
}

BOOST_AUTO_TEST_CASE( usertype )
{
	UserType* t = static_cast<UserType*>(type_of<TestClass1>());
	BOOST_CHECK_EQUAL(t->Tag(), RL_T_CLASS);
	BOOST_CHECK_EQUAL(t->Size(), sizeof(TestClass1));
	BOOST_CHECK_EQUAL(t->getBaseTypeNumber(), 1);
	BOOST_CHECK_EQUAL(t->getFieldNumber(), 1);
	BOOST_CHECK_EQUAL(t->getMethodNumber(), 1);
	BOOST_CHECK_EQUAL(t->getAccessorNumber(), 0);
}

BOOST_FIXTURE_TEST_CASE( name_usertype, StringOutFixture )
{
	Type* t = type_of<TestClass2>();
	t->Name(buf, buf_size);
	BOOST_CHECK(strcmp(buf, "TestClass2") == 0);
}

BOOST_AUTO_TEST_CASE( usertype_field )
{
	UserType* t = static_cast<UserType*>(type_of<TestClass2>());
	Field tcf = t->FindField("field");
	BOOST_CHECK_EQUAL(tcf.getType(), type_of<int>());
}

BOOST_AUTO_TEST_CASE( usertype_method )
{
	UserType* t = static_cast<UserType*>(type_of<TestClass2>());
	Method tcm = t->FindMethod("DoFoo");
	BOOST_CHECK_EQUAL(tcm.getType(), type_of(&ITestClass::DoFoo));
}

BOOST_AUTO_TEST_CASE( usertype_base )
{
	UserType* t = static_cast<UserType*>(type_of<TestClass2>());

	Type* tc = t->FindBaseType("TestClass1");
	BOOST_CHECK_EQUAL(tc, type_of<TestClass1>());

	Type* tc2 = t->FindBaseType("ITestClass");
	BOOST_CHECK_EQUAL(tc2, type_of<ITestClass>());

	BOOST_CHECK(t->FindBaseType("asdf") == 0);
}

struct AccessorFixture
{
	Accessor acc;
	AccessorFixture()
	{
		UserType* t = static_cast<UserType*>(type_of<TestClass2>());
		acc = t->FindAccessor("V");
	}
};

BOOST_FIXTURE_TEST_CASE( usertype_accessor_get, AccessorFixture )
{
	TestClass2 tc;
	tc.m_vec = VML::Vector3(1, 2, 3);
	VML::Vector3 ret;
	acc.getValue(&tc, &ret);
	BOOST_CHECK(VML::equivalent(ret, tc.m_vec));
}

BOOST_FIXTURE_TEST_CASE( usertype_accessor_set, AccessorFixture )
{
	TestClass2 tc;
	VML::Vector3 val(3, 2, 1);
	acc.setValue(&tc, &val);
	BOOST_CHECK(VML::equivalent(val, tc.m_vec));
}

BOOST_AUTO_TEST_CASE( eventTest )
{
	EventProvider provider;
	EventListener listener;

	provider.OnValueChanged.connect(MakeDelegate(&listener, &EventListener::AChanged));
	provider.SetA(10);
	BOOST_CHECK_EQUAL(provider.a, listener.a);

	provider.OnValueChanged.disconnect(MakeDelegate(&listener, &EventListener::AChanged));
	provider.SetA(11);
	BOOST_CHECK_NE(provider.a, listener.a);
}
*/
BOOST_AUTO_TEST_SUITE_END();
