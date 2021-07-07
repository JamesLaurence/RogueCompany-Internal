#include "util.h"
#include <fstream>

namespace Util {

	HMODULE moduleBase;
	UWorld* World;

	VOID FreeMemory(PVOID buffer) {

		static PBYTE addr = NULL;
		if (!addr) {
			
			addr = FindPattern(moduleBase,
				xorstr_("\x48\x85\xC9\x00\x2E\x53\x48"),
				xorstr_("xxx?xxx"));

			if (!addr)
				return;
		}

		return reinterpret_cast<VOID(*)(PVOID)>(addr)(buffer);
	}

	char* GetObjectName(AActor* Actor) {

		static PBYTE addr = NULL;
		if (!addr) {

			addr = FindPattern(moduleBase,
				xorstr_("\x40\x53\x48\x83\xEC\x20\x48\x8B\xD9\x48\x85\xD2\x75\x45\x33\xC0\x48\x89\x01\x48\x89\x41\x08\x8D\x50\x05\xE8\x00\x00\x00\x00\x8B\x53\x08\x8D\x42\x05\x89\x43\x08\x3B\x43\x0C\x7E\x08\x48\x8B\xCB\xE8\x00\x00\x00\x00\x48\x8B\x0B\x48\x8D\x15\x00\x00\x00\x00\x41\xB8\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x48\x8B\xC3\x48\x83\xC4\x20\x5B\xC3\x48\x8B\x42\x18"),
				xorstr_("xxxxxxxxxxxxxxxxxxxxxxxxxxx????xxxxxxxxxxxxxxxxxx????xxxxxx????xx????x????xxxxxxxxxxxxx"));
		}

		auto GetObjectName = reinterpret_cast<FString * (*)(FString*, AActor*)>(addr);

		FString buffer;
		GetObjectName(&buffer, Actor);

		if (!buffer.c_str()) {
			return {};
		}

		CHAR result[256];
		strcpy_s(result, sizeof(result), buffer.c_str());
		FreeMemory((PVOID)buffer.data());

		return result;
	}

	
	FVector GetBoneMatrix(USkeletalMeshComponent* mesh, INT index) {

		static PBYTE addr = NULL;
		if (!addr) {

			addr = FindPattern(moduleBase,
				xorstr_("\x48\x8B\xC4\x55\x53\x56\x57\x41\x54\x41\x56\x41\x57\x48\x8D\x68\x00\x48\x81\xEC\x00\x00\x00\x00\x0F\x29\x78"),
				xorstr_("xxxxxxxxxxxxxxxx?xxx????xxx"));
		}

		auto GetBoneMatrix = reinterpret_cast<FMatrix*(*)(USkeletalMeshComponent*, FMatrix*, INT)>(addr);

		FMatrix buffer = { 0 };
		GetBoneMatrix(mesh, &buffer, index);

		return FVector({ buffer.M[3][0], buffer.M[3][1], buffer.M[3][2] });
	}

	FBox GetBoundingBox(USkeletalMeshComponent* mesh, FVector RelativeLocation) {

		static PBYTE addr = NULL;
		if (!addr) {

			addr = FindPattern(moduleBase,
				xorstr_("\xE8\x00\x00\x00\x00\x48\x8B\x45\x48\x48\x8D\x55\xD8"),
				xorstr_("x????xxxxxxxx"));

			addr = RVA(addr, 5);
		}

		if (!mesh->SkeletalMesh)
			return {};

		auto GetBoundingBox = reinterpret_cast<VOID(*)(USkeletalMesh*, FBoxSphereBounds*)>(addr);

		FBoxSphereBounds buffer = { 0 };
		GetBoundingBox(mesh->SkeletalMesh, &buffer);

		FBox box = {};
		box.Min = RelativeLocation - buffer.BoxExtent;
		box.Max = RelativeLocation + buffer.BoxExtent;
		
		return box;
	}

	BOOL ProjectWorldToScreen(APlayerController* Controller, FVector& WorldPosition, FVector2D* ScreenPosition) {

		static PBYTE addr = NULL;
		if (!addr) {

			addr = FindPattern(moduleBase,
				xorstr_("\xE8\x00\x00\x00\x00\x0F\x10\x07\x44\x0F\xB6\xE0"),
				xorstr_("x????xxxxxxx"));

			addr = RVA(addr, 5);
		}

		return reinterpret_cast<CHAR(*)
			(APlayerController*, FVector, FVector2D*, CHAR)>(addr)
			(Controller, WorldPosition, ScreenPosition, FALSE);
	}

	BOOL LineOfSightTo(APlayerController* Controller, AActor* Actor) {

		static PBYTE addr = NULL;
		if (!addr) {

			addr = FindPattern(moduleBase,
				xorstr_("\x40\x55\x53\x56\x57\x48\x8D\x6C\x24\xF8\x48\x81\xEC\x08\x01\x00\x00\x48\x8B\x05\x00\x00\x00\x00\x48\x33\xC4\x48\x89\x45\xE0"),
				xorstr_("xxxxxxxxxxxxxxxxxxxx????xxxxxxx"));

			if (!addr)
				return FALSE;
		}

		auto LineOfSight = reinterpret_cast<BOOL(*)(APlayerController*, AActor*, FVector)>(addr);

		return LineOfSight(Controller, Actor, FVector({ 0, 0, 0 }));
	}

	VOID Init(HMODULE module) {

		if (!module)
			return;

		moduleBase = module;

		auto addr = FindPattern(module,
			xorstr_("\x48\x89\x05\x00\x00\x00\x00\x48\x8B\xB7\x00\x00\x00\x00"),
			xorstr_("xxx????xxx????"));

		if (!addr)
			return;

		addr = RVA(addr, 7);

		World = (UWorld*)addr;
	}
}