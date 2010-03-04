/*========================================================
* VML_reflect.h
* @author Sergey Mikhtonyuk
* @date 07 July 2009
=========================================================*/
#ifndef _VML_REFLECT_H__
#define _VML_REFLECT_H__

#include "reflection.h"
#include "vml/vml.h"
#include "vml_ios.h"

typedef float (VML::Vector3::*get)();
typedef void (VML::Vector3::*set)(float);

reflect_class(VML::Vector3)
	map_ctor_alloc(VML::AlignedAllocator)
	map_ctor_alloc(VML::AlignedAllocator, float, float, float)
	map_accessor_r("x", get, getXf, set, setX)
	map_accessor_r("y", get, getYf, set, setY)
	map_accessor_r("z", get, getZf, set, setZ)
	map_parsable()
end_reflection()

//////////////////////////////////////////////////////////////////////////

#endif // _VML_REFLECT_H__
