#include "EntArchetypeObtainer.h"

EntArchetypeObtainer::EntArchetypeObtainer()
{

}

int EntArchetypeObtainer::FillEntArcList()
{
	if (!fs::exists(cry_fname::out::ENTARCCACHE)) //Not write cache if one already exists.
	{
		if (fs::exists(cry_fname::in::ENTARCFOLDER)) //How would you collect info about ent. archs without libs??
		{
			m_ent_arc_cache_stream.open(cry_fname::out::ENTARCCACHE, std::fstream::out);

			for (auto& x : fs::recursive_directory_iterator(cry_fname::in::ENTARCFOLDER))
			{
				if (doc.load_file(x.path().c_str()))
				{
					std::string lib_name = doc.child("EntityPrototypeLibrary").attribute("Name").value();
					for (auto& n : doc.select_nodes("EntityPrototypeLibrary/EntityPrototype"))
					{
						if (strcmp(n.node().name(), "EntityPrototype") == 0)
						{
							m_ent_arc_cache_stream << lib_name << "." << n.node().attribute("Name").value() << "\n";
							m_ent_arc_cache_stream << n.node().attribute("Id").value() << "\n";
							m_ent_arc_map.emplace(lib_name + "." + n.node().attribute("Name").value(), n.node().attribute("Id").value());
						}
					}
				}
				else
				{
					std::cout << "[EntArcObtain] Warning! Unable to parse " << x.path() << "\n";
				}
			}
			std::cout << "[EntArcObtain] Got info about " << m_ent_arc_map.size() << " entity archetypes from EntityArchetype folder\n";
		}
		else
		{
			std::cout << "[EntArcObtain] Warning! Unable to find EntityArchetype folder. This may cause missing entites!\n";
		}
	}
	else
	{
		uint16_t cntr = 0;
		std::string buf,buf2;
		m_ent_arc_cache_stream.clear();
		m_ent_arc_cache_stream.close();
		m_ent_arc_cache_stream.open(cry_fname::out::ENTARCCACHE, std::fstream::in);
		while (!m_ent_arc_cache_stream.eof())
		{
			if (cntr == 0)
			{
				std::getline(m_ent_arc_cache_stream, buf);
				cntr++;
			}
			else if (cntr == 1)
			{
				std::getline(m_ent_arc_cache_stream, buf2);
				m_ent_arc_map.emplace(buf,buf2);
				cntr = 0;
			}
		}
		std::cout << "[EntArcObtain] Got info about " << m_ent_arc_map.size() << " entity archetypes from cache\n";
	}

	m_have_ent_data = true;
	return OK;
}

std::unordered_map<std::string, std::string>& EntArchetypeObtainer::GetEntArcMap()
{
	return m_ent_arc_map;
}

bool EntArchetypeObtainer::IsHavingData()
{
	return m_have_ent_data;
}

//m_ent_arc_cache_stream << std::string_view(n.node().attribute("Id").value()).substr(1, 36) << "\n"; //.substr(1,36) removes first and last char of GUID (braces). Size of GUID is constant (38)!
//m_ent_arc_map.emplace(n.node().attribute("Name").value(), std::string_view(n.node().attribute("Id").value()).substr(1, 36));