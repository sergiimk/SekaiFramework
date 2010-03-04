/*========================================================
* IFramework.h
* @author Sergey Mikhtonyuk
* @date 13 December 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _IFRAMEWORK_H__
#define _IFRAMEWORK_H__

#include "IBundle.h"
#include "Events.h"

namespace Framework
{

	/// Framework interface
	/** @ingroup Framework */
	sf_interface IFramework : public IBundle
	{
		sf_uuid("4b366e9b-a0be-4ce7-ab41-3d6c8e8c6877")

		/// Initialize this Framework
		virtual void Init() = 0;

		/// Wait until this Framework has completely stopped
		virtual SFrameworkEvent WaitForStop(long timeout) = 0;
	};

} // namespace

#endif // _IFRAMEWORK_H__
