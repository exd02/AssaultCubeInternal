#pragma once

#include "Vec.h"

struct Player
{
	int health;
	bool onGround;

	Vec3 headPos;
	Vec3 footPos;
	Vec3 speed;
	
	float yaw, pitch, roll;
};

