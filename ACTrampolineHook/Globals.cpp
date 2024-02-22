#include "Globals.h"

const wchar_t* Globals::modName = L"ac_client.exe";
HMODULE Globals::hGameModule;
uintptr_t Globals::gameModuleAddress;
uintptr_t Globals::recoilFuncAddress;
uintptr_t Globals::raydmgAddress;

void Globals::Init()
{
    Globals::hGameModule = Memory::GetModuleHandleByName(modName);
    Globals::gameModuleAddress = (uintptr_t)hGameModule;
    Globals::recoilFuncAddress = gameModuleAddress + Offsets::recoilFuncStart;
    Globals::raydmgAddress = gameModuleAddress + Offsets::raydmgFunc;

#ifdef _DEBUG
    PrintAdresses();
#endif

    std::cout << std::endl;
}

void Globals::PrintAdresses()
{
    std::wcout << std::hex << L"[+] Attaching to the game \"" << modName << "\":" << std::endl;
    std::wcout << std::hex << L"\t[-] Game Module Handle: \"0x" << hGameModule << "\"" << std::endl;
    std::wcout << std::hex << L"\t[-] Game Module Address: \"0x" << gameModuleAddress << L"\"" << std::endl;
    std::cout << std::endl; // BREAK LINE SEPARATE CATEGORIES
    std::wcout << std::hex << L"[+] Finding Game Functions: " << std::endl;
    std::wcout << std::hex << L"\t[-] Recoil Function: \"0x" << Globals::recoilFuncAddress << L"\"" << std::endl;
    std::wcout << std::hex << L"\t[-] Attack Function: \"0x" << Globals::raydmgAddress << L"\"" << std::endl;
}