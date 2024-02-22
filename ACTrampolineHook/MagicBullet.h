#pragma once

#include "Game.h"
#include "Hook.h"

typedef void(__fastcall* RayDmg_T)(Vec3* from, Vec3* to, Player* attacker);

extern RayDmg_T RayDmg_Gateway;

namespace MagicBullet
{
	extern Hook hkRayDmg;
	void InitHook();
};