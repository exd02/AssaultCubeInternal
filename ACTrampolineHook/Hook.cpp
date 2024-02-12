#include "Hook.h"

bool Detour32(BYTE* src, BYTE* dst, const int len)
{
    if (len < 5)
        return false;

    DWORD oldProtect;
    if (!VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &oldProtect))
    {
        DWORD error = GetLastError();
        std::cerr << "Error changing memory protection at \"" << src << "\", ERROR CODE: " << error << std::endl;
        return false;
    }

    // if your len > 5 you need to fill the remaining bytes with NOPs
    memset(src, 0x90, len);

    uintptr_t relativeAddress = dst - src - 5;

    *src = 0xE9;                                // jmp opcode = 0x09
    *(uintptr_t*)(src + 1) = relativeAddress;  // address to jump

    if (!VirtualProtect(src, len, oldProtect, &oldProtect))
    {
        DWORD error = GetLastError();
        std::cerr << "Error changing memory protection back to normal at \"" << src << "\", ERROR CODE: " << error << std::endl;
        return false;
    }

    return true;
}

// src = original function
// dst = hooked function
BYTE* TrampHook32(BYTE* src, BYTE* dst, const int len)
{
    if (len < 5) return 0;

    // Create the Gateway
    BYTE* gateway = (BYTE*)VirtualAlloc(0, len, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);

    // Write the stolen bytes to the gateway
    memcpy_s(gateway, len, src, len);

    // Get the gateway to destination address
    uintptr_t gatewayRelativeAddress = src - gateway - 5;

    *(gateway + len) = 0xE9;                                                // jmp opcode = 0x09
    *(uintptr_t*)((uintptr_t)gateway + len + 1) = gatewayRelativeAddress;  // address to jump

    Detour32(src, dst, len);

    return gateway;
}

Hook::Hook(const char* exportName, const char* modName, BYTE* dst, BYTE* PtrToGatewayFnPtr, uintptr_t len)
{
    HMODULE hMod = GetModuleHandleA(modName);

    this->src = (BYTE*)GetProcAddress(hMod, exportName);
    this->dst = dst;
    this->len = len;
    this->PtrToGatewayFnPtr = PtrToGatewayFnPtr;
}

void Hook::Enable()
{
    memcpy(originalBytes, src, len);
    *(uintptr_t*)PtrToGatewayFnPtr = (uintptr_t)TrampHook32(src, dst, len);
    bStatus = true;
}

void Hook::Disable()
{
    Memory::Patch(src, originalBytes, len);
    bStatus = false;
}