﻿#include "Aimbot.h"

#define M_PI   3.14159265358979323846264338327950288

void Aimbot::Aimbot()
{
    Player* localPlayer = *(Player**)(Globals::gameModuleAddress + Offsets::localPlayer);

    if (localPlayer->isDead)
        return;

    int* currentPlayers = (int*)(Globals::gameModuleAddress + Offsets::currentPlayers);

    uintptr_t entityList = *(uintptr_t*)(Globals::gameModuleAddress + Offsets::entityList);

    // the target is the closest player
    float closestDistance = FLT_MAX;
    Player* target = nullptr;
    for (int i = 1; i < *currentPlayers; i++)
    {
        Player* p = *(Player**)(entityList + (4 * i));

        if (p == nullptr)
            continue;

        if (p->isDead)
            continue;

        if (localPlayer->team == p->team)
            continue;

        float distance = localPlayer->headPos.Distance(p->headPos);
        if (distance < closestDistance)
        {
            closestDistance = distance;
            target = p;
        }

        break;
    }

    if (target == nullptr)
        return;

    // Calculating the direction vector from MyPosition to AimAt
    Vec3 delta = target->headPos - localPlayer->headPos;

    /*
    * atan2 returns [-π/2 ~ +π/2] rad
    * we need to convert to [0° ~ 360°] (units used in the game)
    */
    float x = -atan2(delta.x, delta.y); // [-π/2 ~ +π/2]
    x *= 180 / M_PI; // [-180° ~ +180°]
    x += 180; // [0° ~ +360°]

    /*
    * arc cosine
    * atan2 returns [-π/2 ~ +π/2] rad
    * we need to convert to [-90° ~ +90°], the atan2 result of z/hipotenuse is always going to be in this range
    */
    float y = atan2(delta.z, delta.CalcHipotenusa()); // [-π/2 ~ +π/2]
    y *= 180 / M_PI; // [-90° ~ +90°]

    localPlayer->cameraAngles.x = x;
    localPlayer->cameraAngles.y = y;
}