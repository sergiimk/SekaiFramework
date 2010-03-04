/*========================================================
* VML_ios.h
* @author Sergey Mikhtonyuk
* @date 19 June 2009
=========================================================*/
#ifndef _VML_IOS_H__
#define _VML_IOS_H__

#include "vml/vml.h"
#include <iostream>

//////////////////////////////////////////////////////////////////////////
inline std::ostream& operator<<(std::ostream& os, const VML::Vector3& val)
{
	os<<val.getX()<<' '<<val.getY()<<' '<<val.getZ();
	return os;
}

inline std::istream& operator>>(std::istream& os, VML::Vector3& val)
{
	return os;
}


/*std::ostream& operator<<(std::ostream& os, const VML::Vector4& val);
std::istream& operator>>(std::istream& os, VML::Vector4& val);

std::ostream& operator<<(std::ostream& os, const VML::Point2& val);
std::istream& operator>>(std::istream& os, VML::Point2& val);

std::ostream& operator<<(std::ostream& os, const VML::Point3& val);
std::istream& operator>>(std::istream& os, VML::Point3& val);

std::ostream& operator<<(std::ostream& os, const VML::Quat& val);
std::istream& operator>>(std::istream& os, VML::Quat& val);*/
//////////////////////////////////////////////////////////////////////////

#endif // _VML_IOS_H__
