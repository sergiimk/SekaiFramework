/*========================================================
* BundleRegParser.h
* @author Sergey Mikhtonyuk
* @date 17 December 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#ifndef _BUNDLEREGPARSER_H__
#define _BUNDLEREGPARSER_H__

#include "filesystem/FileSystem.h"
#include "tinyxml/tinyxml.h"

using namespace Module;
using namespace filesystem;

namespace Framework
{
	/// Parser for bundle registry files
	/** @ingroup Framework */
	class BundleRegParser : public TiXmlVisitor
	{
	public:
		BundleRegParser(const char* file);
		virtual bool VisitEnter(const TiXmlDocument& doc);
		virtual bool VisitExit(const TiXmlDocument& doc);
		virtual bool VisitEnter(const TiXmlElement& element, const TiXmlAttribute* firstAttribute);
		virtual bool VisitExit(const TiXmlElement& element);
		virtual bool Visit(const TiXmlDeclaration& declaration);
		virtual bool Visit(const TiXmlText& text);
		virtual bool Visit(const TiXmlComment& comment);
		virtual bool Visit(const TiXmlUnknown& unknown);
	};

} // namespace

#endif // _BUNDLEREGPARSER_H__
