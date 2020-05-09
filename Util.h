#pragma once
#include "pugixml.hpp"
#include <random>
#include <fstream>
#include <iostream>
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

	//These enums are in seperate namespaces in order to not pollute auto completion results (msvs shows full contents of enums even when not needed)
	namespace DataTypes
	{
		enum DATA_TYPES { DIR, MDATA, MISSION, PAK, AIDUMP, TERRAINDUMP, VEGDUMP, TERLAYDUMP, GEOMDUMP, UNKNOWN };
	}

	namespace EngineVersion
	{
		enum ENGINE_VERSION { CE3, CE5, CE2, CE1 };
	}
	
	std::string PathWithoutFilename(std::string& path); //Trunc filename in path

	void DelayedExit(); //Replacement for system("pause")

	bool replace_last(std::string& str, const std::string& replace_what, const std::string& replacement);

}

enum LOG_SEVERITY{ERROR, WARNING, INFO};

class Logger
{
private:
	std::ofstream file;
	LOG_SEVERITY m_ls = INFO;
	bool m_write_to_file = false;
	std::string_view current_name;

public:
	inline void Log(std::string_view text, LOG_SEVERITY ls = INFO)
	{
		std::cout << text << "\n";
		if (m_write_to_file)
		{
			file << text << "\n";
		}
	}

	template <class T>
	inline void Log(std::string_view text, T* p_class, LOG_SEVERITY ls = INFO )
	{
		current_name = typeid(p_class).name();
		current_name = current_name.substr(current_name.find_first_of("class") + 6, current_name.find_first_of('*') - 7);
		std::cout << '[' << current_name << "] " << text << "\n";
		if (m_write_to_file)
		{
			file << '[' << current_name << "] " << text << "\n";
		}
	}

	void SetLogSeverity(LOG_SEVERITY l)
	{
		m_ls = l;
	}

	void SetWriteToFile(bool wtf)
	{
		m_write_to_file = wtf;
	}


	Logger(bool open_file = false)
	{
		if (open_file)
		file.open("clc.log");
	}
};

extern Logger g_Log;