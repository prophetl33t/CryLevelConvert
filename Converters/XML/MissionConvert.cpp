#include "MissionConvert.h"

EntArchetypeObtainer MissionConvert::entarc = EntArchetypeObtainer();//Init archetype obtainer

std::map <std::string, std::string> map_ent = //Some entites have different classes in editor and in game!
{
{ "EnvironmentLight","EnvironmentProbe" },
{ "AreaShape","Shape" },
{ "AITerritory", "Shape" },
{ "LightShape", "Shape" },
{ "RopeEntity", "Rope" }
};


bool MissionConvert::Convert()
{
	for (auto& fg_node : doc.select_node("/Mission/Objects/Entity/FlowGraph/Nodes").node().children()) //collect info about entity guids
	{
		if (strcmp(fg_node.attribute("EntityGUID").value(), "") != 0 || strcmp(fg_node.attribute("EntityGUID_64").value(), "") != 0)
		{
			m_map_guid_64.emplace(fg_node.attribute("EntityGUID").value(), fg_node.attribute("EntityGUID_64").value());
		}
	}
	for (pugi::xml_node mission_node = doc.select_node("/Mission/Objects/Entity").node(); mission_node; mission_node = mission_node.next_sibling()) //for every entity
	{
		if (!mission_node.attribute("Type").empty())
		{
			for (auto& x : map_ent)
			{
				if (strcmp(mission_node.attribute("EntityClass").value(), x.first.c_str()) == 0)
				{
					mission_node.attribute("Type").set_value(x.second.c_str());
				}
			}
		}
		if (!mission_node.attribute("Layer").empty()) //collect info about layers of entities
		{
			m_layer_names.push_back(mission_node.attribute("Layer").value());
		}
		if (!mission_node.attribute("EntityGuid").empty()) //in .lyr files EntityGuid is Id
		{
			pugi::xml_attribute attr = mission_node.attribute("EntityGuid");
			attr.set_name("Id");
		}
		if (strcmp(mission_node.name(), "Entity") == 0)
		{
			m_map_id_parent.emplace(mission_node.attribute("Id").value(), mission_node.attribute("EntityId").value());
			mission_node.set_name("Object");
			mission_node.append_attribute("Type").set_value("Entity");
			if (mission_node.child("Area")) //Areas have additional data in .lyr
			{
				mission_node.append_copy(mission_node.child("Area").child("Points"));
				mission_node.append_copy(mission_node.child("Area").child("Entities"));
				mission_node.append_attribute("AreaId").set_value(mission_node.child("Area").attribute("Area Id").value());
				mission_node.append_attribute("GroupId").set_value(mission_node.child("Area").attribute("Group").value());
				mission_node.append_attribute("Priority").set_value(mission_node.child("Area").attribute("Priority").value());
				mission_node.append_attribute("Height").set_value(mission_node.child("Area").attribute("Height").value());
				mission_node.remove_child("Area");

			}
		}
		if (!mission_node.attribute("Archetype").empty()) //replace archetype type (pun intended) with one from database
		{
			for (auto& arc_ent : entarc.GetEntArcMap())
			{
				if (strcmp(arc_ent.first.c_str(), mission_node.attribute("Archetype").value()) == 0)
				{
					mission_node.attribute("Archetype").set_value(arc_ent.second.c_str());
					break;
				}
			}
		}
		for (auto& val : map_ent) //some entities have different type name in game and in editor
		{
			if (mission_node.attribute("EntityClass").as_string() == val.first)
			{
				mission_node.attribute("EntityClass").set_value(val.second.c_str());
				break;
			}
		}
	}
	//Next two loops are restoring links between entities based on data we collected in previous big loop
	for (auto& link : doc.select_nodes("/Mission/Objects/Object/EntityLinks/Link"))
	{
		for (auto& x : m_map_id_parent)
		{
			if (strcmp(link.node().attribute("TargetId").value(), x.second.c_str()) == 0)
			{
				link.node().attribute("TargetId").set_value(Util::GenerateGUIDFrom64(x.first, true).c_str());
				break;
			}
		}
	}
	for (auto& ent : doc.select_nodes("/Mission/Objects/Object/Entities/Entity"))
	{
		for (auto& x : m_map_id_parent)
		{
			if (strcmp(ent.node().attribute("Id").value(), x.second.c_str()) == 0)
			{
				ent.node().attribute("Id").set_value(Util::GenerateGUIDFrom64(x.first, true).c_str());
				break;
			}
		}
	}
	bool valid_val = false;
	for (pugi::xml_node mission_node = doc.select_node("/Mission/Objects/Object").node(); mission_node; mission_node = mission_node.next_sibling())
	{
		for (auto& id_64 : m_map_guid_64)
		{
			if (strcmp(mission_node.attribute("Id").value(), id_64.second.c_str()) == 0)
			{
				mission_node.attribute("Id").set_value(id_64.first.c_str());
				valid_val = true;
				break;
			}
		}
		if (!valid_val && !mission_node.attribute("Id").empty())
		{
			mission_node.attribute("Id").set_value(Util::GenerateGUIDFrom64(mission_node.attribute("Id").value(), true).c_str()); //Editor requires GUID in it's special format. If it is not converted - editor will throw errors about duplicate objects.
		}
		valid_val = false;
	}

	//delete layer duplicates
	std::sort(m_layer_names.begin(), m_layer_names.end());
	m_layer_names.erase(std::unique(m_layer_names.begin(), m_layer_names.end()), m_layer_names.end());
	for (auto& x : m_layer_names)
	{
		pugi::xml_document dc = Util::CreateLayerFile(x);
		for (auto& a : doc.select_nodes("/Mission/Objects/Object"))
		{
			if (strcmp(a.node().attribute("Layer").value(), x.c_str()) == 0)
			{
				dc.select_node("ObjectLayer/Layer/LayerObjects").node().append_copy(a.node());
			}
		}
		dc.save_file(std::string(Util::PathWithoutFilename(xml_path) + x + ".lyr").c_str(), " "); //We need to save .lyr files in folder of level in case of converting multiple levels in a row.
	}
	return true;
}

void MissionConvert::ExtractTOD()
{
	tod_stream_out.close();
	tod_stream_out.clear();
	tod_stream_out.open(cry_fname::out::TOD, std::ofstream::out);

	if (!tod_stream_out.is_open())
	{
		std::cout << "[TODExtract] Can't write TOD file to disk!\n";
	}
	else
	{
		doc.select_node("/Mission/TimeOfDay").node().print(tod_stream_out);
	}
	tod_stream_out.close();
}

MissionConvert::MissionConvert()
{
}
