#include "Menu.h"

#include <Windows.h>
#include <iostream>
#include <vector>

#include "Globals.h"
#include "Memory.h"
#include "Offsets.h"
#include "Globals.h"
#include "Render.h"
#include "Vec.h"
#include "ESP.h"
#include "Telekill.h"
#include "Aimbot.h"

#define CMD_COLOR_RED       12 
#define CMD_COLOR_GREEN     10 
#define CMD_COLOR_DEFAULT   7  

#define OPT_FREEZEHEALTH    0
#define OPT_FREEZEAMMO      1
#define OPT_NORECOIL        2
#define OPT_ESP             3
#define OPT_AIM             4
#define OPT_TELEKILL        5
#define OPT_MAGICBULLET     6
#define OPT_TRIGGERBOT      7

namespace Menu {

    struct MenuOption {
        bool status;
        const std::string description;
    };

    // I should have used a class but it's too late now xD
    std::vector<MenuOption> menuOptions = {
        { false, "Freeze Health (F1)" },// 0
        { false, "Freeze Ammo (F2)" },  // 1
        { false, "NoRecoil (F3)" },     // 2
        { false, "ESP (F4)" },          // 3
        { false, "Aimbot (F5)" },       // 4
        { false, "Telekill (F6)" },     // 5
        { false, "MagicBullet (F7)" },   // 6
        { false, "TriggetBot (F8)" }   // 7
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
        Player* localPlayer = *(Player**)(Globals::gameModuleAddress + Offsets::localPlayer);

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
            menuOptions[OPT_ESP].status = !menuOptions[OPT_ESP].status;
            hasChanged = true;
        }

        if (GetAsyncKeyState(VK_F5) & 1)
        {
            menuOptions[OPT_AIM].status = !menuOptions[OPT_AIM].status;
            hasChanged = true;
        }

        if (GetAsyncKeyState(VK_F6) & 1)
        {
            menuOptions[OPT_TELEKILL].status = !menuOptions[OPT_TELEKILL].status;
            hasChanged = true;

            if (menuOptions[OPT_TELEKILL].status)
            {
                // save the current position
                if (!localPlayer->isDead)
                    Telekill::originalPosition = localPlayer->footPos;
            }
            else
            {
                // teleport the player back to where he was
                if (!localPlayer->isDead)
                    localPlayer->footPos = Telekill::originalPosition;
            }
        }

        if (GetAsyncKeyState(VK_F7) & 1)
        {
            menuOptions[OPT_MAGICBULLET].status = !menuOptions[OPT_MAGICBULLET].status;
            hasChanged = true;
        }

        if (GetAsyncKeyState(VK_F8) & 1)
        {
            menuOptions[OPT_TRIGGERBOT].status = !menuOptions[OPT_TRIGGERBOT].status;
            hasChanged = true;
        }

        if (menuOptions[OPT_FREEZEHEALTH].status)
        {
            localPlayer->health = 1337;
        }

        if (menuOptions[OPT_FREEZEAMMO].status)
        {
            *(int*)localPlayer->currWeapon->ammo = 1337;
        }

        if (menuOptions[OPT_ESP].status)
        {
            Render::SetupOrtho();
            ESP::Draw();
            Render::RestoreGL();
        }

        if (menuOptions[OPT_AIM].status)
        {
            Aimbot::Aimbot();
        }

        if (menuOptions[OPT_TELEKILL].status)
        {
            Telekill::Telekill();
        }

        if (hasChanged)
        {
            system("cls");
            Menu::Print();
        }
    }
};