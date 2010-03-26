/*========================================================
* BundleRegParser.cpp
* @author Sergey Mikhtonyuk
* @date 17 December 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "BundleRegParser.h"

namespace Framework
{
	//////////////////////////////////////////////////////////////////////////

	BundleRegParser::BundleRegParser(const char* file)
	{
		TiXmlDocument doc;
		doc.LoadFile(file);
		doc.Accept(this);
	}

	//////////////////////////////////////////////////////////////////////////

	bool BundleRegParser::VisitEnter(const TiXmlDocument &doc)
	{
		return true;
	}

	//////////////////////////////////////////////////////////////////////////

	bool BundleRegParser::VisitExit(const TiXmlDocument &doc)
	{
		return true;
	}

	//////////////////////////////////////////////////////////////////////////

	bool BundleRegParser::VisitEnter(const TiXmlElement &element, const TiXmlAttribute *firstAttribute)
	{
		return true;
	}

	//////////////////////////////////////////////////////////////////////////

	bool BundleRegParser::VisitExit(const TiXmlElement &element)
	{
		return true;
	}

	//////////////////////////////////////////////////////////////////////////

	bool BundleRegParser::Visit(const TiXmlText &text)
	{
		return true;
	}

	//////////////////////////////////////////////////////////////////////////

	bool BundleRegParser::Visit(const TiXmlDeclaration& declaration)
	{
		return true;
	}

	//////////////////////////////////////////////////////////////////////////

	bool BundleRegParser::Visit(const TiXmlComment& comment)
	{
		return true;
	}

	//////////////////////////////////////////////////////////////////////////

	bool BundleRegParser::Visit(const TiXmlUnknown& unknown)
	{
		return true;
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace
