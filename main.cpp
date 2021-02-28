//#define MAIN_DISABLE
#define USE_PAK_INTERACTION

#include "MissionConvert.h"
#include "MovieDataConvert.h"
#include "VegetationDumpConvert.h"
#include "EntArchetypeObtainer.h"
#include "TerrainLayerInfoConvert.h"
#include <chrono>
#include <locale>
#include <codecvt>
#ifdef USE_PAK_INTERACTION
#include "Zippy.hpp"
#endif

inline void BatchConvert(const char* path, MissionConvert& c_m, MovieDataConvert& m_m, TerrainLayerInfoConvert& t_m)
{
	std::string work_dir = std::filesystem::current_path().string() + "\\";
	Zippy::ZipArchive arch(path);
	arch.ExtractEntry(cry_fname::in::MISSIONXML, work_dir);

	c_m.ConvertFromDisk(work_dir + cry_fname::in::MISSIONXML);
	c_m.ExtractTOD();

	arch.ExtractEntry(cry_fname::in::MDATA, work_dir);

	m_m.ConvertFromDisk(work_dir + cry_fname::in::MDATA);

	arch.ExtractEntry(cry_fname::in::LVLDATA, work_dir);

	t_m.ConvertFromDisk(work_dir + cry_fname::in::LVLDATA);

	std::cout << "[BatchConvert] Complete!\n";
}


int main(int argc, char* argv[])
{
	auto begin = std::chrono::steady_clock::now();
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
				for (auto& x : fs::recursive_directory_iterator(argv[a]))
				{
					if (x.path().extension() == ".pak" || x.path().extension() == ".zip")
					{
						BatchConvert(x.path().string().c_str(), mis_convert, mdata_convert, terlay_convert);
					}	
				}
				break;
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
				BatchConvert(argv[1], mis_convert, mdata_convert, terlay_convert);
				break;
			#endif
			case Util::DataTypes::AIDUMP:
				std::cout << "AIDump convert is now being handled by CryDumper!\n";
				Util::DelayedExit();
				break;
			case Util::DataTypes::TERRAINDUMP:
				std::cout << "Terrain convert is now being handled by CryDumper!\n";
				Util::DelayedExit();
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