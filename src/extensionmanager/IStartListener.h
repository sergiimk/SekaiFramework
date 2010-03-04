/*========================================================
* IStartListener.h
* @author Sergey Mikhtonyuk
* @date 07 December 2008
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _ISTARTLISTENER_H__
#define _ISTARTLISTENER_H__

#include "module/interfaces.h"

namespace Extensions
{
	/// Extenders will be started on core startup
	/** @ingroup Extensions */
	sf_interface IStartListener : public Module::IUnknown
	{
		sf_uuid("36d3d4bf-5b5f-4fb0-803d-3f7b89917979")

		/// Called after core initialization
		virtual void OnStart(int argc, char *argv[]) = 0;
	};


} // namespace


#endif // _ISTARTLISTENER_H__