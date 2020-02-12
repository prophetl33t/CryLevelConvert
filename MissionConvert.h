#pragma once
#include "Converter.h"
#include <unordered_map>
#include "EntArchetypeObtainer.h"

/// <summary>
///<para>XML Converter class</para><para>Input : mission_mission0.xml file from level.pak</para> <para>Output : .lyr files containing scripts/dynamic entities info</para>
/// </summary>
class MissionConvert : public XMLConverter
{
private:
	static EntArchetypeObtainer entarc; //Database is shared across different instances of MissionConvert.
	std::vector <std::string> m_layer_names; //if ent. contains lyr name - write to its own file!
	std::map <std::string, std::string> m_map_guid_64;
	std::map <std::string, std::string> m_map_id_parent;
	std::fstream tod_stream_out;
	inline bool Convert() override; 
public:
	void ExtractTOD();
	MissionConvert();
	using XMLConverter::XMLConverter; //Deriving constructor
};

