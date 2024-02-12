#include "Render.h"

Render::Color_RGBA Render::red{ 1.0f, 0.0f, 0.0f, 1.0f };
Render::Color_RGBA Render::green{ 0.0f, 1.0f, 0.0f, 1.0f };
Render::Color_RGBA Render::blue{ 0.0f, 0.0f, 1.0f, 1.0f };

void Render::SetupOrtho()
{
	// Save the current attrib and matrix (it will be reverted in RestoreGL() )
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glPushMatrix();

	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glViewport(0, 0, viewport[2], viewport[3]);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, viewport[2], viewport[3], 0, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glDisable(GL_DEPTH_TEST);
}

void Render::RestoreGL()
{
	glPopMatrix();
	glPopAttrib();
}

void Render::DrawLine(float x, float y, float x2, float y2, const Color_RGBA& lineColor)
{
	glColor4f(lineColor.r, lineColor.g, lineColor.b, lineColor.a);

	glBegin(GL_LINES);
		glVertex2f(x ,  y);
		glVertex2f(x2, y2);
	glEnd();
}

Vec2 Render::WorldToScreen(const float* viewMatrix, const Vec3& footPos) {
	// transform footposition to screen cordinates using viewmatrix
	float transformedX = viewMatrix[0] * footPos.x + viewMatrix[4] * footPos.y + viewMatrix[8] * footPos.z + viewMatrix[12];
	float transformedY = viewMatrix[1] * footPos.x + viewMatrix[5] * footPos.y + viewMatrix[9] * footPos.z + viewMatrix[13];
	float transformedZ = viewMatrix[2] * footPos.x + viewMatrix[6] * footPos.y + viewMatrix[10] * footPos.z + viewMatrix[14];
	float transformedW = viewMatrix[3] * footPos.x + viewMatrix[7] * footPos.y + viewMatrix[11] * footPos.z + viewMatrix[15];

	// return if behind the camera
	if (transformedZ < 0.0f)
		return Vec2(-1.0f, -1.0f);

	// perspective projection
	transformedX /= transformedW;
	transformedY /= transformedW;

	Vec2 screenPos;

	screenPos.x = (transformedX + 1.0f) * 0.5f * Globals::screenWidth;
	screenPos.y = (1.0f - transformedY) * 0.5f * Globals::screenHeight;

	return screenPos;
}
