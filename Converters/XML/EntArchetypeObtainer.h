#pragma once
#include "CLCHeaders.h"
#include <unordered_map>
#include <fstream>

enum ENT_ARC_CACHE_RES {OK, CACHE_EXISTS, WRITE_ERROR, READ_ERROR};

/// <summary>
///Entity archetype resolver is required for retriving all entity archetype id's from provided XML libraries (Libs folder)
/// </summary>
class EntArchetypeObtainer
{
private:
	std::unordered_map<std::string, std::string> m_ent_arc_map;
	pugi::xml_document doc;
	std::fstream m_ent_arc_cache_stream;
	bool m_have_ent_data = false;
public:
	EntArchetypeObtainer();
	int FillEntArcList();
	std::unordered_map<std::string, std::string>& GetEntArcMap();
	bool IsHavingData();
};

