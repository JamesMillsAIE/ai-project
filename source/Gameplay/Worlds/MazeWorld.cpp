#include "Gameplay/Worlds/MazeWorld.h"

#include "AI/Agent.h"

MazeWorld::MazeWorld()
{
	MakeActor<Agent>();
}
