#include "Aimbot.h"

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
    
    delta.Normalize();

    localPlayer->cameraAngles.x = -atan2(delta.x, delta.y) / M_PI * 180 + 180;
    localPlayer->cameraAngles.y = atan2(delta.z, sqrt(delta.x * delta.x + delta.y * delta.y)) / M_PI * 180;
}