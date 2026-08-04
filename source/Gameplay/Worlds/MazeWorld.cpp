#include "Gameplay/Worlds/MazeWorld.h"

#include "AI/Agent.h"
#include "AI/Navigation/Navigation.h"

#include "Gameplay/Components/AnimatedMeshComponent.h"

MazeWorld::MazeWorld()
{
	Navigation& navigation = Navigation::GetInstance();
	Agent* agent = MakeActor<Agent>();

	agent->MakeComponent<MeshComponent>("Models/SM_Cube");
	agent->SetAgentType(navigation.FindAgentType("default"));
}
