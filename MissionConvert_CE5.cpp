#include "MissionConvert_CE5.h"

bool MissionConvert_CE5::Convert()
{
	bool status = MissionConvert_Base::Convert();
	if (!SaveToDisk())
	{
		g_Log.Log("Can't save .lyr files to disk!", this);
		return false;
	}
	VersionSpecificInstructions();
	return status;
}

inline void MissionConvert_CE5::VersionSpecificInstructions()
{
}

MissionConvert_CE5::MissionConvert_CE5()
{
}

