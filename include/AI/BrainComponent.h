#pragma once

#include "Gameplay/IComponent.h"

class IBehaviour;

class BrainComponent : public IComponent
{
private:
	IBehaviour* m_behaviour;

public:
	virtual void Tick(float dt) override;
	virtual void Render() override;

	[[nodiscard]] IBehaviour* GetBehaviour() const;
	void SetBehaviour(IBehaviour* newBehaviour);

};