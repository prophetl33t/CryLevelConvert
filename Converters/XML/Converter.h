#pragma once
#include "CLCHeaders.h"
#include <fstream>
#include <vector>

/// <summary>
///Base class for all XML converters.
/// </summary>
class XMLConverter
{
protected:
	std::string class_name;
	pugi::xml_document doc;
	pugi::xml_parse_result res;
	std::string xml_path;
	inline virtual bool Convert() = 0;
public:
	virtual bool ConvertFromDisk(const std::string& path_in);
	virtual bool ConvertFromDisk(const std::vector<std::string>& paths_in);
	//virtual bool ConvertFromMemory();
	XMLConverter(const std::string& path_in);
	XMLConverter();
};

