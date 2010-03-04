/*========================================================
* IFrameworkFactory.h
* @author Sergey Mikhtonyuk
* @date 21 November 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _IFRAMEWORKFACTORY_H__
#define _IFRAMEWORKFACTORY_H__

#include "IFramework.h"
#include "module/intellectual.h"

namespace Framework
{

	/// Activator for the framework System Bundle
	/** @ingroup Framework */
	sf_interface IFrameworkFactory : public Module::IUnknown
	{
		sf_uuid("260ebe18-7b28-47db-b913-85e1ab9873dd")

		/// Creates a framework instance
		virtual Module::com_ptr<IFramework> NewFramework(int argc, char *argv[], const char* settingsFile) = 0;
	};

} // namespace

#endif // _IFRAMEWORKFACTORY_H__
