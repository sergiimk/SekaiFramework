/*========================================================
* CExtensionPoint.h
* @author Sergey Mikhtonyuk
* @date 29 November 2008
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _CEXTENSIONPOINT_H__
#define _CEXTENSIONPOINT_H__

#include "IExtensionPoint.h"
#include "module/implementations.h"

namespace Extensions
{
	
	/// Implementation of IExtensionPoint interface
	/** @ingroup Extensions */
	class NOVTABLE CExtensionPoint : 
		public module::ComRootObject<>,
		public IExtensionPoint
	{
	public:
		DECLARE_IMPLEMENTATION(CExtensionPoint)
	
		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(IExtensionPoint)
		END_INTERFACE_MAP()

		const std::string&	ID()						{ return mName; }
		const std::string&	UniqueID()					{ return mFullName; }
		IPluginShadow*		Provider()					{ return mProvider; }
		const module::guid&	InterfaceID()				{ return mInterfaceID; }
		size_t				getExtensionCount()			{ return mExtensions.size(); }
		IExtension*			getExtension(size_t index)	{ return mExtensions[index]; }
	
	/* internal: */
		std::string					mName;
		std::string					mFullName;
		IPluginShadow*				mProvider;
		module::guid					mInterfaceID;
		std::vector<IExtension*>	mExtensions;
	};


} // namespace


#endif // _CEXTENSIONPOINT_H__