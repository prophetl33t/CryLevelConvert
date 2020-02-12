#include "VegetationDumpConvert.h"


std::fstream file_r_dump_veg_read;
std::fstream file_rw_veg_dump;

struct VegInstance
{
	std::string model;
	std::string material;
	std::string pos;


	bool operator == (const VegInstance& obj)
	{
		return (model == obj.model) && (material == obj.material);
	}
};


std::vector <VegInstance> vec_veg_ents;
std::vector <VegInstance> vec_veg_groups;

void VegetationDumpConvert(const std::string& path_in, const std::string& path_out)
{
	std::string buf;

	if (fs::exists(path_in))
	{
		file_r_dump_veg_read.open(path_in);
		file_rw_veg_dump.open(path_out, std::ofstream::out);
		std::getline(file_r_dump_veg_read, buf); //skip id
		VegInstance vg;
		while (!file_r_dump_veg_read.eof())
		{
			std::getline(file_r_dump_veg_read, buf);
			vg.model = buf;
			std::getline(file_r_dump_veg_read, buf);
			vg.material = buf;
			std::getline(file_r_dump_veg_read, buf);
			vg.pos = buf;
			vec_veg_ents.push_back(vg);
		}

		for (unsigned int a = 0; a < vec_veg_ents.size(); a++)
		{
			if (std::find(vec_veg_groups.begin(), vec_veg_groups.end(), vec_veg_ents[a]) == vec_veg_groups.end())
			{
				vec_veg_groups.push_back(vec_veg_ents[a]);
			}
		}

		file_rw_veg_dump << "<Vegetation>\n";

		for (unsigned int a = 0; a < vec_veg_groups.size(); a++)
		{
			std::string group_name = vec_veg_groups[a].model.substr(0, vec_veg_groups[a].model.size() - 4);
			file_rw_veg_dump << R"( <VegetationObject Size="1" SizeVar="0" RandomRotation="0" AlignToTerrain="0" UseTerrainColor="0" AllowIndoor="0" Bending="1" Hideable="0" PlayerHideable="0" GrowOnVoxels="0" GrowOnBrushes="0" Pickable="0" AIRadius="-1" Brightness="1" Density="1" ElevationMin="-1e+006" ElevationMax="4096" SlopeMin="0" SlopeMax="90" CastShadow="0" RecvShadow="0" RecvDecals="1" AlphaBlend="0" SpriteDistRatio="100" LodDistRatio="100" MaxViewDistRatio="100" Material=")" + vec_veg_groups[a].material + R"(" UseSprites="1" MinSpec="0" Frozen="0" Layer_Wet="0" Id=")" + std::to_string(a) + "\" FileName=\"" + vec_veg_groups[a].model + "\" GUID=\"{" + Util::GenerateRandomGUID()+ R"(" Hidden="0" Index="0" Category=")" + Util::PathWithoutFilename(group_name) + R"(">)" + "\n";
			file_rw_veg_dump << "  <Instances>\n";
			for (unsigned int k = 0; k < vec_veg_ents.size(); k++)
			{
				if (vec_veg_ents[k] == vec_veg_groups[a])
				{
					file_rw_veg_dump << "   <Instance Pos=\"" + vec_veg_ents[k].pos + R"("/>)" + "\n";
				}
			}
			file_rw_veg_dump << "  </Instances>\n";
			file_rw_veg_dump << " </VegetationObject>\n";
		}

		file_rw_veg_dump << "</Vegetation>\n";


		file_r_dump_veg_read.close();
		file_rw_veg_dump.close();

		std::cout << "[VegetationConvert] Converted vegetation dump to .veg file!\n";
	}
}

