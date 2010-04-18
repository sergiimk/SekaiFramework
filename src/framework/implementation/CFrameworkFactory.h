/*========================================================
* CFrameworkFactory.h
* @author Sergey Mikhtonyuk
* @date 21 November 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _CFRAMEWORKFACTORY_H__
#define _CFRAMEWORKFACTORY_H__

#include "IFrameworkFactory.h"
#include "module/implementations.h"

using namespace module;

namespace Framework
{

	/// System bundle activator implementation
	/** @ingroup Framework */
	class NOVTABLE CFrameworkFactory
		: public ComRootObject<module::MultiThreadModel>
		, public IFrameworkFactory
	{
		DECLARE_IMPLEMENTATION(CFrameworkFactory)

		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(IFrameworkFactory)
		END_INTERFACE_MAP()

		virtual com_ptr<IFramework> NewFramework(int argc, char *argv[], const char* settingsFile);
	};

} // namespace

#endif // _CFRAMEWORKFACTORY_H__
