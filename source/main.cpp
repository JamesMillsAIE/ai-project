#include "Application.h"

#if _DEBUG
#include <crtdbg.h>
#endif

int32 main()
{
#if _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	Application app;
	return app.Run();
}