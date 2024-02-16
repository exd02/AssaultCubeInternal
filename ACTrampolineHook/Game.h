#pragma once

#include <Windows.h>
#include <iostream>
#include "Vec.h"

#define STR_MERGE_IMPL(a, b) a##b
#define STR_MERGE(a, b) STR_MERGE_IMPL(a, b)
#define MAKE_PAD(size) STR_MERGE(_pad, __COUNTER__)[size]
#define DEFINE_MEMBER_N(type, name, offset) struct {unsigned char MAKE_PAD(offset); type name;}

enum
{
	GMODE_DEMO = -1,
	GMODE_TEAMDEATHMATCH = 0,           // 0
	GMODE_COOPEDIT,
	GMODE_DEATHMATCH,
	GMODE_SURVIVOR,
	GMODE_TEAMSURVIVOR,
	GMODE_CTF,                          // 5
	GMODE_PISTOLFRENZY,
	GMODE_BOTTEAMDEATHMATCH,
	GMODE_BOTDEATHMATCH,
	GMODE_LASTSWISSSTANDING,
	GMODE_ONESHOTONEKILL,               // 10
	GMODE_TEAMONESHOTONEKILL,
	GMODE_BOTONESHOTONEKILL,
	GMODE_HUNTTHEFLAG,
	GMODE_TEAMKEEPTHEFLAG,
	GMODE_KEEPTHEFLAG,                  // 15
	GMODE_TEAMPF,
	GMODE_TEAMLSS,
	GMODE_BOTPISTOLFRENZY,
	GMODE_BOTLSS,
	GMODE_BOTTEAMSURVIVOR,              // 20
	GMODE_BOTTEAMONESHOTONKILL,
	GMODE_NUM
};

class weaponInfo
{
public:
	union {
		// DEFINE_MEMBER_N(char, type, 0x0000);
		// DEFINE_MEMBER_N(char, name, 0x0017);
		DEFINE_MEMBER_N(int16_t, shootDelay, 0x004A);
		DEFINE_MEMBER_N(int16_t, damage, 0x004C);
		DEFINE_MEMBER_N(int16_t, accuracy1, 0x0054);
		DEFINE_MEMBER_N(int16_t, knockback, 0x0056);
		DEFINE_MEMBER_N(int16_t, viewmodelRecoil, 0x005C);
		DEFINE_MEMBER_N(int16_t, recoilFirst3Shots, 0x0060);
		DEFINE_MEMBER_N(int16_t, recoilAfter3Shots, 0x0062);
		DEFINE_MEMBER_N(int16_t, isAuto, 0x0066);
	};
};

class Weapon
{
public:
	union {
		DEFINE_MEMBER_N(int, id, 0x0004);
		// DEFINE_MEMBER_N(Player*, owner, 0x0008);
		DEFINE_MEMBER_N(weaponInfo*, weaponInfo, 0x000C);
		DEFINE_MEMBER_N(int *, extraAmmo, 0x0010);
		DEFINE_MEMBER_N(int *, ammo, 0x0014);
		DEFINE_MEMBER_N(int *, shootsFired, 0x001C);
	};
};

class Player
{
public:
	union {
		DEFINE_MEMBER_N(Vector3, headPos, 0x0004);
		DEFINE_MEMBER_N(Vector3, speed, 0x0010);
		DEFINE_MEMBER_N(Vector3, footPos, 0x0028);
		DEFINE_MEMBER_N(Vector3, cameraAngles, 0x0034);
		DEFINE_MEMBER_N(int, health, 0x00EC);
		// DEFINE_MEMBER_N(char[15], name, 0x0205);
		DEFINE_MEMBER_N(int, team, 0x030C);
		DEFINE_MEMBER_N(int, isDead, 0x0318);
		DEFINE_MEMBER_N(Weapon*, currWeapon, 0x0364);
	};

	bool IsValid();
};

namespace Game {
	extern int gameMode;
	bool GamemodeHasTeammates();
};