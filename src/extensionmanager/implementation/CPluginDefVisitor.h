/*========================================================
* CPluginDefVisitor.h
* @author Sergey Mikhtonyuk
* @date 26 November 2008
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _CPLUGINDEFVISITOR_H__
#define _CPLUGINDEFVISITOR_H__

#include "module/interfaces.h"
#include "tinyxml/tinyxml.h"
#include <map>
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>

namespace Extensions
{
	struct PrerequisiteDef
	{
		std::string Plugin;
	};

	struct ExportDef
	{
		std::string ClassName;
		std::string ClassID;
		Module::GUID	ClassGUID;
	};

	struct ExtensionPointDef
	{
		std::string	PointID;
		Module::GUID	InterfaceID;
	};

	struct ExtensionDef
	{
		std::string	PointID;
		Module::GUID	ClassID;
		std::map<std::string, std::string> PropertyMap;
	};

	/// Visitor class that is used to parse the plugin definitions
	/** Visitor is traversed down the XML tree and loads plugin attributes,
	  * it's export map, prerequisites, provided and used extension points 
	  * 
	  * @ingroup Extensions */
	class CPluginDefVisitor : public TiXmlVisitor
	{
	public:
		~CPluginDefVisitor();
		bool VisitEnter(const TiXmlDocument& doc);
		bool VisitExit(const TiXmlDocument& doc);

		bool VisitEnter(const TiXmlElement& element, const TiXmlAttribute* firstAttribute);
		bool VisitExit(const TiXmlElement& element);

		bool Visit(const TiXmlDeclaration& declaration);
		bool Visit(const TiXmlText& text);
		bool Visit(const TiXmlComment& comment);
		bool Visit(const TiXmlUnknown& unknown);

		void ThrowHelper(const char* message);
		bool ProcessPluginDef(const TiXmlElement& element, const TiXmlAttribute* firstAttribute);
		bool ProcessPrerequisites(const TiXmlElement& element, const TiXmlAttribute* firstAttribute);
		bool ProcessExports(const TiXmlElement& element, const TiXmlAttribute* firstAttribute);
		bool ProcessProvides(const TiXmlElement& element, const TiXmlAttribute* firstAttribute);
		bool ProcessExtends(const TiXmlElement& element, const TiXmlAttribute* firstAttribute);

	public:
		typedef std::vector<ExportDef*> TExports;
		typedef std::vector<ExtensionDef*> TExtensions;
		typedef std::vector<PrerequisiteDef*> TPrerequisites;
		typedef std::vector<ExtensionPointDef*> TExtensionPoints;

		/// \todo add version to prerequisites

		std::string						PluginName;
		int								Version;
		TExports						Exports;
		TExtensions						Extensions;
		TPrerequisites					Prerequisites;
		TExtensionPoints				ExtensionPoints;

	private:
		void ToLower(std::string& str);
		static const std::string _name;
		static const std::string _plugin;
		static const std::string _version;
		static const std::string _classid;
		static const std::string _exports;
		static const std::string _prereq;
		static const std::string _provides;
		static const std::string _point;
		static const std::string _iid;
		static const std::string _extends;

		static const char* _not_enough_params;
		static const char* _invalid_format;
	};

} // namespace

#endif // _CPLUGINDEFVISITOR_H__