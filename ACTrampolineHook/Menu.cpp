#include "Menu.h"

#include <Windows.h>
#include <iostream>
#include <vector>

#include "Globals.h"
#include "Memory.h"
#include "Offsets.h"
#include "Globals.h"
#include "Render.h"
#include "Player.h"
#include "Vec.h"

#define CMD_COLOR_RED       12 
#define CMD_COLOR_GREEN     10 
#define CMD_COLOR_DEFAULT   7  

#define OPT_FREEZEHEALTH    0
#define OPT_FREEZEAMMO      1
#define OPT_NORECOIL        2
#define OPT_ESPLINE         3

namespace Menu {

    struct MenuOption {
        bool status;
        const std::string description;
    };

    std::vector<MenuOption> menuOptions = {
        { false, "Freeze Health (F1)" },// 0
        { false, "Freeze Ammo (F2)" },  // 1
        { false, "NoRecoil (F3)" },     // 2
        { false, "ESP Line (F4)" }      // 3
    };

    void SetConsoleColor(int color) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    }

    void Menu::Print() {
        for (MenuOption o : menuOptions)
        {
            std::cout << "[";

            if (o.status) {
                SetConsoleColor(CMD_COLOR_GREEN);
                std::cout << "ON";
            }
            else {
                SetConsoleColor(CMD_COLOR_RED);
                std::cout << "OFF";
            }
            SetConsoleColor(CMD_COLOR_DEFAULT);

            std::cout << "] " << o.description << std::endl;
        }
    }
    
    void HandleInput()
    {
        bool hasChanged = false;

        if (GetAsyncKeyState(VK_F1) & 1)
        {
            menuOptions[OPT_FREEZEHEALTH].status = !menuOptions[OPT_FREEZEHEALTH].status;
            hasChanged = true;
        }

        if (GetAsyncKeyState(VK_F2) & 1)
        {
            menuOptions[OPT_FREEZEAMMO].status = !menuOptions[OPT_FREEZEAMMO].status;
            hasChanged = true;
        }

        if (GetAsyncKeyState(VK_F3) & 1)
        {
            menuOptions[OPT_NORECOIL].status = !menuOptions[OPT_NORECOIL].status;
            hasChanged = true;

            uintptr_t recoilFunctionAddress = Globals::gameModuleAddress + Offsets::recoilFuncStart;

            if (menuOptions[OPT_NORECOIL].status)
            {
                Memory::Patch((BYTE*)recoilFunctionAddress, (BYTE*)"\xC2\x8", 3);
            }
            else
            {
                Memory::Patch((BYTE*)recoilFunctionAddress, (BYTE*)"\x83\xEC\x28", 3);
            }
        }

        if (GetAsyncKeyState(VK_F4) & 1)
        {
            menuOptions[OPT_ESPLINE].status = !menuOptions[OPT_ESPLINE].status;
            hasChanged = true;
        }

        if (menuOptions[OPT_FREEZEHEALTH].status) {
            uintptr_t localPlayerAddress = *(uintptr_t *)(Globals::gameModuleAddress + Offsets::localPlayer);
            int* health = (int *)(localPlayerAddress + Offsets::health);
            *health = 1337;
        }

        if (menuOptions[OPT_FREEZEAMMO].status) {
            uintptr_t localPlayerAddress = *(uintptr_t*)(Globals::gameModuleAddress + Offsets::localPlayer);
            int* ammo = (int*)(Memory::FindDMAAddy(localPlayerAddress, Offsets::currentWeaponAmmo));
            *ammo = 1337;
        }

        if (menuOptions[OPT_ESPLINE].status)
        {
            Render::SetupOrtho();

            uintptr_t localPlayer = *(uintptr_t*)(Globals::gameModuleAddress + Offsets::localPlayer);
            int currentPlayers = *(int *)(Globals::gameModuleAddress + Offsets::currentPlayers);
            uintptr_t entityList = *(uintptr_t *)(Globals::gameModuleAddress + Offsets::entityList);

            float v[16]{ 0 };
            memcpy(v, (void *)(Globals::gameModuleAddress + Offsets::viewMatrix), 16 * sizeof(float));

            // for loop all players
            for (int i = 1; i < currentPlayers; i++)
            {
                uintptr_t player = *(uintptr_t *)(entityList + (4 * i));

                int health = *(int*)(player + Offsets::health);

                if (health <= 0 || health > 100)
                    continue;

                // Vec3 headPos = *(Vec3 *)(player + Offsets::headPos);
                Vec3 footPos = *(Vec3*)(player + Offsets::footPos);

                int team = *(int*)(player + Offsets::playerTeam);
                int localPlayerTeam = *(int*)(localPlayer + Offsets::playerTeam);

                Render::Color_RGBA lineColor = (team == localPlayerTeam) ? Render::blue : Render::red;

                Vec2 screenCordinates = Render::WorldToScreen(v, footPos);

                if (screenCordinates.x != -1.0f && screenCordinates.y != -1.0f) // if it's not behing the camera
                    Render::DrawLine(Globals::screenWidth/2, Globals::screenHeight, screenCordinates.x, screenCordinates.y, lineColor);
            }

            Render::RestoreGL();
        }

        if (hasChanged)
        {
            system("cls");
            Menu::Print();
        }
    }
};