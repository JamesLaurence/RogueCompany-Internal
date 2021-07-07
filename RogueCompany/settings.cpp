#include "stdafx.h"


Setting Settings;

namespace playerSettings {

	VOID Init() {

		/*
		* Auto Assign Vars to TRUE/FALSE.
		*/

		Settings.Aimbot = TRUE;
		Settings.ESP = TRUE;
		Settings.FOV = 90.0f;
		Settings.PlayerName = TRUE;
		Settings.ShootDowned = TRUE;
		Settings.Glow = false;
		Settings.Crosshair = false;
		Settings.DistanceESP = false;
		Settings.WeaponESP = false;
		Settings.CornerESP = false;
		Settings.Skeleton = false;
		Settings.HeadCircle = false;
		Settings.HeadBox = false;
		Settings.ChestBox = false;
		Settings.pelvis = false;
		Settings.HealEsp = false;
		Settings.keybindSpinBot = 0x14;
		Settings.SpinBot = false;
	}
}