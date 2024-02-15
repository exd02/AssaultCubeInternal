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

void Render::DrawLine(float x, float y, float x2, float y2, const Color_RGBA& color)
{
	glColor4f(color.r, color.g, color.b, color.a);

	glBegin(GL_LINES);
		glVertex2f(x ,  y);
		glVertex2f(x2, y2);
	glEnd();
}

void Render::DrawRect(float x, float y, float x2, float y2, const Color_RGBA& color)
{
	glColor4f(color.r, color.g, color.b, color.a);

	glBegin(GL_LINE_LOOP);
		glVertex2f(x, y);
		glVertex2f(x2, y);
		glVertex2f(x2, y2);
		glVertex2f(x, y2);
	glEnd();
}

bool Render::WorldToScreen(const Vec3 &pos, Vec3& screen, float matrix[16], const int width, const int height)
{
	Vec4 clipCoords;

	clipCoords.x = matrix[0] * pos.x + matrix[4] * pos.y + matrix[8] * pos.z + matrix[12];
	clipCoords.y = matrix[1] * pos.x + matrix[5] * pos.y + matrix[9] * pos.z + matrix[13];
	clipCoords.z = matrix[2] * pos.x + matrix[6] * pos.y + matrix[10] * pos.z + matrix[14];
	clipCoords.w = matrix[3] * pos.x + matrix[7] * pos.y + matrix[11] * pos.z + matrix[15];

	// if it's inside or behind you
	if (clipCoords.w < 0.1f)
	{
		return false;
	}

	Vec3 NDC;
	NDC.x = clipCoords.x / clipCoords.w;
	NDC.y = clipCoords.y / clipCoords.w;
	NDC.z = clipCoords.z / clipCoords.w;

	// modify the screen cordinates passed by reference
	screen.x = (width / 2 * NDC.x) + (NDC.x + width / 2);
	screen.y = -(height / 2 * NDC.y) + (NDC.y + height / 2);

	return true;
}