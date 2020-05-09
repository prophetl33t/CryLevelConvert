#include "MissionConvert_CE3.h"

bool MissionConvert_CE3::Convert()
{
	bool status = MissionConvert_Base::Convert();
	if (SaveToDisk())
	{
		g_Log.Log("Can't save .lyr files to disk!",this, INFO);
		return false;
	}
	return status;
}

MissionConvert_CE3::MissionConvert_CE3()
{
}

