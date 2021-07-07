#include "core.h"
#include "Discord.h"
#include "aimkeys.h"

namespace Core {

	APawn* Pawn = NULL;
	HMODULE moduleBase;
	ULONG(__fastcall* GetViewPoint)(APlayerController*, FVector*, FRotator*) = NULL;

	/*
	* AController::SetControlRotation
	* 
	*/
	VOID SetControlRotation(APlayerController* Controller, FRotator NewRotation) {

		auto pController = read<PVOID>(Controller);
		if (!pController) {
			return;
		}

		return reinterpret_cast<VOID(__fastcall*)(ULONG_PTR, FRotator)>
			(read<PVOID>((PBYTE)pController + 0x680))((ULONG_PTR)Controller, NewRotation);
	}

	VOID SetIgnoreLookInput(APlayerController* Controller, BOOL IsLocked) {

		auto pController = read<PVOID>(Controller);
		if (!pController) {
			return;
		}

		return reinterpret_cast<VOID(__fastcall*)(ULONG_PTR, CHAR)>
			(read<PVOID>((PBYTE)pController + 0x740))((ULONG_PTR)Controller, IsLocked);
	}

	ULONG GetPlayerViewPointHook(APlayerController* Controller, FVector* pLocation, FRotator* pRotation) {

		GetViewPoint(Controller, pLocation, pRotation);

		/*
		* You can do whatever you want to the camera location/rotation.
		*/

		if (!Pawn) {
			return GetViewPoint(Controller, pLocation, pRotation);;
		}

		auto headPos = Util::GetBoneMatrix(Pawn->Mesh, 110);

		auto ChestPos = Util::GetBoneMatrix(Pawn->Mesh, 178);
		auto pelvis = Util::GetBoneMatrix(Pawn->Mesh, 1);
		if (Settings.Aimbot)
		{
			if (GetAsyncKeyState(keys[aimbot_key])) {
				if (Pawn->Health > 0.0f)
				{
					if (!Settings.ShootDowned && Pawn->bDowned)
					{
						return TRUE;
					}
					
					if (Settings.HeadBox)
					{
						auto angles = FRotator::CalcAngle(*pLocation, headPos).ClampAngles();
						*pRotation = angles;
					}

					if (Settings.ChestBox)
					{
						auto angles = FRotator::CalcAngle(*pLocation, ChestPos).ClampAngles();
						*pRotation = angles;
					}
				}

				return TRUE;
			}

			return GetViewPoint(Controller, pLocation, pRotation);
		}
	}


	VOID Init(HMODULE module) {
		if (!module)
			return;

		moduleBase = module;
		auto addr = Util::FindPattern(moduleBase, xorstr_("\x48\x89\x5C\x24\x10\x48\x89\x74\x24\x18\x55\x41\x56\x41\x57\x48\x8B\xEC"), xorstr_("xxxxxxxxxxxxxxxxxx"));

		if (!addr)
			return;

		DISCORD.HookFunction((uintptr_t)addr, (uintptr_t)GetPlayerViewPointHook, (uintptr_t)&GetViewPoint);
		return;
	}

}
