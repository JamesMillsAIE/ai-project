#pragma once

class Actor;

class IComponent
{
	friend Actor;

private:
	Actor* m_owner;

public:
	IComponent()
		: m_owner{ nullptr }
	{}
	
	virtual ~IComponent()
	{}

public:
	[[nodiscard]] Actor* Owner() const
	{
		return m_owner;
	}

	virtual void BeginPlay()
	{}

	virtual void Tick(float dt)
	{}

	virtual void Render()
	{}

	virtual void EndPlay()
	{}

};