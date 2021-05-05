#pragma once
#include "Converter.h"
#include <regex>
/// <summary>
/// <para> XML data converter class</para> <para>Input : levelinfo.xml from level</para> <para>Output : .lay file containing data about terrain layers. REFACTOR IN FUTURE!</para>
/// </summary>
class TerrainLayerInfoConvert : public XMLConverter
{
private:
	uint16_t size;
	uint8_t zero = 0;
	uint8_t holder = 255;
	std::smatch matname_match;
	std::ifstream terlay_fstream_in;
	std::ofstream terlay_fstream_out;
	inline bool Convert() override;
	//bool Convert() override;
public:
	TerrainLayerInfoConvert();
	using XMLConverter::XMLConverter;
};

