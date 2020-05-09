#pragma once
#include "MissionConvert_CE3.h"
/// <summary>
///<para>CE5 XML Converter</para><para>Input : mission_mission0.xml file from level.pak</para> <para>Output : .lyr files containing scripts/dynamic entities info</para>
/// </summary>
class MissionConvert_CE5 final : MissionConvert_CE3
{
private:
	inline bool Convert() override;
	inline void VersionSpecificInstructions() override;
public:
	MissionConvert_CE5();
};

