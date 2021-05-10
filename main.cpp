#include "CLCHeaders.h"
#include "Converters/XML/MissionConvert.h"
#include "Converters/XML/MovieDataConvert.h"
#include "Converters/CustomFormat/VegetationDumpConvert.h"
#include "XML/EntArchetypeObtainer.h"
#include "Converters/XML/TerrainLayerInfoConvert.h"
#include <chrono>
#include <locale>
#include <codecvt>
#include <future>
#ifdef USE_PAK_INTERACTION
#include "zipper/unzipper.h"
#endif

inline void BatchConvert(const char* path)
{
	MissionConvert c_m;
	MovieDataConvert m_m;
	TerrainLayerInfoConvert t_m;

	zipper::Unzipper arch(path);
	std::vector<unsigned char> data;
	bool success = arch.extractEntryToMemory(cry_fname::in::MISSIONXML, data);
	if (success)
	{
		c_m.ConvertFromByteArray(data);
		c_m.ExtractTOD();
	}

	success = arch.extractEntryToMemory(cry_fname::in::MDATA, data);
	if (success) m_m.ConvertFromByteArray(data);

	success = arch.extractEntryToMemory(cry_fname::in::LVLDATA, data);
	if (success) t_m.ConvertFromByteArray(data);

	std::cout << "[BatchConvert] " << path << " extracted\n";
}


int main(int argc, char* argv[])
{
	auto begin = std::chrono::steady_clock::now();
	std::ios_base::sync_with_stdio(false);

	MissionConvert::GetEntArcObtainter().FillEntArcList();

	MissionConvert mis_convert;
	MovieDataConvert mdata_convert;
	TerrainLayerInfoConvert terlay_convert;

	if (argc > 1)
	{
		for (int a = 1; a < argc; a++)
		{
			std::cout << argv[a] << "\n";
			switch (Util::DetectDataType(argv[a]))
			{
			#ifdef USE_PAK_INTERACTION
			case Util::DataTypes::DIR:
			{
				for (auto& x : fs::recursive_directory_iterator(argv[a]))
				{
					if (x.path().extension() == ".pak" || x.path().extension() == ".zip")
					{
						std::async(std::launch::async,BatchConvert,x.path().string().c_str());
					}
				}
				break;
			}
			#endif
			case Util::DataTypes::MDATA:
				mdata_convert.ConvertFromDisk(argv[a]);
				break;
			case Util::DataTypes::MISSION:
				mis_convert.ConvertFromDisk(argv[a]);
				mis_convert.ExtractTOD();
				break;
			case Util::DataTypes::PAK:
			#ifdef USE_PAK_INTERACTION
				BatchConvert(argv[1]);
				break;
			#endif
			case Util::DataTypes::AIDUMP:
				std::cout << "AIDump convert is now being handled by CryDumper!\n";
				break;
			case Util::DataTypes::TERRAINDUMP:
				std::cout << "Terrain convert is now being handled by CryDumper!\n";
				break;
			case Util::DataTypes::VEGDUMP:
				VegetationDumpConvert(argv[a], std::string(argv[a]) + "clc_veg.veg");
				break;
			case Util::DataTypes::GEOMDUMP:
				std::cout << "Geom convert is now being handled by CryDumper!\n";
				break;
			case Util::DataTypes::TERLAYDUMP:
				terlay_convert.ConvertFromDisk(argv[a]);
				break;
			case Util::DataTypes::UNKNOWN:
				std::cout << "Unknown file type!\n";
				break;
			}
		}
	}
	else
	{
		if (mis_convert.ConvertFromDisk(cry_fname::in::MISSIONXML))
		{
			std::cout << "[MissionConvert] Converted mission to .lyr!\n";
			mis_convert.ExtractTOD();
		}
		if (mdata_convert.ConvertFromDisk(cry_fname::in::MDATA))
		{
			std::cout << "[MovieData] Converted moviedata to .lyr!\n";
		}
		VegetationDumpConvert("veg_dump.txt", "clc_veg.veg");
		terlay_convert.ConvertFromDisk(cry_fname::in::LVLDATA);
	}
	auto end = std::chrono::steady_clock::now();
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	std::cout << "Elapsed time: " << elapsed_ms.count() << " ms\n";
	std::cout << "CryLevelConvert V2 by Prophet\n";
	Util::DelayedExit();
}