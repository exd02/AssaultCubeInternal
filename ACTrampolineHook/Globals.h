#pragma once

#include <Windows.h>
#include <iostream>

#include "Offsets.h"


namespace Globals
{
    extern HMODULE hGameModule;
    extern uintptr_t gameModuleAddress;
    extern uintptr_t recoilFuncAddress;

    extern int screenWidth;
    extern int screenHeight;

    void Init();
};
