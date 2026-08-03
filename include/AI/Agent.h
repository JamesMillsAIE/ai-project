#pragma once

#include <string>
#include <nlohmann/json.hpp>

#include "Gameplay/Actor.h"

using std::string;

struct AgentType
{
	string id = "default";
	float radius = 1.f;
	float halfHeight = 1.f;
};

class IBehaviour;

class Agent final : public Actor
{
	friend IWorld;

private:
	AgentType m_agentType;
	IBehaviour* m_behaviour;

protected:
	explicit Agent(IWorld* world);
	~Agent() override;

public:
	void Tick(float dt) override;
	void Render() override;

	void SetBehaviour(IBehaviour* behaviour);
	void SetAgentType(const AgentType& agentType);

};