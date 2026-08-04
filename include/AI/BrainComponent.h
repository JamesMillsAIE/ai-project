#pragma once

#include "Gameplay/IComponent.h"

class Agent;
class IBehaviour;

class BrainComponent : public IComponent
{
private:
	IBehaviour* m_behaviour;

public:
	BrainComponent(IBehaviour* defaultBehaviour = nullptr);

public:
	virtual void Tick(float dt) override;
	virtual void Render() override;

	[[nodiscard]] IBehaviour* GetBehaviour() const;
	void SetBehaviour(IBehaviour* newBehaviour);

protected:
	Agent* OwningAgent() const;

};