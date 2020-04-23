#pragma once
#include "MissionConvert_Base.h"

/// <summary>
///<para>CE3 XML Converter</para><para>Input : mission_mission0.xml file from level.pak</para> <para>Output : .lyr files containing scripts/dynamic entities info</para>
/// </summary>
class MissionConvert_CE3 final : public MissionConvert_Base
{
private:
	inline bool Convert() override;
public:
	void ExtractTOD();
	MissionConvert_CE3();
};

