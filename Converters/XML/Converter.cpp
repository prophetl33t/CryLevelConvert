#include "Converter.h"

bool XMLConverter::ConvertFromDisk(const std::string& path_in)
{
	if (!path_in.empty())
	{
		xml_path = path_in;
		doc.load_file(path_in.c_str());
		if (doc.load_file(path_in.c_str()).status != pugi::status_ok)
		{
			return false;
			std::cout << "[Converter] Can't reload xml\n";
		}
		if (Convert())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool XMLConverter::ConvertFromDisk(const std::vector<std::string>& paths_in)
{
	bool success = true;
	for (auto& flist : paths_in)
	{
		if (!flist.empty())
		{
			xml_path = flist;
			doc.load_file(flist.c_str());
			if (doc.load_file(flist.c_str()).status != pugi::status_ok)
			{
				return false;
				std::cout << "[MissionConvert] Can't reload xml\n";
			}
		}
		if (!Convert())
		{
			success = false;
		}
	}
	return success;
}

bool XMLConverter::ConvertFromByteArray(std::vector<unsigned char>& data)
{
	doc.load_buffer_inplace((void*)data.data(), data.size());
	if (Convert())
	{
		return true;
	}
	else
	{
		return false;
	}
}

XMLConverter::XMLConverter(const std::string& path_in)
{
	xml_path = path_in;
	res = doc.load_file(xml_path.c_str());
	if (res.status != pugi::status_ok)
	{
		std::cout << "[Coverter] Can't properly parse XML!\n";
	}
}

XMLConverter::XMLConverter()
{

}
