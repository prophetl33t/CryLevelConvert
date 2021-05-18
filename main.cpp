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

inline void PakConvert(const char* path)
{
#ifdef USE_PAK_INTERACTION
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

	std::cout << "[PakConvert] " << path << " converted\n";
#else
	std::cout << path << " was not processed because CLC was compiled without USE_PAK_INTERACTION\n";
#endif
}

inline void ConvertData(const char* path)
{
	MissionConvert mis_convert;
	MovieDataConvert mdata_convert;
	TerrainLayerInfoConvert terlay_convert;
	if (!fs::exists(path))
		std::cout << path << " doesn't exist.\n"; return;

	switch (Util::DetectDataType(path))
	{
	case Util::DataTypes::DIR:
		ConvertData(path);
		break;
	case Util::DataTypes::MDATA:
		if (mdata_convert.ConvertFromDisk(path))
		{
			std::cout << "[MovieData] Converted moviedata to .lyr!\n";
		}
		break;
	case Util::DataTypes::MISSION:
		if (mis_convert.ConvertFromDisk(path))
		{
			std::cout << "[MissionConvert] Converted mission to .lyr!\n";
			mis_convert.ExtractTOD();
		}
		break;
	case Util::DataTypes::PAK:
		PakConvert(path);
		break;
	case Util::DataTypes::AIDUMP:
		std::cout << "Use CryDumper for AIDump.\n";
		break;
	case Util::DataTypes::TERRAINDUMP:
		std::cout << "Use CryDumper for TerrainDump.\n";
		break;
	case Util::DataTypes::VEGDUMP:
		VegetationDumpConvert(path, std::string(path) + "clc_veg.veg");
		break;
	case Util::DataTypes::GEOMDUMP:
		std::cout << "Use CryDumper for GeomDump.\n";
		break;
	case Util::DataTypes::TERLAYDUMP:
		terlay_convert.ConvertFromDisk(path);
		break;
	case Util::DataTypes::UNKNOWN:
		std::cout << "Unknown file format.\n";
		break;
	}
}

int main(int argc, char* argv[])
{
	auto begin = std::chrono::steady_clock::now();
	std::ios_base::sync_with_stdio(false);

	std::cout << "CryLevelConvert V2 by Prophet\n";
	MissionConvert::GetEntArcObtainter().FillEntArcList();

	if (argc > 1)
	{
		for (int a = 1; a < argc; a++)
		{
			std::cout << argv[a] << "\n";
			std::async(std::launch::async, ConvertData, argv[a]);
		}
	}
	else
	{
		ConvertData(cry_fname::in::MISSIONXML.data());
		ConvertData(cry_fname::in::MDATA.data());
		ConvertData(cry_fname::in::LVLDATA.data());
		VegetationDumpConvert("veg_dump.txt", "clc_veg.veg");
	}

	auto end = std::chrono::steady_clock::now();
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	std::cout << "Elapsed time: " << elapsed_ms.count() << " ms\n";
	Util::DelayedExit();
}