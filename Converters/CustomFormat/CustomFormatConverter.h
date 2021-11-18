#pragma once
#include "../../Utils/CLCHeaders.h"
class CustomFormatConverter
{
private:
	std::ofstream fstream_out;
	std::ifstream fstream_in;
	std::string buf;
public:
	CustomFormatConverter(std::string_view path_in, std::string_view path_out);
	virtual bool Convert() = 0;
};

