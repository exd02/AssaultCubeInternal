#pragma once

#include <vector>

namespace Offsets {
    extern uintptr_t localPlayer;
    extern uintptr_t recoilFuncStart;
    extern uintptr_t currentPlayers;
    extern uintptr_t entityList;
    extern uintptr_t viewMatrix;

    extern uintptr_t headPos;
    extern uintptr_t footPos;
    extern uintptr_t scrnX;
    extern uintptr_t scrnY;
    extern uintptr_t health;
    extern uintptr_t playerTeam;

    extern std::vector<uintptr_t> currentWeaponAmmo;
};