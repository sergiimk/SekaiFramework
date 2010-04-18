/*========================================================
* CExtension.h
* @author Sergey Mikhtonyuk
* @date 29 November 2008
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _CEXTENSION_H__
#define _CEXTENSION_H__

#include "IExtension.h"
#include "module/implementations.h"
#include <boost/scoped_ptr.hpp>

namespace Extensions
{
	
	/// Implementation of IExtension interface
	/** @ingroup Extensions */
	class NOVTABLE CExtension : 
		public module::ComRootObject<>,
		public IExtension
	{
		typedef std::map<std::string, std::string> TParameterMap;

	public:
		DECLARE_IMPLEMENTATION(CExtension)
	
		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(IExtension)
		END_INTERFACE_MAP()

		IPluginShadow*		Extender()			{ return pExtender; }
		IExtensionPoint*	ExtensionPoint()	{ return pExtensionPoint; }
		const module::guid&	ImplClassID()		{ return mImplClassID; }
		const char*			getParameter(const char* name)		
		{
			TParameterMap::const_iterator it = mParameterMap.find(name);
			return (it == mParameterMap.end()) ? 0 : it->second.c_str();
		}
	
	/* internal: */
		IPluginShadow*		pExtender;
		IExtensionPoint*	pExtensionPoint;
		module::guid			mImplClassID;
		TParameterMap		mParameterMap;
	};


} // namespace


#endif // _CEXTENSION_H__