#pragma once
#include "stdafx.h"

namespace Util {
	extern UWorld* World;
	VOID Init(HMODULE module);
	char* GetObjectName(AActor* Actor);
	BOOL ProjectWorldToScreen(APlayerController* Controller, FVector& WorldPosition, FVector2D* ScreenPosition);
	FVector GetBoneMatrix(USkeletalMeshComponent* mesh, INT index);
	FBox GetBoundingBox(USkeletalMeshComponent* mesh, FVector RelativeLocation);
	BOOL LineOfSightTo(APlayerController* Controller, AActor* Actor);
}