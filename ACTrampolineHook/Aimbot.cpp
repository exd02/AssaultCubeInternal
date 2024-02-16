#include "Aimbot.h"

#define M_PI 3.14159265358979323846264338327950288

void Aimbot::Aimbot()
{
    Player* localPlayer = *(Player**)(Globals::gameModuleAddress + Offsets::localPlayer);

    if (!localPlayer || localPlayer->isDead)
        return;

    Player* target = localPlayer->GetClosestEnemy();

    if (target == nullptr)
        return;

    // Calculating the direction vector from MyPosition to AimAt
    Vec3 delta = target->headPos - localPlayer->headPos;

    /*
    * atan2 returns [-π/2 ~ +π/2] rad
    * we need to convert to [0° ~ 360°] (units used in the game)
    */
    float x = -atan2(delta.x, delta.y); // [-π/2 ~ +π/2]
    x *= 180 / M_PI; // [-180° ~ +180°]
    x += 180; // [0° ~ +360°]

    /*
    * arc cosine
    * atan2 returns [-π/2 ~ +π/2] rad
    * we need to convert to [-90° ~ +90°], the atan2 result of z/hipotenuse is always going to be in this range
    */
    float y = atan2(delta.z, delta.CalcHipotenusa()); // [-π/2 ~ +π/2]
    y *= 180 / M_PI; // [-90° ~ +90°]

    localPlayer->cameraAngles = { x, y };
}