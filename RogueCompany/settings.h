#pragma once
#include "stdafx.h"

struct Setting {
	BOOL ShowMenu;
	bool Aimbot;
	float FOV;
	bool ESP;
	bool PlayerName;
	bool ShootDowned;
	bool Glow = false;
	bool CornerESP = false;
	bool Crosshair = false;
	bool Skeleton = false;
	bool SpinBot = false;
	bool HeadBox = false;
	bool ChestBox = false;
	bool pelvis = false;
	bool HealEsp = false;
	bool DistanceESP = false;
	bool WeaponESP = false;
	bool HeadCircle = false;
	int keybindSpinBot = 0x14;
};


extern Setting Settings;

namespace playerSettings {

	extern VOID Init();
}