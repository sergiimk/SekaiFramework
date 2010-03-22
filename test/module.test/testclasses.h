/*========================================================
* TestClasses.h
* @author Sergey Mikhtonyuk
* @date 23 July 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "module/implementations.h"
#include "module/exception.h"

//////////////////////////////////////////////////////////////////////////

sf_interface ITest : public Module::IUnknown
{
	sf_uuid("835ca580-8bc7-40a7-913e-49bbb4987085")

	virtual void Test() = 0;
};

sf_interface ITest2 : public Module::IUnknown
{
	sf_uuid("123ca580-8bc7-40a7-913e-49bbb4987085")

	virtual void Test() = 0;
};

sf_interface ITest3 : public Module::IUnknown
{
	sf_uuid("633f7d87-44a7-45b8-b3ed-3453fe7687cb")

	virtual void Foo() = 0;
};

//////////////////////////////////////////////////////////////////////////

class NOVTABLE CTest : 
	public Module::ComRootObject<>,
	public ITest,
	public ITest2
{
public:
	
	DECLARE_IMPLEMENTATION(CTest)

	BEGIN_INTERFACE_MAP()
		INTERFACE_ENTRY(ITest)
		INTERFACE_ENTRY(ITest2)
	END_INTERFACE_MAP()

	void Test()
	{
	}
};

//////////////////////////////////////////////////////////////////////////

class CTest2 :
	public CTest,
	public ITest3
{
public:

	DECLARE_IMPLEMENTATION_DERIVED(CTest2, CTest)

	BEGIN_INTERFACE_MAP()
		INTERFACE_ENTRY(ITest3)
		INTERFACE_ENTRY_CHAIN(CTest)
	END_INTERFACE_MAP()

	void Foo()
	{
	}
};

//////////////////////////////////////////////////////////////////////////

SF_DECLARE_EXCEPTION(TestException, Module::Exception)

//////////////////////////////////////////////////////////////////////////
