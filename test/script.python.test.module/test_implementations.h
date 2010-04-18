/*========================================================
* test_implementations.h
* @author Sergey Mikhtonyuk
* @date 06 November 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _TEST_IMPLEMENTATIONS_H__
#define _TEST_IMPLEMENTATIONS_H__

#include "test_interfaces.h"
#include "module/implementations.h"

class NOVTABLE CFancyAdder : 
	public module::ComRootObject<>,
	public IFancyInterface
{
public:
	
	DECLARE_IMPLEMENTATION(CFancyAdder)

	BEGIN_INTERFACE_MAP()
		INTERFACE_ENTRY(IFancyInterface)
	END_INTERFACE_MAP()

	int DoFancyThings(int a, int b);

	int getLastResult() const { return lastResult; }

	int lastResult;
};

// {e051c779-64dc-4da3-99bb-01a7b7dcf603} 
static const module::guid CLSID_FancyAdder = { 0xe051c779, 0x64dc, 0x4da3, { 0x99, 0xbb, 0x01, 0xa7, 0xb7, 0xdc, 0xf6, 0x03 } };

reflect_class(CFancyAdder, "CFancyAdder")
	.def_base(IFancyInterface)
	.def_create_inst()
	.def_accessor_ro("LastResult", getLastResult)
end_reflection()

#endif // _TEST_IMPLEMENTATIONS_H__