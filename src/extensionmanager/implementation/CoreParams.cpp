/*========================================================
* CoreParams.cpp
* @author Sergey Mikhtonyuk
* @date 21 May 2009
*
* Copyrights (c) Sergey Mikhtonyuk 2007-2010.
* Terms of use, copying, distribution, and modification
* are covered in accompanying LICENSE file
=========================================================*/
#include "CoreParams.h"
#include "GlobalEnvironment.h"
#include "filesystem/filesystem.h"
#include "tinyxml/tinyxml.h"

namespace Extensions
{
	//////////////////////////////////////////////////////////////////////////
	using namespace Module;
	using namespace filesystem;
	//////////////////////////////////////////////////////////////////////////

	bool CoreParams::ShouldLoad(const std::string& plugin) const
	{
		return mLoadOnlyPlugins.find(plugin) != mLoadOnlyPlugins.end();
	}

	//////////////////////////////////////////////////////////////////////////

	bool CoreParams::ParseFile(const char* file)
	{
		// Init xml adapter
		TiXmlDocument doc;

		try 
		{ 
			doc.LoadFile(file); 
			if(!doc.FirstChild()) 
				return false;
		}
		catch (...) 
		{ 
			return false; 
		}

		TiXmlElement* xml = doc.FirstChildElement();

		// Parse file
		TiXmlElement* lo = xml->FirstChildElement("loadonly");
		if(!lo) return false;

		TiXmlElement* pl = lo->FirstChildElement("plugin");
		while(pl)
		{
			const char* name = pl->Attribute("name");
			if(name)
				mLoadOnlyPlugins.insert(name);

			pl = pl->NextSiblingElement("plugin");
		}

		return mLoadOnlyPlugins.size() != 0;
	}

	//////////////////////////////////////////////////////////////////////////

} // namespace
