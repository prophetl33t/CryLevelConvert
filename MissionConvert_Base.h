#pragma once
#include "Converter.h"
#include <unordered_map>
#include "EntArchetypeObtainer.h"


static std::map <std::string, std::string> map_ent = //Some entites have different classes in editor and in game!
{
{ "EnvironmentLight","EnvironmentProbe" },
{ "AreaShape","Shape" },
{ "AITerritory", "Shape" },
{ "LightShape", "Shape" },
{ "RopeEntity", "Rope" }
};


/// <summary>
/// Base class for converter of mission_mission0.xml from different verisons of CE
/// </summary>
class MissionConvert_Base : public XMLConverter
{
protected:
	static EntArchetypeObtainer entarc; //Database is shared across different instances of MissionConvert.
	std::vector <std::string> m_layer_names; //if ent. contains lyr name - write to its own file!
	std::map <std::string, std::string> m_map_guid_64;
	std::map <std::string, std::string> m_map_id_parent;
	std::fstream tod_stream_out;
	inline virtual bool Convert() = 0;
public:
	virtual void ExtractTOD() = 0;
	using XMLConverter::XMLConverter; //Deriving constructor
};