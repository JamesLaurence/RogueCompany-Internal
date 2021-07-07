#pragma once
#include "stdafx.h"

namespace Core {

	extern APawn* Pawn;

	VOID SetControlRotation(APlayerController* Controller, FRotator NewRotation);
	VOID SetIgnoreLookInput(APlayerController* Controller, BOOL IsLocked);
	VOID Init(HMODULE module);
}