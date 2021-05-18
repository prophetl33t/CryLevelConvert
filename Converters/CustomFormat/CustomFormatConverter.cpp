#include "CustomFormatConverter.h"

CustomFormatConverter::CustomFormatConverter(std::string_view path_in, std::string_view path_out)
{
	fstream_out.open(path_out.data());
	fstream_in.open(path_in.data());
}
