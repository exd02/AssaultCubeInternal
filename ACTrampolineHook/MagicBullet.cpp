#include "MagicBullet.h"

RayDmg_T RayDmg_Gateway;

/*
* Assembly:
* .text:004C73B9                 lea     edx, [esp+30h+to] ;    to
* .text:004C73BD                 push    dword ptr [esi+8] ;    attacker
* .text:004C73C0                 lea     ecx, [esp+34h+from] ;  from
* .text:004C73C4                 call    raydmg
* 
* __fastcall args:
* The first two DWORD: ECX and EDX (left to right)
* Others: stack (right to left)
*/
void __fastcall RayDmg_Hook(Vec3* from, Vec3* to, Player* attacker)
{
    #ifdef _DEBUG
        std::cout << "[+] MagicBullet: " << attacker->headPos.ToString() << std::endl;
        std::cout << "\t[-] From: " << from->ToString() << std::endl;
        std::cout << "\t[-] To: " << to->ToString() << std::endl;
        std::cout << "\t[-] AttackerHead: " << attacker->headPos.ToString() << std::endl;
    #endif

    Player* localPlayer = *(Player**)(Globals::gameModuleAddress + Offsets::localPlayer);

    if (attacker == localPlayer)
    {
        Player* target = attacker->GetClosestEnemy();
        if (target)
        {
            from->x = target->headPos.x;
            from->y = target->headPos.y;
            from->z = target->headPos.z;

            #ifdef _DEBUG
                std::cout << "\t[-] New From: " << from->ToString() << std::endl;
            #endif
        }
    }

    RayDmg_Gateway(from, to, attacker);
}

Hook MagicBullet::hkRayDmg;

void MagicBullet::InitHook()
{
    MagicBullet::hkRayDmg.Init((BYTE*)0x4C9510, (BYTE*)RayDmg_Hook, (BYTE*)&RayDmg_Gateway, 6);
}