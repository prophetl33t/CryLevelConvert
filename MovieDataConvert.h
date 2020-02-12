#pragma once
#include "Converter.h"
/// <summary>
///<para>XML Converter class</para><para>Input : moviedata.xml file from level.pak</para> <para>Output : .lyr file containing trackview data</para>
/// </summary>
class MovieDataConvert : public XMLConverter
{
private:
	inline bool Convert() override;
	std::string mdata_guid = Util::GenerateRandomGUID(); //we need only one guid for layer, because all data from moviedata is being stored in one layer!
public:
	MovieDataConvert();
	using XMLConverter::XMLConverter; //Deriving constructor
};

