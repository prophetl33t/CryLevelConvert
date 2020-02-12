#pragma once
#include "pugixml.hpp"
#include <random>
#include <fstream>
#include <string_view>

const int auto_exit = 0;

namespace cry_fname
{
	namespace in
	{
		const std::string MISSIONXML = "mission_mission0.xml";
		const std::string AIDUMP = "ai_points_dump.txt";
		const std::string MDATA = "moviedata.xml";
		const std::string GEOMDUMP = "dump_ent.txt";
		const std::string TERRAINDUMP = "dump_terrain.txt";
		const std::string VEGDUMP = "veg_dump.txt";
		const std::string LVLDATA = "leveldata.xml";
		const std::string ENTARCFOLDER = "EntityArchetypes";
	}
	namespace out
	{
		const std::string MISSIONXML = "Layer_Mission.lyr";
		const std::string TOD = "TimeOfDay.tod";
		const std::string AIDUMP = "Layer_AI_Markup.lyr";
		const std::string MDATA = "Layer_MovieData.lyr";
		const std::string GEOMDUMP = "Layer_Geom.lyr";
		const std::string TERRAINDUMP = "terrain.raw";
		const std::string VEGDUMP = "VegetationData.veg";
		const std::string TERLAYDATA = "TerrainLayerTexInfo.lay";
		const std::string ENTARCCACHE = "EntityArchetypeData.clcdb";
	}
	const std::string LEVELPAK = "level.pak";
}

namespace Util
{
	//Original code of GenerateRandomGUID is taken from : https://gist.github.com/fernandomv3/46a6d7656f50ee8d39dc
	//Changed random to a better one and replaced "uuid" with "guid"

	std::string GenerateRandomGUID(bool add_brackets = 0); //Generate random GUID

	std::string GenerateGUIDFrom64(const std::string& guid_64, bool add_brackets = 0); //Generate EntityGuid from EntityGUID_64 being used as GUID in flowgraph

	pugi::xml_document CreateLayerFile(std::string_view name, std::string_view guid = Util::GenerateRandomGUID(true)); //Create layer xml document with pre-generated layer structure

	int DetectDataType(const std::string& path); //Detects data type of provided file.

	namespace DataTypes
	{
		enum DATA_TYPES { DIR, MDATA, MISSION, PAK, AIDUMP, TERRAINDUMP, VEGDUMP, TERLAYDUMP, GEOMDUMP, UNKNOWN };
	}

	std::string PathWithoutFilename(std::string& path); //Trunc filename in path

	void DelayedExit(); //Replacement for system("pause")
}
