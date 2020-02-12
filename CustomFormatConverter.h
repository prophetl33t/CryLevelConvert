#pragma once
#include "CLCHeaders.h"
class CLCDumpConverter
{
private:
	std::ofstream fstream_out;
	std::ifstream fstream_in;
	std::string buf;
public:
	CLCDumpConverter(std::string_view path_in, std::string_view path_out);
	virtual bool Convert() = 0;
};

