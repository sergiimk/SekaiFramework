/*========================================================
* test_implementations.cpp
* @author Sergey Mikhtonyuk
* @date 06 November 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "test_implementations.h"

//////////////////////////////////////////////////////////////////////////

int CFancyAdder::DoFancyThings(int a, int b)
{
	lastResult = a + b;
	return lastResult;
}

//////////////////////////////////////////////////////////////////////////