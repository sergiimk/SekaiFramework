/*========================================================
* test_interfaces.h
* @author Sergey Mikhtonyuk
* @date 06 November 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _TEST_INTERFACES_H__
#define _TEST_INTERFACES_H__

#include "module/interfaces.h"
#include "reflection/reflection.h"

sf_interface IFancyInterface : public module::IUnknown
{
	sf_uuid("79189e96-9353-4177-9d7d-1530bf94eb59")

	virtual int DoFancyThings(int a, int b) = 0;
};

reflect_class(IFancyInterface, "IFancyInterface")
	.def_method("DoFancyThings", DoFancyThings)
end_reflection()

#endif // _TEST_INTERFACES_H__