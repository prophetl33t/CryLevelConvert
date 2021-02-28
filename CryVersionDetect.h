#pragma once
#include <vector>
#include <array>
#include <string>
#include <string_view>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <sstream>
#include <map>
#include "pugixml.hpp"

namespace fs = std::filesystem;

enum EngineGeneration { CE1 = 1, CE2, CE3, CE4, CE5 = 5 };

struct EngineVersionInfo
{
	EngineGeneration engine_generation; //Generation of engine (e.g. CE3)
	std::string game_name; //Name of game (e.g. Warface)
	std::string engine_version; //Full version of engine in string format
	std::string desc; //Additional description
	std::string level_name; //Name of level where engine version was used
	bool is_crytek_build = false; //Flag is set to true if game is made by crytek or uses internal engine version

	EngineVersionInfo() {};
	EngineVersionInfo(EngineGeneration eng_gen, const char* game_name, const char* eng_version, const char* desc, const char* levelname, bool crytek_build) :
		engine_generation(eng_gen), game_name(game_name), engine_version(eng_version), desc(desc), level_name(levelname), is_crytek_build(crytek_build) {};

	void Print(bool verbose = false)
	{
		std::cout << "Engine version: " << engine_version << "\n";
		if (verbose)
		{
			std::cout << "Engine generation: CE" << engine_generation <<
				"\nGame name: " << game_name <<
				"\nAdditional info: " << desc <<
				(is_crytek_build ? "\nVersion of engine used internally by Crytek (for games like Crysis)" : "\nFreeSDK/EAAS/CE5 or other public version");
		}
	}
};

extern std::vector<EngineVersionInfo> KNOWN_VERSIONS;

namespace EngineVersionUtils
{
	size_t FindNthOccurence(std::string_view str, char ch, int num);
	EngineVersionInfo& FindInfoByVersion(std::string& ver);
	void SetDefaultEngineVersionDB();
	void LoadEngineVersionDB(std::string_view path);
	void CreateEngineVersionDB(const char* path);
	void CreateVersionInfoFromString(std::string_view str);
	EngineGeneration GetEngineGenFromMission(pugi::xml_document mission_xml);
};