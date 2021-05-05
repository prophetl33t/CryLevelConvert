#include "TerrainLayerInfoConvert.h"

std::regex rx_matname("Name=\"(.*?)\"");

inline bool TerrainLayerInfoConvert::Convert()
{
	terlay_fstream_in.open(xml_path);
	terlay_fstream_out.open(cry_fname::out::TERLAYDATA, std::ofstream::out | std::ofstream::binary);
	if (terlay_fstream_in.is_open())
	{
		size_t before = terlay_fstream_out.tellp();
		int layer_cntr = 0;
		std::string buffer;
		bool IsSurfDat = false;
		std::vector <std::string> layers_mats;
		while (std::getline(terlay_fstream_in, buffer))
		{
			if (buffer == " <SurfaceTypes>")
			{
				IsSurfDat = true;
				break;
			}
		}
		if (IsSurfDat)
		{
			terlay_fstream_out << "   <LayerSettings>\n";
			terlay_fstream_out << " <SurfaceTypes>\n";
			while (std::getline(terlay_fstream_in, buffer))
			{
				if (buffer != " </SurfaceTypes>")
				{
					std::regex_search(buffer, matname_match, rx_matname);
					layers_mats.push_back(matname_match.str().substr(6, matname_match.str().size() - 1));
					terlay_fstream_out << buffer << "\n";
				}
				else
				{
					break;
				}
			}
			terlay_fstream_out << " </SurfaceTypes>\n";
			terlay_fstream_out << " <Layers>\n";
			for (auto& x : layers_mats)
			{
				layer_cntr++;
				terlay_fstream_out << "  <Layer Name=\"" << "layer_" << layer_cntr << R"(" Texture="" TextureWidth="4" TextureHeight="4" Material="" AltStart="0" AltEnd="4096" MinSlopeAngle="0" MaxSlopeAngle="90" InUse="1" AutoGenMask="1" LayerId=")" << layer_cntr << R"(" SurfaceType=")" << x << R"( FilterColor="0.61960787,0.56470591,0.40392157" LayerBrightness="0.39215687" UseRemeshing="0" LayerTiling="1" SpecularAmount="0" SortOrder="0"/>)" << "\n";
			}
			terlay_fstream_out << " </Layers>\n";
			terlay_fstream_out << "</LayerSettings>\n";

			//binary end
			for (int a = 0; a < 4; a++)
			{
				terlay_fstream_out.write(reinterpret_cast<const char*>(&zero), sizeof(zero));
			}

			size = terlay_fstream_out.tellp().operator-(before).operator-(std::streamoff(7));
			terlay_fstream_out.seekp(std::ios_base::beg);
			terlay_fstream_out.write(reinterpret_cast<const char*>(&holder), sizeof(holder));
			terlay_fstream_out.write(reinterpret_cast<const char*>(&size), sizeof(size));

			std::cout << "[TerTexLayInfo] Exported terrain layers info to .lay!\n";
			return true;
		}
		else
		{
			std::cout << "[TerTexLayInfo] Leveldata.xml doesn't have any information about terrain texture layers!\n";
			return false;
		}
	}
	
}

TerrainLayerInfoConvert::TerrainLayerInfoConvert()
{
}
