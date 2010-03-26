/*========================================================
* CPluginManager.h
* @author Sergey Mikhtonyuk
* @date 15 November 2008
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/

#ifndef _CPLUGINMANAGER_H__
#define _CPLUGINMANAGER_H__

#include "IPluginManager.h"
#include "CoreParams.h"
#include "module/implementations.h"
#include "module/intellectual.h"
#include "filesystem/filesystem.h"
#include "CPluginDefVisitor.h"
#include "platform/hash_map.h"
#include <vector>
#include "common/stringutils.h"

namespace Extensions
{
		class CExtension;
		class CPluginShadow;
		class CExtensionPoint;

		/// Implementation of IPluginManager interface
		/** Implements the managing system of plug-ins
	      * @ingroup Extensions */
		class NOVTABLE CPluginManager :
			public Module::ComRootObject<>,
			public IPluginManager
		{
		public:
			DECLARE_IMPLEMENTATION(CPluginManager)

			BEGIN_INTERFACE_MAP()
				INTERFACE_ENTRY(IPluginManager)
			END_INTERFACE_MAP()

			CPluginManager();
			virtual ~CPluginManager();

			/// Start routine of plug-in manager
			void Run(const char* paramsFile);

			IPluginShadow* FindPluginShadow(const std::string &name);

			IExtensionPoint* FindExtensionPoint(const std::string &name);

		public:
			/// Executed on start to initialize core plug-ins
			Module::HResult	LoadCorePlugins();

			/// Loads all dynamic plug-ins
			void			LoadPlugins();

			/// Find all xml files
			void			FindDefinitionFiles(std::vector<filesystem::path>& files);

			/// Parses the definition files
			void			ParseDefinitions(	std::vector<CPluginDefVisitor>& visitors,
												std::vector<filesystem::path>& files);

			/// Creates shadows from visitors
			void			CreateShadows(std::vector<CPluginDefVisitor>& visitors);

			/// Binds extenders to loaded shadows
			void			BindPlugins(std::vector<CPluginDefVisitor>& visitors);

			/// Creates plugin shadow
			CPluginShadow*	CreatePluginShadow(const std::string& name, int version);

			/// Creates extension
			CExtension*		CreateExtension(CPluginShadow *extender, IExtensionPoint* exPoint, const Module::GUID& classID, std::map<std::string, std::string>& paramMap);

			/// Creates extension point
			CExtensionPoint* CreateExtensionPoint(CPluginShadow *provider, const std::string& name, const Module::GUID& iid);

			/// Breaks full extension point path
			void			ParseExtesionPoint(const std::string& str, std::string& plugin, std::string& point);

			/// Initialization of loaded plugin
			Module::HResult	OnPluginLoad(CPluginShadow *pShadow);

		protected:
			typedef std::vector<CPluginShadow*> TCreationStack;
			typedef std::hash_map<std::string, CPluginShadow*, str_hash> TShadowMap;
			typedef std::hash_multimap<std::string, std::pair<CPluginShadow*, Module::GUID>, str_hash> TExtendersMap;

			CoreParams*		mCoreParams;	///< Settings that will be used for core initialization
			TShadowMap		mShadows;		///< Shadows
			TExtendersMap	mExtendersMap;	///< Extenders
			TCreationStack	mCreationStack;	///< Stack is used to unload libraries in reverse to creation order
		};

} // namespace


#endif // _CPLUGINMANAGER_H__
