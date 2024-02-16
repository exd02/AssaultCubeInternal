#pragma once

#include <string>
#include <iostream>
#include <math.h>

struct Vec4
{
    float x, y, z, w;

    std::string toString() {
        return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ", " + std::to_string(w) + ")";
    }
};

struct Vec3
{
	float x, y, z;

    std::string ToString()
    {
        return "(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
    }

    Vec3 operator-(const Vec3& other) const {
        return { x - other.x, y - other.y, z - other.z };
    }

    void Normalize()
    {
        // Calculating the length (magnitude) of the vector
        float length = std::sqrt(x * x + y * y + z * z);

        // Normalizing the vector
        if (length != 0) {
            x /= length;
            y /= length;
            z /= length;
        }
    }

    float Distance(const Vec3& otherPoint) const
    {
        float dx = otherPoint.x - x;
        float dy = otherPoint.y - y;
        float dz = otherPoint.z - z;
        return std::sqrt(dx * dx + dy * dy + dz * dz);
    }

    float CalcHipotenusa()
    {
        float squaresum = x*x + y*y + z*z;
        return sqrt(squaresum);
    }
};

struct Vec2
{
	float x, y;

    std::string toString() {
        return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
    }
};

using Vector4 = Vec4;
using Vector3 = Vec3;
using Vector2 = Vec2;