#pragma once

class Agent;

class IBehaviour
{
public:
	IBehaviour() = default;
	virtual ~IBehaviour() = default;

public:
	virtual void Tick(float dt, Agent* agent) = 0;

};