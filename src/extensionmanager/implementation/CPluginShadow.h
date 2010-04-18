/*========================================================
* CPluginShadow.h
* @author Sergey Mikhtonyuk
* @date 16 November 2008
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _CPLUGINSHADOW_H__
#define _CPLUGINSHADOW_H__

#include "IPluginShadow.h"
#include "module/implementations.h"
#include "common/stlutils.h"
#include <string>
#include <vector>
#include <unordered_set>
#include "module/module.h"


namespace Extensions
{

	/// Implements IPluginShadow interface
	/** Implementation of proxy object for plug-in
	  *
	  * @ingroup Extensions */
	class NOVTABLE CPluginShadow :
		public module::ComRootObject<>,
		public IPluginShadow
	{
	public:
		DECLARE_IMPLEMENTATION(CPluginShadow)

		BEGIN_INTERFACE_MAP()
			INTERFACE_ENTRY(IPluginShadow)
		END_INTERFACE_MAP()

		CPluginShadow();
		virtual	~CPluginShadow();

		const std::string& PluginName() { return mPluginName; }
		const std::string& ModuleName() { return mModuleName; }

		bool Exports(const module::guid &clsid);
		bool Provides(const std::string &expoint);
		bool Extends(const std::string &expoint);

		module::HResult CreateInstance(SF_RIID clsid, SF_RIID riid, void** ppv);
		module::HResult CreateInstance(SF_RIID riid, void** ppv);

		size_t getExtensionCount() { return mExtensions.size(); }
		IExtension* getExtension(size_t index) { return mExtensions[index]; }
		size_t getExtensionPointCount() { return mExtensionPoints.size(); }
		IExtensionPoint* getExtensionPoint(size_t index) { return mExtensionPoints[index]; }

		IExtensionPoint* FindExtensionPoint(const std::string& name);

	/* internal: */
		void			FinalConstruct(const std::string &pluginName, int version);
		module::HResult	LoadModule();
		void			Shutdown();

	/* internal: */
		int						mVersion;
		std::string				mPluginName;
		std::string				mModuleName;
		module::ModuleHandle	mModule;

		typedef std::unordered_set<module::guid, module::guid_hash> TExportTable;

		/// Provides quick look-up for exported classes
		TExportTable					mExportTable;
		std::vector<IExtension*>		mExtensions;
		std::vector<IExtensionPoint*>	mExtensionPoints;
	};

} // namespace

#endif // _CPLUGINSHADOW_H__
