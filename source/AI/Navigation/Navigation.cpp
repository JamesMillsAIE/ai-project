#include "AI/Navigation/Navigation.h"

#include "Utility/Config.h"

Navigation& Navigation::GetInstance()
{
	static Navigation instance;

	return instance;
}

Navigation::Navigation()
	: m_config{ new Config{ "navigation" } }
{
	for (Json agentType : m_config->Get<Json>("agentTypes"))
	{
		m_agentTypes.Add(agentType["id"], agentType.get<AgentType>());
	}

	for (Json areaType : m_config->Get<Json>("areaTypes"))
	{
		m_areaTypes.Add(areaType["id"], areaType.get<NavigationAreaType>());
	}
}

Navigation::~Navigation()
{
	delete m_config;
}

AgentType* Navigation::FindAgentType(const string& id)
{
	if (m_agentTypes.ContainsKey(id))
	{
		return &m_agentTypes[id];
	}

	return nullptr;
}

NavigationAreaType* Navigation::FindAreaType(const string& id)
{
	if (m_areaTypes.ContainsKey(id))
	{
		return &m_areaTypes[id];
	}

	return nullptr;
}
