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
#include "module/implementations.h"
#include <iostream>

//////////////////////////////////////////////////////////////////////////
inline int F1(int a, int b) { return a + b; }
//////////////////////////////////////////////////////////////////////////

struct Vec3
{
	float x, y, z;
	Vec3() : x(0), y(0), z(0) { }
	Vec3(float v) : x(v), y(v), z(v) { }
	Vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) { }
	bool operator==(const Vec3& rhs) { return x == rhs.x && y == rhs.y && z == rhs.z; }
};

reflect_class(Vec3, "Vec3")
//map_ctor()
//map_ctor(int)
end_reflection()

//////////////////////////////////////////////////////////////////////////

enum TestEnum
{
	VAL_1,
	VAL_2,
};

reflect_enum(TestEnum, "TestEnum")
	.def(enumeration_member("VAL_1", VAL_1))
	.def(enumeration_member("VAL_2", VAL_2))
end_reflection()

//////////////////////////////////////////////////////////////////////////

struct ITestClass
{
	virtual int DoFoo(int a, int b) = 0;
};

reflect_class(ITestClass, "ITestClass")
	.def<ITestClass>("DoFoo", &ITestClass::DoFoo)
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

reflect_class(TestClass1, "TestClass1")
	.def(base_type(type_of<ITestClass>(), classoffset<ITestClass, TestClass1>() ))
	.def<TestClass1>("DoFooInv", &TestClass1::DoFooInv)
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
	virtual const Vec3& GetV() const { return m_vec; }
	virtual void SetV(const Vec3& v) { m_vec = v; }
	int m_stub2;
	Vec3 m_vec;
};

reflect_class(TestClass2, "TestClass2")
	.def(base_type(type_of<TestClass1>(), classoffset<TestClass1, TestClass2>() ))
	.def<TestClass2>("V", &TestClass2::GetV, &TestClass2::SetV)
end_reflection()

//////////////////////////////////////////////////////////////////////////

#endif
