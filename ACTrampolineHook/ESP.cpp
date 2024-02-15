#include "ESP.h"

void ESP::Draw()
{
    // uintptr_t localPlayer = *(uintptr_t*)(Globals::gameModuleAddress + Offsets::localPlayer);
    Player* localPlayer = *(Player**)(Globals::gameModuleAddress + Offsets::localPlayer);
    int* currentPlayers = (int *)(Globals::gameModuleAddress + Offsets::currentPlayers);
    float* matrix = (float *)(Globals::gameModuleAddress + Offsets::viewMatrix);

    uintptr_t entityList = *(uintptr_t *)(Globals::gameModuleAddress + Offsets::entityList);

    int viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);

    for (int i = 1; i < *currentPlayers; i++)
    {
        Player* p = *(Player**)(entityList + (4 * i));
        
        if (p == nullptr)
            continue;
        
        Render::Color_RGBA color = localPlayer->team == p->team ? Render::green : Render::red;

        Vec3 screenHead{ 0 };
        Vec3 screenFoot{ 0 };

        if (Render::WorldToScreen(p->footPos, screenFoot, matrix, viewport[2], viewport[3]) && Render::WorldToScreen(p->headPos, screenHead, matrix, viewport[2], viewport[3]))
        {
            float boxHeight = screenHead.y - screenFoot.y;
            float boxWidth = boxHeight / 2.f;

            Render::DrawLine(viewport[2] / 2, viewport[3], screenFoot.x, screenFoot.y, color);
            Render::DrawRect(screenHead.x - (boxWidth / 2.f), screenHead.y, screenFoot.x + (boxWidth / 2), screenFoot.y, color);
        }
    }
}