#include "Util.h"
#include <filesystem>
#include <iostream>

const std::string CHARS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

std::string Util::GenerateRandomGUID(bool add_brackets)
{
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> rand_gen_guid(1, 9999999);
	std::string guid = std::string(36, ' ');
	int rnd = 0;
	int r = 0;

	guid[8] = '-';
	guid[13] = '-';
	guid[18] = '-';
	guid[23] = '-';
	guid[14] = '4';

	for (int i = 0; i < 36; i++) {

		if (i != 8 && i != 13 && i != 18 && i != 14 && i != 23) {
			if (rnd <= 0x02) {
				rnd = 0x2000000 + rand_gen_guid(rng) * rand_gen_guid(rng) | 0;
			}
			rnd >>= 4;
			guid[i] = CHARS[(i == 19) ? ((rnd & 0xf) & 0x3) | 0x8 : rnd & 0xf];
		}
	}
	if (add_brackets)
	{
		guid.insert(0, "{");
		guid += '}';
	}
	return guid;
}

std::string Util::GenerateGUIDFrom64(const std::string& guid_64, bool add_brackets)
{
	return std::string((add_brackets ? "{" : "") + guid_64.substr(8) + "-" + guid_64.substr(4, 4) + "-" + guid_64.substr(0, 4) + "-" + guid_64.substr(0, 4) + "-" + guid_64.substr(8) + guid_64.substr(0, 4) + (add_brackets ? "}" : ""));
}

pugi::xml_document Util::CreateLayerFile(std::string_view name, std::string_view guid)
{
	pugi::xml_document layer;
	pugi::xml_node lr_nd = layer.root().append_child("ObjectLayer").append_child("Layer");
	lr_nd.append_attribute("Name").set_value(name.data());
	lr_nd.append_attribute("GUID").set_value(guid.data());
	lr_nd.append_attribute("FullName").set_value(name.data());
	lr_nd.append_attribute("External").set_value(0);
	lr_nd.append_attribute("Exportable").set_value(1);
	lr_nd.append_attribute("ExportLayerPak").set_value(1);
	lr_nd.append_attribute("DefaultLoaded").set_value(0);
	lr_nd.append_attribute("HavePhysics").set_value(1);
	lr_nd.append_attribute("Expanded").set_value(0);
	lr_nd.append_attribute("IsDefaultColor").set_value(1);
	lr_nd.append_child("LayerObjects");
	return layer;
}

Util::DATA_TYPES Util::DetectDataType(const std::string& path)
{
	std::ifstream file_r_check_type;
	std::string buf_check;
	file_r_check_type.open(path);
	std::getline(file_r_check_type, buf_check);
	if (std::filesystem::is_directory(path))
	{
		return Util::DATA_TYPES::DIR;
	}
	else if (buf_check == "<MovieData>")
	{
		return Util::DATA_TYPES::MDATA;
	}
	else if (buf_check.find("Mission Name") != std::string::npos)
	{
		return Util::DATA_TYPES::MISSION;
	}
	else if (std::filesystem::path(path).extension() == ".pak" || std::filesystem::path(path).extension() == ".zip")
	{
		return Util::DATA_TYPES::PAK;
	}
	else if (buf_check.find("AIPointsDump") != std::string::npos)
	{
		return Util::DATA_TYPES::AIDUMP;
	}
	else if (buf_check.find("Terrain") != std::string::npos)
	{
		return Util::DATA_TYPES::TERRAINDUMP;
	}
	else if (buf_check.find("VegDump") != std::string::npos)
	{
		return Util::DATA_TYPES::VEGDUMP;
	}
	else if (buf_check == "World")
	{
		return  Util::DATA_TYPES::GEOMDUMP;
	}
	else if (buf_check.find("LevelData") != std::string::npos)
	{
		return Util::DATA_TYPES::TERLAYDUMP;
	}
	else
	{
		return Util::DATA_TYPES::UNKNOWN;
	}
}

std::string Util::PathWithoutFilename(std::string& path)
{
	auto a = path.rfind('\\');
	if (path.size() > 3)
	{
		if (a != std::string::npos)
		{
			path.erase(a, std::string::npos);
			return path + '\\';
		}
		else
		{
			return "";
		}
	}
	else
	{
		return "";
	}
}

void Util::DelayedExit()
{
	if (auto_exit != 1)
	{
		std::cout << "Press ENTER to exit...\n";
		std::cin.get();
		exit(0);
	}
}



