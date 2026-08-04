#include "Gameplay/Worlds/MazeWorld.h"

#include "Resources.h"

#include "AI/Agent.h"
#include "AI/Navigation/Navigation.h"

#include "Gameplay/Components/AnimatedMeshComponent.h"

MazeWorld::MazeWorld()
{
	Navigation& navigation = Navigation::GetInstance();
	Agent* agent = MakeActor<Agent>();

	AnimatedMeshComponent* comp = agent->MakeComponent<AnimatedMeshComponent>("Models/SK_AnimatedYBot");
	comp->SetMeshScale(10.f);

	agent->SetAgentType(navigation.FindAgentType("default"));

	m_customModel = new Resource;
	m_customModel->model = LoadModelFromMesh(GenMeshPlane(100.f, 100.f, 10, 10));
	////m_customModel->model.materials[0].
	//
	//Actor* planeActor = MakeActor<Actor>();
	//planeActor->MakeComponent<MeshComponent>(m_customModel);
}

MazeWorld::~MazeWorld()
{
	UnloadModel(m_customModel->model);
	delete m_customModel;
}
