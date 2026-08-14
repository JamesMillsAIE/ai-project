#include "Application.h"

#if _DEBUG
#include <crtdbg.h>
#endif

using AiForGames::Application;

int main()
{
#if _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	return Application().Run();
}