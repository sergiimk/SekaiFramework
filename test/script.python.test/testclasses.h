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
#include <iostream>
#include "vml/vml.h"
#include "reflection/vml_reflect.h"

//////////////////////////////////////////////////////////////////////////

using namespace Module;
using namespace Script;
using namespace Reflection;

//////////////////////////////////////////////////////////////////////////

enum TestEnum
{
	eTE_VAL0,
	eTE_VAL1,
};

reflect_enum(TestEnum)
	map_enum(eTE_VAL0)
	map_enum(eTE_VAL1)
end_reflection_enum()

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

	~TestClass()
	{
		++sDelCount;
	}

	int data;
	bool bval;
	int methodID;
	static int sInstCount;
	static int sDelCount;
	char* str;

	int GetMethodID() const
	{
		return methodID;
	}

	void Method1()
	{
		methodID = 1;
	}

	void Method2()
	{
		methodID = 2;
	}

	virtual double Method3(int a, double b)
	{
		methodID = 3;
		double c = a * b;
		return c;
	}

};

reflect_class(TestClass)
	map_ctor()
	map_field("data", data)
	map_field("bval", bval)
	map_field("str", str)
	map_field("methodID", methodID)
	map_method("GetMethodID", GetMethodID)
	map_method("Method1", Method1)
	map_method("Method2", Method2)
	map_method("Method3", Method3)
end_reflection()

//////////////////////////////////////////////////////////////////////////

class TestPlayer
{
public:
	VML::Vector3 mPosition;

	VML::Vector3* mPositionPtr;


	const VML::Vector3& getPosition() const { return mPosition; }

	void setPosition(const VML::Vector3& pos) { mPosition = pos; }

	VML::Vector3* getPositionPtr() const { return mPositionPtr; }

	void setPositionPtr(VML::Vector3* pos) { mPositionPtr = pos; }


	TestPlayer() : mPosition(0), mPositionPtr(&mPosition) { }
};

//////////////////////////////////////////////////////////////////////////

reflect_class(TestPlayer)
	map_ctor_alloc(VML::AlignedAllocator)
	map_field("mPosition", mPosition)
	map_field("mPositionPtr", mPositionPtr)
	map_accessor("Position", getPosition, setPosition)
	map_accessor("PositionPtr", getPositionPtr, setPositionPtr)
	map_method("setPosition", setPosition)
	map_method("getPosition", getPosition)
	map_method("setPositionPtr", setPositionPtr)
	map_method("getPositionPtr", getPositionPtr)
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

reflect_class(TestInh_Base)
	map_ctor()
	map_method("getFlag", getFlag)
	map_method("VirtFunc", VirtFunc)
end_reflection()

reflect_class(TestInh_Derived)
	map_ctor()
	map_base(TestInh_Base)
end_reflection()

//////////////////////////////////////////////////////////////////////////

sf_interface ITestInterface : public Module::IUnknown
{
	sf_uuid("5315a473-f8e8-4724-bb13-336557779f85")
	virtual int Sum(int a, int b) = 0;
};

class NOVTABLE CTestInterface : 
	public Module::ComRootObject<>,
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


reflect_class(com_ptr<ITestInterface>)
	map_ctor()
end_reflection()

reflect_class(ITestInterface)
	map_base(Module::IUnknown)
	map_method("Sum", Sum)
end_reflection()

reflect_class(TestInterfaceFactory)
	map_ctor()
	map_method("GetTestInterface", GetTestInterface)
	map_method("CreateTestInterface", CreateTestInterface)
end_reflection()

//////////////////////////////////////////////////////////////////////////

class TestDocClass
{
public:
	int Add(int a, int b) { return a+b; }
	int somedata;
};

reflect_class( TestDocClass )
	map_ctor()
	map_method_doc("Add", Add, "Return summ of two integers")
	map_field_doc("somedata", somedata, "Some data documentation")
end_reflection()

//////////////////////////////////////////////////////////////////////////

#endif // _TESTCLASSES_H__
