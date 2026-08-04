#pragma once

#include <string>
#include <nlohmann/json.hpp>

#include "Utility/Collections/TMap.h"

class Config;

using std::string;

struct AgentType
{
	float radius = 1.f;
	float halfHeight = 1.f;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(AgentType, radius, halfHeight)
};

struct NavigationAreaType
{
	bool walkable = true;
	float costModifier = 1.f;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(NavigationAreaType, walkable, costModifier)
};

class Navigation
{
public:
	static Navigation& GetInstance();

private:
	Config* m_config;

	TMap<string, AgentType> m_agentTypes;
	TMap<string, NavigationAreaType> m_areaTypes;

private:
	Navigation();
	~Navigation();

public:
	AgentType* FindAgentType(const string& id);
	NavigationAreaType* FindAreaType(const string& id);

};