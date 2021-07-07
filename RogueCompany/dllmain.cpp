#include "stdafx.h"

FVector2D FVector::ToScreen(APlayerController* Controller)
{

	if (!Controller)
		return {};

	FVector2D resultPosition = { 0 };
	Util::ProjectWorldToScreen(Controller, *this, &resultPosition);
	return resultPosition;

}

//std::once_flag openConsole;

VOID Init()
{
	/*std::call_once(openConsole, []()
	{ 
		Helper::OpenConsole();
	});*/

	playerSettings::Init();

	HMODULE base = GetModuleHandle(0);
	if (!base)
		return;

	Util::Init(base);
	Core::Init(base);

	Render::Init(base);
}


BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		Init();
	}

	return TRUE;
}