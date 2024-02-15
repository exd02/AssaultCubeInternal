#include "Telekill.h"

Vec3 Telekill::originalPosition{ 0 };

void Telekill::Telekill()
{
    Player* localPlayer = *(Player**)(Globals::gameModuleAddress + Offsets::localPlayer);

    if (localPlayer->isDead)
        return;

    int* currentPlayers = (int*)(Globals::gameModuleAddress + Offsets::currentPlayers);

    uintptr_t entityList = *(uintptr_t*)(Globals::gameModuleAddress + Offsets::entityList);

    // the target is going to be the first enemy encountered validated
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

        target = p;
        break;
    }

    if (target == nullptr)
        return;

    localPlayer->footPos = target->footPos;
}