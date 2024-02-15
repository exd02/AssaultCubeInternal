#include "Offsets.h"

uintptr_t Offsets::localPlayer = 0x18AC00;
uintptr_t Offsets::recoilFuncStart = 0xC8BA0;
uintptr_t Offsets::currentPlayers = 0x18AC0C;
uintptr_t Offsets::entityList = 0x18AC04;
uintptr_t Offsets::viewMatrix = 0x17DFD0;

uintptr_t Offsets::headPos = 0x4;
uintptr_t Offsets::footPos = 0x28;
uintptr_t Offsets::scrnX = 0x34;
uintptr_t Offsets::scrnY = 0x38;
uintptr_t Offsets::health = 0xEC;
uintptr_t Offsets::playerTeam = 0x30C;

std::vector<uintptr_t> Offsets::currentWeaponAmmo = { 0x364, 0x14, 0x0 };