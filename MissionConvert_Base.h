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

const fs::path path_entfiles = "Entities";

/// <summary>
/// Base class for converter of mission_mission0.xml from different verisons of CE.
/// </summary>
class MissionConvert_Base : public XMLConverter
{
protected:
	static EntArchetypeObtainer entarc; //Database is shared across different instances of MissionConvert.
	std::vector <std::string> m_layer_names; //if ent. contains lyr name - write to its own file!
	std::map <std::string, std::string> m_map_guid_64;
	std::map <std::string, std::string> m_map_id_parent;
	std::fstream tod_stream_out;
	//Instead of redefining whole Convert() method sometimes it is much easier to inject needed instructions in derived classes through this method. For example CE3 and CE5 conversions are almost identical. It executes after all conversions done. Look into MissionConvert_Base::Convert() for more info.
	virtual void VersionSpecificInstructions();
	virtual bool Convert();
	bool SaveToDisk();
public:
	virtual void ExtractTOD();
	using XMLConverter::XMLConverter; //Deriving constructor
};