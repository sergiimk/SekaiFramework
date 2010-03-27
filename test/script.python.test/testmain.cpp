/*========================================================
* testmain.cpp
* @author Sergey Mikhtonyuk
* @date 06 July 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/

#include "testclasses.h"
#include "module/module_reflection.h"

#define BOOST_TEST_MODULE Python_script_test
#include <boost/test/unit_test.hpp>

ModuleHandle py(SHARED_LIB_NAME("script.python"));
ModuleHandle test(SHARED_LIB_NAME("script.python.test.module"));

BOOST_AUTO_TEST_SUITE( PyTest );

struct ScriptFixture
{
	com_ptr<IScriptManager> mgr;

	ScriptFixture()
	{
		TestClass::sInstCount = 0;
		TestClass::sDelCount = 0;
		py.CreateInstance(UUID_PPV(IScriptManager, mgr.wrapped()));
		mgr->Init();
	}

	void Shutdown()
	{
		if(mgr)
		{
			mgr->Shutdown();
			mgr.Release();
		}
	}

	~ScriptFixture() { Shutdown(); }
};

BOOST_FIXTURE_TEST_CASE( InitShytdownTest, ScriptFixture )
{
}

BOOST_FIXTURE_TEST_CASE( PlainPyTest, ScriptFixture )
{
	mgr->RunScript("py_plain");
}

BOOST_FIXTURE_TEST_CASE( ObjectCreateDestroyTest, ScriptFixture )
{
	mgr->ExportType("Sekai", (UserType*)type_of<TestClass>());
	mgr->RunScript("py_simple");

	Shutdown();

	BOOST_CHECK_EQUAL(TestClass::sInstCount, 2);
	BOOST_CHECK_EQUAL(TestClass::sDelCount, 2);
}

BOOST_FIXTURE_TEST_CASE( CounstructionTest, ScriptFixture )
{
	mgr->ExportType("Sekai", (UserType*)type_of<VML::Vector3>());
	mgr->RunScript("py_construction");
}

BOOST_FIXTURE_TEST_CASE( MethodsTest, ScriptFixture )
{
	mgr->ExportType("Sekai", (UserType*)type_of<TestClass>());
	mgr->RunScript("py_methods");
}

BOOST_FIXTURE_TEST_CASE( MembersTest, ScriptFixture )
{
	mgr->ExportType("Sekai", (UserType*)type_of<TestClass>());
	mgr->RunScript("py_members");
}

BOOST_FIXTURE_TEST_CASE( ArgumentsTest, ScriptFixture )
{
	mgr->ExportType("Sekai", (UserType*)type_of<TestClass>());
	mgr->RunScript("py_arguments");
}

BOOST_FIXTURE_TEST_CASE( VectorTest, ScriptFixture )
{
	mgr->ExportType("Sekai", (UserType*)type_of<VML::Vector3>());
	mgr->RunScript("py_vector");
}

BOOST_FIXTURE_TEST_CASE( UserTypeArgumentsTest, ScriptFixture )
{
	mgr->ExportType("Sekai", (UserType*)type_of<TestPlayer>());
	mgr->ExportType("Sekai", (UserType*)type_of<VML::Vector3>());
	mgr->RunScript("py_utargs");
}

BOOST_FIXTURE_TEST_CASE( PointerArgsTest, ScriptFixture )
{
	mgr->ExportType("Sekai", (UserType*)type_of<TestPlayer>());
	mgr->ExportType("Sekai", (UserType*)type_of<VML::Vector3>());
	mgr->RunScript("py_ptrargs");
}

BOOST_FIXTURE_TEST_CASE( CustomizationTest, ScriptFixture )
{
	mgr->ExportType("Sekai", (UserType*)type_of<VML::Vector3>());
	mgr->RunScript("py_customization");
}

BOOST_FIXTURE_TEST_CASE( InheritanceTest, ScriptFixture )
{
	mgr->ExportType("Sekai", (UserType*)type_of<TestInh_Derived>());
	mgr->ExportType("Sekai", (UserType*)type_of<VML::Vector3>());
	mgr->RunScript("py_inheritance");
}

BOOST_FIXTURE_TEST_CASE( EnumExportTest, ScriptFixture )
{
	mgr->ExportType("Sekai", (UserType*)type_of<TestEnum>());
	mgr->RunScript("py_enumtest");
}

BOOST_FIXTURE_TEST_CASE( FuncImportTest, ScriptFixture )
{
	mgr->RunScript("py_funcaccess");

	int a = 13;
	int r;

	SScriptAny any;
	BOOST_REQUIRE(mgr->FindEntry("py_funcaccess.run", any));

	ValueTypePair args[] = { make_typed_pair(a) };
	ValueTypePair ret = make_typed_pair(r);

	any.asFunction()->Invoke(args, 1, &ret);
	BOOST_CHECK_EQUAL(r, 12);
}

BOOST_FIXTURE_TEST_CASE( TableAccessTest, ScriptFixture )
{
	mgr->RunScript("py_tableaccess");

	SScriptAny any;
	BOOST_REQUIRE(mgr->FindEntry("py_tableaccess.d", any));

	BOOST_CHECK( any.asTable()->HasEntry(0) );

	int val;
	BOOST_CHECK( any.asTable()->GetEntry(0, val) );
	BOOST_CHECK_EQUAL( val, 23 );

	BOOST_CHECK( ! any.asTable()->HasEntry(1) );
	BOOST_CHECK( any.asTable()->HasEntry("Roma") );
}

BOOST_FIXTURE_TEST_CASE( ClassImportTest, ScriptFixture )
{
	mgr->RunScript("py_classaccess");

	SScriptAny inst_any;
	BOOST_REQUIRE( mgr->CreateInstance("py_classaccess.TestClass", inst_any) );

	SScriptAny setter_any;
	BOOST_CHECK( inst_any.asObject()->GetMember("setData", setter_any) );
	SScriptAny getter_any;
	BOOST_CHECK( inst_any.asObject()->GetMember("getData", getter_any) );

	int dataVal = 10;
	ValueTypePair args[] = { make_typed_pair(dataVal) };
	setter_any.asFunction()->Invoke(args, 1, 0);

	int r = -1;
	ValueTypePair ret = make_typed_pair(r);
	getter_any.asFunction()->Invoke(0, 0, &ret);
	BOOST_CHECK_EQUAL( r, 10 );

	SScriptAny field_any;
	BOOST_CHECK( inst_any.asObject()->GetMember("mData", field_any) );
	BOOST_CHECK_EQUAL( field_any.asInt(), 10 );
}

BOOST_FIXTURE_TEST_CASE( VariableExportTest, ScriptFixture )
{
	mgr->ExportType("Sekai", (UserType*)type_of<VML::Vector3>());
	mgr->ExportType("Sekai", (UserType*)type_of<TestPlayer>());

	TestPlayer pl;
	TestPlayer* ppl = &pl;
	mgr->ExportVariable("Sekai", "g_player", make_typed_pair(ppl)) ;

	mgr->RunScript("py_varexport");
}

BOOST_FIXTURE_TEST_CASE( InterfaceImportTest, ScriptFixture )
{
	mgr->ExportType("Sekai", (UserType*)type_of<ITestInterface>());
	mgr->ExportType("Sekai", (UserType*)type_of<TestInterfaceFactory>());
	mgr->ExportType("Sekai", (UserType*)type_of<com_ptr<ITestInterface> >());
	mgr->RunScript("py_interface");
}

BOOST_FIXTURE_TEST_CASE( DocTest, ScriptFixture )
{
	mgr->ExportType("Sekai", (UserType*)type_of<TestDocClass>() );
	mgr->RunScript("py_doctest");
}

struct ScriptModuleFixture : public ScriptFixture
{
	ScriptModuleFixture()
	{
		mgr->ExportModule("TestModule", test);
	}
};


BOOST_FIXTURE_TEST_CASE(ExportModule, ScriptModuleFixture)
{
}

BOOST_FIXTURE_TEST_CASE(ModuleCreate, ScriptModuleFixture)
{
	mgr->RunScript("py_module_creation");
}

BOOST_FIXTURE_TEST_CASE(ModuleExportInstance, ScriptModuleFixture)
{
}

struct ModuleLibraryFixture : public ScriptFixture
{
	ModuleLibraryFixture()
	{
		mgr->ExportType("Module", (UserType*)type_of<Module::GUID>());
	}
};

BOOST_FIXTURE_TEST_CASE(Guid, ModuleLibraryFixture)
{
	mgr->RunScript("py_module_guid");
}

BOOST_AUTO_TEST_SUITE_END();
