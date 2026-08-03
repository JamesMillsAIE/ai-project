#pragma once

#include <string>
#include <nlohmann/json.hpp>

#include "Utility/Collections/TList.h"

class Config;

using std::string;

struct AgentType
{
	string id = "default";
	float radius = 1.f;
	float halfHeight = 1.f;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(AgentType, id, radius, halfHeight)
};

struct NavigationAreaType
{
	string id = "default";
	bool walkable = true;
	float costModifier = 1.f;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(NavigationAreaType, id, walkable, costModifier)
};

class Navigation
{
private:
	Config* m_config;

	TList<AgentType> m_agentTypes;
	TList<NavigationAreaType> m_areaTypes;

public:
	Navigation();
	~Navigation();

};