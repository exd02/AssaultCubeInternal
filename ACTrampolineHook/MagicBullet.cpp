#include "MagicBullet.h"

void MagicBullet::MagicBullet()
{
    Player* localPlayer = *(Player**)(Globals::gameModuleAddress + Offsets::localPlayer);

    if (!localPlayer || localPlayer->isDead)
        return;

    Player* target = localPlayer->GetClosestEnemy();

    if (target == nullptr)
        return;

    // hook the shoot function
    // change the bullet to spawn inside target.head
}