#include "CryVersionDetect.h"
#include <vector>
#include <string>
#include <string_view>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <sstream>
#include "Zippy.hpp"
std::vector<EngineVersionInfo> KNOWN_VERSIONS;

size_t EngineVersionUtils::FindNthOccurence(std::string_view str, char ch, int num = 0)
{
	size_t occ = 0;
	for (int a = 0; a < str.size(); a++)
	{
		if (str[a] == ch)
		{
			occ++;
			if (occ == num)
			{
				return a;
			}
		}
	}
}

EngineVersionInfo& EngineVersionUtils::FindInfoByVersion(std::string& ver)
{
	for (auto& x : KNOWN_VERSIONS)
	{
		if (x.engine_version == ver)
		{
			return x;
		}
	}
}

void EngineVersionUtils::SetDefaultEngineVersionDB()
{
	KNOWN_VERSIONS.emplace_back(CE3, "Generic internal version", "Unknown", "1.1.1.1", "Generic version for commercial editions of CE", true);
}

void EngineVersionUtils::LoadEngineVersionDB(std::string_view path)
{
	pugi::xml_document doc;
	doc.load_file(path.data());
	auto z = doc.child("DB");
	for (auto& a : z.children())
	{
		for (auto& x : a.children())
		{
			KNOWN_VERSIONS.emplace_back(EngineGeneration(a.attribute("Gen").as_int()), a.attribute("Name").value(), x.attribute("Version").value(), x.attribute("Desc").value(), x.attribute("LevelName").value(), x.attribute("Internal").as_bool());
		}
	}
	int x = 0;
}

void EngineVersionUtils::CreateEngineVersionDB(const char* path)
{
	std::map<std::string, std::string> vers;
	pugi::xml_document doc_write;
	std::string work_dir = std::filesystem::current_path().string() + "\\";
	for (auto x : fs::recursive_directory_iterator(path))
	{
		if (std::string fname = x.path().filename().string(); fname == std::string("level.pak.zip"))
		{
			pugi::xml_document doc_read;
			Zippy::ZipArchive pak(x.path().generic_string());
			std::string xml_path = x.path().parent_path().string();
			pak.ExtractEntry("leveldata.xml", xml_path);
			doc_read.load_file((xml_path + std::string("\\leveldata.xml")).c_str());
			vers.emplace(doc_read.select_node("/LevelData").node().attribute("SandboxVersion").value(), doc_read.select_node("/LevelData/LevelInfo").node().attribute("Name").value());
		}
	}
	for (auto& x : vers)
	{
		auto child = doc_write.append_child("VerData");
		child.append_attribute("Version").set_value(x.first.c_str());
		child.append_attribute("LevelName").set_value(x.second.c_str());
		child.append_attribute("Desc").set_value("FarCry");
		child.append_attribute("Internal").set_value(1);
		doc_write.save_file((work_dir + "VersionDB.clcdb").c_str());
	}
	int x = 0;
}

void EngineVersionUtils::CreateVersionInfoFromString(std::string_view str)
{
	std::string sor = str.data();
	size_t prev_point = 0;
	int point_cnt = 0;
	std::array<std::string, 4> arr;
	arr[0] = sor.substr(0, FindNthOccurence(sor, '.', 1));
	arr[1] = sor.substr(FindNthOccurence(sor, '.', 1), FindNthOccurence(sor, '.', 2));
	arr[2] = sor.substr(FindNthOccurence(sor, '.', 2), FindNthOccurence(sor, '.', 3));
	arr[2] = sor.substr(FindNthOccurence(sor, '.', 2));
	int x = 0;
}

EngineGeneration EngineVersionUtils::GetEngineGenFromMission(pugi::xml_document mission_xml)
{
	if (mission_xml.attribute("MusicScript").empty() && mission_xml.attribute("Script").empty());
	{
		return CE1;
	}
}
