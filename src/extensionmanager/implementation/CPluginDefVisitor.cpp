/*========================================================
* CPluginDefVisitor.cpp
* @author Sergey Mikhtonyuk
* @date 26 November 2008
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/

#include "CPluginDefVisitor.h"
#include "module/exception.h"
#include <cctype>
#include <algorithm>
#include <functional>
#include <boost/bind.hpp>

namespace Extensions
{

	/*=======================================================================
	 =  Flow functions
	 ==============*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/

	bool CPluginDefVisitor::VisitEnter(const TiXmlDocument &doc)
	{
		return true;
	}

	bool CPluginDefVisitor::VisitExit(const TiXmlDocument &doc)
	{
		return true;
	}

	bool CPluginDefVisitor::VisitEnter(const TiXmlElement &element, const TiXmlAttribute *firstAttribute)
	{
		if(element.ValueStr() == _plugin)
			return ProcessPluginDef(element, firstAttribute);
		else if (element.ValueStr() == _prereq)
			return ProcessPrerequisites(element, firstAttribute);
		else if (element.ValueStr() == _exports)
			return ProcessExports(element, firstAttribute);
		else if (element.ValueStr() == _provides)
			return ProcessProvides(element, firstAttribute);
		else if (element.ValueStr() == _extends)
			return ProcessExtends(element, firstAttribute);

		return false;
	}

	bool CPluginDefVisitor::VisitExit(const TiXmlElement &element)
	{
		return true;
	}

	bool CPluginDefVisitor::Visit(const TiXmlText &text)
	{
		return true;
	}

	bool CPluginDefVisitor::Visit(const TiXmlDeclaration& declaration)
	{
		return true;
	}

	bool CPluginDefVisitor::Visit(const TiXmlComment& comment)
	{
		return true;
	}

	bool CPluginDefVisitor::Visit(const TiXmlUnknown& unknown)
	{
		return true;
	}

	/*=======================================================================
	 =  Parsing functions
	 ==============*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
	bool CPluginDefVisitor::ProcessPluginDef(const TiXmlElement &element, const TiXmlAttribute *firstAttribute)
	{
		Version = -1;

		const TiXmlAttribute* pAttr = firstAttribute;
		while(pAttr)
		{
			if(pAttr->NameStr() == _name) // Read plugin name
				PluginName = pAttr->ValueStr();
			else if (pAttr->NameStr() == _version) // Read version
				if(pAttr->QueryIntValue(&Version) != TIXML_SUCCESS)
					ThrowHelper(_invalid_format);

			pAttr = pAttr->Next();
		}

		// Validate all params are set
		if(PluginName.size() == 0 || Version == -1)
			ThrowHelper(_not_enough_params);

		ToLower(PluginName);

		return true;
	}



	bool CPluginDefVisitor::ProcessPrerequisites(const TiXmlElement &element, const TiXmlAttribute *firstAttribute)
	{
		const TiXmlElement *pReq = element.FirstChildElement();
		while(pReq)
		{
			PrerequisiteDef* definition = new PrerequisiteDef;
			Prerequisites.push_back(definition);

			const TiXmlAttribute *pAttr = pReq->FirstAttribute();

			while(pAttr)
			{
				if(pAttr->NameStr() == _plugin)
				{
					definition->Plugin = pAttr->ValueStr();
					ToLower(definition->Plugin);
				}
				pAttr = pAttr->Next();
			}

			if(definition->Plugin.size() == 0)
				ThrowHelper(_invalid_format); // No need to delete, pointer is protected by adding to collection first

			pReq = pReq->NextSiblingElement();
		}
		return false;
	}



	bool CPluginDefVisitor::ProcessExports(const TiXmlElement &element, const TiXmlAttribute *firstAttribute)
	{
		const TiXmlElement *pReq = element.FirstChildElement();
		while(pReq)
		{
			const TiXmlAttribute *pAttr = pReq->FirstAttribute();
			ExportDef* definition = new ExportDef;
			Exports.push_back(definition);

			while(pAttr)
			{
				if(pAttr->NameStr() == _name)
				{
					definition->ClassName = pAttr->ValueStr();
				}
				else if(pAttr->NameStr() == _classid)
				{
					definition->ClassID = pAttr->ValueStr();
				}

				pAttr = pAttr->Next();
			}

			if(definition->ClassID.size() == 0 ||
				!definition->ClassGUID.FromString(definition->ClassID.c_str()))
				ThrowHelper("Invalid GUID format, parsing failed");

			pReq = pReq->NextSiblingElement();
		}
		return false;
	}


	bool CPluginDefVisitor::ProcessProvides(const TiXmlElement &element, const TiXmlAttribute *firstAttribute)
	{
		ExtensionPointDef* definition = new ExtensionPointDef;
		ExtensionPoints.push_back(definition);
		std::string siid;

		while(firstAttribute)
		{
			if(firstAttribute->NameStr() == _point)
			{
				definition->PointID = firstAttribute->ValueStr();
				ToLower(definition->PointID);
			}
			else if(firstAttribute->NameStr() == _iid)
			{
				siid = firstAttribute->ValueStr();
			}

			firstAttribute = firstAttribute->Next();
		}

		if(definition->PointID.size() == 0 ||
			!definition->InterfaceID.FromString(siid.c_str()))
			ThrowHelper("Invalid GUID format, parsing failed");

		return false;
	}



	bool CPluginDefVisitor::ProcessExtends(const TiXmlElement& element, const TiXmlAttribute* firstAttribute)
	{
		ExtensionDef* definition = new ExtensionDef;
		Extensions.push_back(definition);
		std::string classid;

		// Load point's name
		while(firstAttribute)
		{
			if(firstAttribute->NameStr() == _point)
			{
				definition->PointID = firstAttribute->ValueStr();
				ToLower(definition->PointID);
			}
			else if(firstAttribute->NameStr() == _classid)
			{
				classid = firstAttribute->ValueStr();
			}

			firstAttribute = firstAttribute->Next();
		}

		// Validate point
		if(definition->PointID.size() == 0)
			ThrowHelper(_not_enough_params);

		if(definition->PointID[0] == ':' || definition->PointID[definition->PointID.size() - 1] == ':')
			ThrowHelper(_invalid_format);

		// Translate classid to class GUID
		if(classid.size() != 0)
		{
			TExports::const_iterator it = std::find_if(Exports.begin(), Exports.end(),
				boost::bind(&ExportDef::ClassName, _1) == classid);

			if(it != Exports.end())
				definition->ClassID = (*it)->ClassGUID;
			else if(!definition->ClassID.FromString(classid.c_str()))
				ThrowHelper(_invalid_format);
		}
		else
		{
			definition->ClassID.SetZero();
		}

		// Fill the property map

		const TiXmlElement* pElems = element.FirstChildElement();
		while(pElems)
		{
			if(!pElems->FirstChild())
				ThrowHelper(_invalid_format);

			const std::string& name = pElems->ValueStr();
			const std::string* pvalue = &pElems->FirstChild()->ValueStr();

			// Convert all class names in property values to class'es GUIDs
			TExports::const_iterator it = std::find_if(Exports.begin(), Exports.end(),
				boost::bind(&ExportDef::ClassName, _1) == *pvalue);

			if(it != Exports.end())
				pvalue = &(*it)->ClassID;

			definition->PropertyMap.insert(std::make_pair(name, *pvalue));
			pElems = pElems->NextSiblingElement();
		}

		return false;
	}


	void CPluginDefVisitor::ThrowHelper(const char* message)
	{
		throw Module::RuntimeException(message);
	}

	CPluginDefVisitor::~CPluginDefVisitor()
	{
		for(size_t i = 0; i < Exports.size(); ++i)
			if(Exports[i]) delete Exports[i];
		for(size_t i = 0; i < Extensions.size(); ++i)
			if(Extensions[i]) delete Extensions[i];
		for(size_t i = 0; i < Prerequisites.size(); ++i)
			if(Prerequisites[i]) delete Prerequisites[i];
		for(size_t i = 0; i < ExtensionPoints.size(); ++i)
			if(ExtensionPoints[i]) delete ExtensionPoints[i];
	}

	void CPluginDefVisitor::ToLower(std::string &str)
	{
		std::transform(str.begin(), str.end(), str.begin(), tolower);
	}

	const std::string CPluginDefVisitor::_name("name");
	const std::string CPluginDefVisitor::_plugin("plugin");
	const std::string CPluginDefVisitor::_version("version");
	const std::string CPluginDefVisitor::_prereq("prerequisites");
	const std::string CPluginDefVisitor::_exports("exports");
	const std::string CPluginDefVisitor::_classid("classid");
	const std::string CPluginDefVisitor::_provides("provides");
	const std::string CPluginDefVisitor::_point("point");
	const std::string CPluginDefVisitor::_iid("iid");
	const std::string CPluginDefVisitor::_extends("extends");

	const char* CPluginDefVisitor::_not_enough_params = "Not enough parameters";
	const char* CPluginDefVisitor::_invalid_format = "Invalid format";
} // namespace
