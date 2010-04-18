/*========================================================
* TestClasses.h
* @author Sergey Mikhtonyuk
* @date 06 July 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _TESTCLASSES_H__
#define _TESTCLASSES_H__

//////////////////////////////////////////////////////////////////////////

#include "module/module.h"
#include "module/intellectual.h"
#include "module/module_reflection.h"
#include "script.python/Scripting.h"

//////////////////////////////////////////////////////////////////////////

using namespace module;
using namespace Script;
using namespace reflection;

//////////////////////////////////////////////////////////////////////////

struct Vec3
{
	float x, y, z;
	Vec3() : x(0), y(0), z(0) { }
	Vec3(float v) : x(v), y(v), z(v) { }
	Vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) { }
	bool operator==(const Vec3& rhs) { return x == rhs.x && y == rhs.y && z == rhs.z; }
	float getX() const { return x; } void setX(float v) { x = v; }
	float getY() const { return y; } void setY(float v) { y = v; }
	float getZ() const { return z; } void setZ(float v) { z = v; }
};

inline std::ostream& operator<<(std::ostream& os, const Vec3& v)
{
	return os << v.x << ' ' << v.y << ' ' << v.z;
}

inline std::istream& operator>>(std::istream& is, Vec3& v)
{
	return is;
}

reflect_class(Vec3, "Vector3")
	.def_ctor()
	.def_ctor(float)
	.def_ctor(float, float, float)
	.def_accessor("x", getX, setX)
	.def_accessor("y", getY, setY)
	.def_accessor("z", getZ, setZ)
	.def_parsable()
end_reflection()

//////////////////////////////////////////////////////////////////////////

enum TestEnum
{
	eTE_VAL0,
	eTE_VAL1,
};

reflect_enum(TestEnum, "TestEnum")
	.def_enum("eTE_VAL0", eTE_VAL0)
	.def_enum("eTE_VAL1", eTE_VAL1)
end_reflection()

//////////////////////////////////////////////////////////////////////////

class TestClass
{
public:
	TestClass()
	{
		methodID = 0;
		data = sInstCount++;
		str = (char*)"some string";
	}

	~TestClass() { ++sDelCount; }

	int data;
	int getData() const { return data; }
	void setData(int d) { data = d; }

	bool bval;
	int methodID;
	static int sInstCount;
	static int sDelCount;
	char* str;
	const char* getStr() const { return str; }

	int GetMethodID() const { return methodID; }
	void Method1() { methodID = 1; }
	void Method2() { methodID = 2; }
	virtual double Method3(int a, double b) { methodID = 3; double c = a * b; return c; }
};

reflect_class(TestClass, "TestClass")
	.def_ctor()
	.def_method("GetMethodID", GetMethodID)
	.def_method("Method1", Method1)
	.def_method("Method2", Method2)
	.def_method("Method3", Method3)
	.def_accessor("data", getData, setData)
	.def_accessor_ro("str", getStr)
end_reflection()

//////////////////////////////////////////////////////////////////////////

class TestPlayer
{
public:
	Vec3 mPosition;
	Vec3* mPositionPtr;

	const Vec3& getPosition() const { return mPosition; }
	void setPosition(const Vec3& pos) { mPosition = pos; }

	Vec3* getPositionPtr() const { return mPositionPtr; }
	void setPositionPtr(Vec3* pos) { mPositionPtr = pos; }

	TestPlayer() : mPosition(0), mPositionPtr(&mPosition) { }
};

//////////////////////////////////////////////////////////////////////////

reflect_class(TestPlayer, "TestPlayer")
	.def_ctor()
	.def_accessor("Position", getPosition, setPosition)
	.def_accessor("PositionPtr", getPositionPtr, setPositionPtr)
	.def_method("setPosition", setPosition)
	.def_method("getPosition", getPosition)
	.def_method("setPositionPtr", setPositionPtr)
	.def_method("getPositionPtr", getPositionPtr)
end_reflection()

//////////////////////////////////////////////////////////////////////////

struct TestInh_Base
{
	static int flag;

	int getFlag() const { return flag; }

	virtual void VirtFunc(int f) { flag = f; }
};

struct TestInh_Derived : public TestInh_Base
{
	void VirtFunc(int f) { flag = f - 1; }
};

reflect_class(TestInh_Base, "TestInh_Base")
	.def_ctor()
	.def_method("getFlag", getFlag)
	.def_method("VirtFunc", VirtFunc)
end_reflection()

reflect_class(TestInh_Derived, "TestInh_Derived")
	.def_ctor()
	.def_base(TestInh_Base)
end_reflection()

//////////////////////////////////////////////////////////////////////////

sf_interface ITestInterface : public module::IUnknown
{
	sf_uuid("5315a473-f8e8-4724-bb13-336557779f85")
	virtual int Sum(int a, int b) = 0;
};

class NOVTABLE CTestInterface : 
	public module::ComRootObject<>,
	public ITestInterface
{
public:
	
	DECLARE_IMPLEMENTATION(CTestInterface)

	BEGIN_INTERFACE_MAP()
		INTERFACE_ENTRY(ITestInterface)
	END_INTERFACE_MAP()

	virtual int Sum(int a, int b) { return a + b; }
};

class TestInterfaceFactory
{
public:
	ITestInterface* GetTestInterface() 
	{
		CTestInterface* ti;
		create_instance_impl(&ti);
		return ti;
	}

	com_ptr<ITestInterface> CreateTestInterface()
	{
		com_ptr<ITestInterface> ti;
		create_instance<CTestInterface, ITestInterface>(ti);
		return ti;
	}
};


reflect_class(com_ptr<ITestInterface>, "ITestInterfacePtr")
	.def_ctor()
end_reflection()

reflect_class(ITestInterface, "ITestInterface")
	.def_base(module::IUnknown)
	.def_method("Sum", Sum)
end_reflection()

reflect_class(TestInterfaceFactory, "TestInterfaceFactory")
	.def_ctor()
	.def_method("GetTestInterface", GetTestInterface)
	.def_method("CreateTestInterface", CreateTestInterface)
end_reflection()

//////////////////////////////////////////////////////////////////////////

/*class TestDocClass
{
public:
	int Add(int a, int b) { return a+b; }
	int somedata;
};

reflect_class( TestDocClass )
	map_ctor()
	map_method_doc("Add", Add, "Return sum of two integers")
	map_field_doc("somedata", somedata, "Some data documentation")
end_reflection()*/

//////////////////////////////////////////////////////////////////////////

#endif // _TESTCLASSES_H__
