#include <Windows.h>
#include <iostream>
#include <vector>

#include "Memory.h"

// get module base
HMODULE Memory::GetModuleHandleByName(const wchar_t* modName)
{
    HMODULE hModuleProc = GetModuleHandle(modName);

    if (hModuleProc == nullptr)
    {
        std::wcout << L"Could not get \"" << modName << L"\" Module Handle." << std::endl;
        return 0;
    }

    return hModuleProc;
}

bool Memory::Patch(BYTE* dest, BYTE* src, unsigned int size)
{
    DWORD oldProtect = NULL;
    if (!VirtualProtect(dest, size, PAGE_EXECUTE_READWRITE, &oldProtect))
    {
        DWORD error = GetLastError();
        std::cerr << "Error changing memory protection at \"" << (void*)dest << "\", ERROR CODE: " << error << std::endl;
        return false;
    }

    memcpy(dest, src, size);

    if (!VirtualProtect(dest, size, oldProtect, &oldProtect))
    {
        DWORD error = GetLastError();
        std::cerr << "Error changing memory protection back to normal at \"" << (void*)dest << "\", ERROR CODE: " << error << std::endl;
        return false;
    }

    return true;
}

uintptr_t Memory::FindDMAAddy(uintptr_t address, std::vector<uintptr_t> offsets)
{
    const int totalOffsets = offsets.size();

    if (totalOffsets == 0) return address;

    for (int i = 0; i < totalOffsets - 1; i++)
    {
        address = *(uintptr_t *)(address + offsets[i]);
    }

    // Add the last offset to the final address to get the ultimate result.
    return address + offsets[totalOffsets - 1];
}