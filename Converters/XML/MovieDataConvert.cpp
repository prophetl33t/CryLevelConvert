#include "MovieDataConvert.h"

inline bool MovieDataConvert::Convert()
{
	pugi::xml_document dc = Util::CreateLayerFile("CLC_MovieData");
	for (pugi::xml_node mission_node = doc.select_node("/MovieData/Mission/SequenceData/Sequence").node(); mission_node; mission_node = mission_node.next_sibling())
	{
		auto node = dc.select_node("ObjectLayer/Layer/LayerObjects").node().append_child("Object");
		node.append_attribute("Type").set_value("SequenceObject");
		node.append_attribute("Layer").set_value("CLC_MDATA");
		node.append_attribute("LayerGUID").set_value(mdata_guid.c_str());
		node.append_attribute("Id").set_value(Util::GenerateRandomGUID().c_str());
		node.append_attribute("Name").set_value(mission_node.attribute("Name").as_string());
		dc.select_node("ObjectLayer/Layer/LayerObjects").node().append_copy(mission_node);
	}
	dc.save_file("CLC_MovieData.lyr", " ");
	return true;
}

MovieDataConvert::MovieDataConvert()
{
}
