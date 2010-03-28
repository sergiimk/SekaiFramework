/*========================================================
* TestClasses.h
* @author Sergey Mikhtonyuk
* @date 02 January 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _TEST_CLASSES_H__
#define _TEST_CLASSES_H__


#include "reflection/reflection.h"
/*#include "module/implementations.h"
#include "vml/vml.h"
#include "reflection/vml_ios.h"
#include "reflection/vml_reflect.h"
#include <iostream>

//////////////////////////////////////////////////////////////////////////
inline int F1(int a, int b) { return a + b; }
//////////////////////////////////////////////////////////////////////////

struct ASDF
{
	int a, s, d, f;
	ASDF() : a(0), s(1), d(2), f(3)
	{
	}

	ASDF(int _a) : a(_a), s(a+1), d(a+2), f(a+3)
	{
	}
};

reflect_class(ASDF)
	map_ctor()
	map_ctor(int)
end_reflection()


//////////////////////////////////////////////////////////////////////////

enum TestEnum
{
	VAL_1,
	VAL_2,
};

std::ostream& operator<<(std::ostream& os, const TestEnum& cc);
std::istream& operator>>(std::istream& os, TestEnum& cc);

reflect_enum(TestEnum)
	map_enum(VAL_1) 
	map_enum(VAL_2)
end_reflection_enum()


//////////////////////////////////////////////////////////////////////////

struct ITestClass
{
	virtual int DoFoo(int a, int b) = 0;
};

reflect_class(ITestClass)
	map_method("DoFoo", DoFoo)
end_reflection()

//////////////////////////////////////////////////////////////////////////

class MixUp
{
	virtual void Blah() { }
	int m_stub;
};

class TestClass1 : public MixUp, public ITestClass
{
public:
	virtual int DoFoo(int a, int b) { return a + b; }
	virtual int DoFooInv(int a, int b) { return a - b; }
	int field;
};

reflect_class(TestClass1)
	map_base(ITestClass)
	map_method("DoFooInv", DoFooInv)
	map_field("field", field)
end_reflection()

//////////////////////////////////////////////////////////////////////////

class MixUp2
{
	virtual void Blah2() { }
	int m_stubx;
};

class TestClass2 : public MixUp2, public TestClass1
{
public:
	virtual int DoFoo(int a, int b) { return a * b; }
	virtual int DoFooInv(int a, int b) { return a / b; }
	virtual const VML::Vector3& GetV() const { return m_vec; }
	virtual void SetV(const VML::Vector3& v) { m_vec = v; }
	int m_stub2;
	VML::Vector3 m_vec;
};

reflect_class(TestClass2)
	map_base(TestClass1)
	map_accessor("V", GetV, SetV)
end_reflection()

//////////////////////////////////////////////////////////////////////////

class EventProvider
{
public:
	int a;

	void SetA(int na) { 
		if(a != na) {
			a = na; 
			OnValueChanged.raise(na);
		}
	}

	int GetA() const { return a; }

	Reflection::Event<void (int)> OnValueChanged;
};

//////////////////////////////////////////////////////////////////////////

class EventListener
{
public:
	int a;

	void AChanged(int na)
	{ a = na; }
};

//////////////////////////////////////////////////////////////////////////
*/
#endif
