#include "Globals.h"
#include "Memory.h"

HMODULE Globals::hGameModule;
uintptr_t Globals::gameModuleAddress;
uintptr_t Globals::recoilFuncAddress;

int Globals::screenWidth = 800;
int Globals::screenHeight = 600;

void Globals::Init()
{
	const wchar_t* modName = L"ac_client.exe";

    std::wcout << std::hex << L"[+] Attaching to the game \"" << modName << "\":" << std::endl;

    Globals::hGameModule = Memory::GetModuleHandleByName(modName);
    std::wcout << std::hex << L"\t[-] Game Module Handle: \"" << hGameModule << "\"" << std::endl;

    Globals::gameModuleAddress = (uintptr_t)hGameModule;
    std::wcout << std::hex << L"\t[-] Game Module Address: \"0x" << gameModuleAddress << L"\"" << std::endl;


    std::cout << std::endl; // BREAK LINE SEPARATE CATEGORIES


    std::wcout << std::hex << L"[+] Finding Game Offsets/Addresses: " << std::endl;

    Globals::recoilFuncAddress = gameModuleAddress + Offsets::recoilFuncStart;
    std::wcout << std::hex << L"\t[-] Recoil Function: \"0x" << Globals::recoilFuncAddress << L"\"" << std::endl;
}