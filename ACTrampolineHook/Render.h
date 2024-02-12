#pragma once
#pragma comment(lib, "OpenGL32.lib")

#include <Windows.h>
#include <iostream>
#include <gl/GL.h>
#include "Vec.h"
#include "Globals.h"

namespace Render {
	struct Color_RGBA {
		float r, g, b, a;
	};

	extern Color_RGBA red;
	extern Color_RGBA blue;
	extern Color_RGBA green;


	void SetupOrtho();
	void RestoreGL();
	void DrawLine(float x, float y, float x2, float y2, const Color_RGBA& color);
	Vec2 WorldToScreen(const float* viewMatrix, const Vec3& footPos);
};
