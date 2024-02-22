#include <Windows.h>
#include <iostream>
#include <vector>

#include "Memory.h"
#include "Hook.h"
#include "Offsets.h"
#include "Globals.h"
#include "Render.h"
#include "Menu.h"
#include "MagicBullet.h"

typedef BOOL(__stdcall* twglSwapBuffers)(HDC hDC);

twglSwapBuffers owglSwapBuffers;
twglSwapBuffers wglSwapBuffersGateway;

BOOL __stdcall hkwglSwapBuffers(HDC hDC)
{
    Menu::HandleInput();

    return wglSwapBuffersGateway(hDC);
}

void SetupConsole()
{
    if (!AllocConsole()) {
        std::cerr << "[ERROR] allocating console." << std::endl;
        return; // Aborta se falhar em alocar o console
    }

    FILE* pFile;
    if (freopen_s(&pFile, "CONIN$", "r", stdin) != 0)
    {
        std::cerr << "[ERROR] setting CONIN$ to console." << std::endl;
        return;
    }

    if (freopen_s(&pFile, "CONOUT$", "w", stdout) != 0)
    {
        std::cerr << "[ERROR] setting CONOUT$ to console." << std::endl;
        return;
    }


    if (freopen_s(&pFile, "CONOUT$", "w", stderr) != 0)
    {
        std::cerr << "[ERROR] setting CONOUT$ to console." << std::endl;
        return;
    }

    if (pFile)
        fclose(pFile);

    // don't forget to FreeConsole() after use
}

DWORD WINAPI HackThread(HMODULE hModule)
{
    SetupConsole();
    
    Globals::Init();
    MagicBullet::InitHook();
    Menu::Print();
    
    Hook swapBuffersHook("wglSwapBuffers", "opengl32.dll", (BYTE*)hkwglSwapBuffers, (BYTE*)&wglSwapBuffersGateway, 5);

    swapBuffersHook.Enable();

    // FreeConsole();
    // FreeLibraryAndExitThread(hModule, 0);
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    {
        HANDLE hThread = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, nullptr);

        if (hThread == nullptr || hThread == INVALID_HANDLE_VALUE)
        {
            DWORD error = GetLastError();
            std::cerr << "Error creating thread HackerThread, ERROR CODE: " << error << std::endl;
            return FALSE; // Returning FALSE prevents the DLL from being loaded
        }

        CloseHandle(hThread);
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
