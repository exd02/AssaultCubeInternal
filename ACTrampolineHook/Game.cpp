#include "Game.h"

int Game::gameMode = 0; // do it later - dword_58ABF8

bool Game::GamemodeHasTeammates()
{
    if (
        Game::gameMode == GMODE_BOTTEAMONESHOTONKILL ||
        Game::gameMode == GMODE_TEAMONESHOTONEKILL ||
        Game::gameMode == GMODE_BOTTEAMDEATHMATCH ||
        Game::gameMode == GMODE_TEAMDEATHMATCH ||
        Game::gameMode == GMODE_TEAMSURVIVOR ||
        Game::gameMode == GMODE_TEAMLSS ||
        Game::gameMode == GMODE_CTF ||
        Game::gameMode == GMODE_TEAMKEEPTHEFLAG ||
        Game::gameMode == GMODE_HUNTTHEFLAG ||
        Game::gameMode == GMODE_TEAMPF ||
        Game::gameMode == GMODE_BOTTEAMSURVIVOR ||
        Game::gameMode == GMODE_BOTTEAMONESHOTONKILL
        )
        return true;

	return false;
}

bool Player::IsValid()
{
    if (this == nullptr)
        return false;

    return true;
}

Player* Player::GetClosestEnemy()
{
    Player* localPlayer = *(Player**)(Globals::gameModuleAddress + Offsets::localPlayer);

    if (!localPlayer || localPlayer->isDead)
        return nullptr;

    int* currentPlayers = (int*)(Globals::gameModuleAddress + Offsets::currentPlayers);

    uintptr_t entityList = *(uintptr_t*)(Globals::gameModuleAddress + Offsets::entityList);

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

        float distance = localPlayer->pos.Distance(p->pos);

        if (distance < closestDistance)
        {
            closestDistance = distance;
            target = p;
        }
    }

    return target;
}