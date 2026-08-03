#include "AI/Pathfinding/Navigation.h"

#include "Utility/Config.h"

Navigation::Navigation()
	: m_config{ new Config{ "navigation" } }
{
	vector<AgentType> agentTypes = m_config->Get<vector<AgentType>>("agentTypes");
}

Navigation::~Navigation() {}