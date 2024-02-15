#include "Game.h"

int Game::gameMode = 0; // tdm for now XD

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