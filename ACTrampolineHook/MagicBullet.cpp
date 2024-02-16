#include "MagicBullet.h"

void MagicBullet::MagicBullet()
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

    // hook the shoot function
    // change the bullet to spawn inside target.head
}