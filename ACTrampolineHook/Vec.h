#pragma once

#include <string>

struct Vec3
{
	float x, y, z;

    std::string toString() {
        return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
    }
};

struct Vec2
{
	float x, y;

    std::string toString() {
        return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
    }
};
