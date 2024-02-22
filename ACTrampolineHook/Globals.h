#pragma once

#include <Windows.h>
#include <iostream>

#include "Memory.h"
#include "Offsets.h"

namespace Globals
{
    extern const wchar_t* modName;
    extern HMODULE hGameModule;
    extern uintptr_t gameModuleAddress;
    extern uintptr_t recoilFuncAddress;
    extern uintptr_t raydmgAddress;

    void Init();
    void PrintAdresses();
};

