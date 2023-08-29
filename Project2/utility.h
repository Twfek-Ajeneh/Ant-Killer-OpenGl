#pragma once
#include <windows.h>		// Header File For Windows
#include<string>
#include <gl.h>			// Header File For The OpenGL32 Library
#include <glu.h>			// Header File For The GLu32 Library
#include <glaux.h>		// Header File For The Glaux Library
#include<texture.h>
#include "heightMap.h"
#include "Model_3DS.h"
#include "3DTexture.h"
#include "camera.h"
#include "TgaLoader.h"
#include "ant.h"
#include "bullet.h"
//#include "Sound.h"
#include <set>
#include<vector>


void drawUnitCube() {

	glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	//Front Face
	glNormal3f(0, 0, 1);
	glVertex3f(-0.5, -0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);

	//Back Face
	glNormal3f(0, 0, -1);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);

	//Right Face
	glNormal3f(1, 0, 0);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(0.5, -0.5, 0.5);

	//Left Face
	glNormal3f(-1, 0, 0);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(-0.5, 0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);

	//Top Face
	glNormal3f(0, 1, 0);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, 0.5);
	glVertex3f(-0.5, 0.5, 0.5);

	//Bottom Face
	glNormal3f(0, -1, 0);
	glVertex3f(-0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(0.5, -0.5, 0.5);
	glVertex3f(-0.5, -0.5, 0.5);

	glEnd();
}
void drawMyCube(float xPos, float yPos, float zPos,
	float xSize, float ySize, float zSize,
	float xRot, float yRot, float zRot) {

	glPushMatrix();

	glTranslatef(xPos, yPos, zPos);
	glRotatef(xRot, 1, 0, 0);
	glRotatef(yRot, 0, 1, 0);
	glRotatef(zRot, 0, 0, 1);
	glScalef(xSize, ySize, zSize);
	drawUnitCube();

	glPopMatrix();

}

void drawSphere(double r, int lats, int longs , int p) {
	glDisable(GL_TEXTURE_2D);
	float M_PI = 3.14/p;
	int i, j;
	for (i = 0; i <= lats; i++) {
		double lat0 = M_PI * (-0.5 + (double)(i - 1) / lats);
		double z0 = sin(lat0);
		double zr0 = cos(lat0);

		double lat1 = M_PI * (-0.5 + (double)i / lats);
		double z1 = sin(lat1);
		double zr1 = cos(lat1);
		glBegin(GL_QUAD_STRIP);
		for (j = 0; j <= longs; j++) {
			double lng = 2 * M_PI * (double)(j - 1) / longs;
			double x = cos(lng);
			double y = sin(lng);

			glNormal3f(x * zr0, y * zr0, z0);
			glVertex3f(r * x * zr0, r * y * zr0, r * z0);
			glNormal3f(x * zr1, y * zr1, z1);
			glVertex3f(r * x * zr1, r * y * zr1, r * z1);
		}
		glEnd();
	}
	glEnable(GL_TEXTURE_2D);
}
void Draw_Building(float x, float y, float z, float width, float height, float length, int UP, int DOWN, int LEFT, int RIGHT, int FRONT, int BACK
	, bool FUP, bool FDOWN, bool FLEFT, bool FRIGHT, bool FFRONT, bool FBACK){
	//glEnable(GL_TEXTURE_2D);

	// Draw Front side
	if (FFRONT){
		glBindTexture(GL_TEXTURE_2D, FRONT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z - length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z - length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z - length);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z - length);
		glEnd();
	}

	// Draw Back side
	if (FBACK){
		glBindTexture(GL_TEXTURE_2D, BACK);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
		glEnd();
	}

	// Draw Left side
	if (FLEFT){
		glBindTexture(GL_TEXTURE_2D, LEFT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z - length);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z - length);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);
		glEnd();
	}

	// Draw Right side
	if (FRIGHT){
		glBindTexture(GL_TEXTURE_2D, RIGHT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z - length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z - length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
		glEnd();
	}

	// Draw Up side
	if (FUP){
		glBindTexture(GL_TEXTURE_2D, UP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y + height, z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y + height, z - length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z - length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
		glEnd();
	}

	// Draw Down side
	if (FDOWN){
		glBindTexture(GL_TEXTURE_2D, DOWN);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z - length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y, z - length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y, z);
		glEnd();
	}
	//glDisable(GL_TEXTURE_2D);
}
void output(float x, float y, float z, const char *string)
{
	glDisable(GL_TEXTURE_2D);
	glColor3f(1, 1, 1);
	glRasterPos3f(x, y, z);
	int len, i;
	len = (int)strlen(string);
	for (i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
	}
}

void Draw_Glass(float x, float y, float z, float width, float height, float length, bool up , bool left, bool right, bool front, bool back){
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4d(1, 1, 1, 0.3);
	//Front
	if (front){
		glBegin(GL_QUADS);
		glVertex3f(x, y, z - length);
		glVertex3f(x, y + height, z - length);
		glVertex3f(x + width, y + height, z - length);
		glVertex3f(x + width, y, z - length);
		glEnd();
	}
	//Back
	if (back){
		glBegin(GL_QUADS);
		glVertex3f(x + width, y, z);
		glVertex3f(x + width, y + height, z);
		glVertex3f(x, y + height, z);
		glVertex3f(x, y, z);
		glEnd();
	}
	//Left
	if (left){
		glBegin(GL_QUADS);
		glVertex3f(x, y + height, z);
		glVertex3f(x, y + height, z - length);
		glVertex3f(x, y, z - length);
		glVertex3f(x, y, z);
		glEnd();
	}
	//Right
	if (right){
		glBegin(GL_QUADS);
		glVertex3f(x + width, y, z);
		glVertex3f(x + width, y, z - length);
		glVertex3f(x + width, y + height, z - length);
		glVertex3f(x + width, y + height, z);
		glEnd();
	}
	//Up
	if (up){
		glBegin(GL_QUADS);
		glVertex3f(x + width, y + height, z);
		glVertex3f(x + width, y + height, z - length);
		glVertex3f(x, y + height, z - length);
		glVertex3f(x, y + height, z);
		glEnd();
	}
	glDisable(GL_BLEND);
	glColor3d(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
}




void Draw_Building2(float x, float y, float z, float width, float height, float length, float r, float g, float b){
	glDisable(GL_TEXTURE_2D);

	// Draw Front side
	//glBindTexture(GL_TEXTURE_2D, FRONT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
	glColor3f(r, g, b);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z - length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z - length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z - length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z - length);
	glEnd();

	// Draw Back side
	//glBindTexture(GL_TEXTURE_2D, BACK);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
	glEnd();

	// Draw Left side
	//glBindTexture(GL_TEXTURE_2D, LEFT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z - length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z - length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);
	glEnd();

	// Draw Right side
	//glBindTexture(GL_TEXTURE_2D, RIGHT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z - length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z - length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glEnd();

	// Draw Up side
	//glBindTexture(GL_TEXTURE_2D, UP);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y + height, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y + height, z - length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z - length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
	glEnd();

	// Draw Down side
	//glBindTexture(GL_TEXTURE_2D, DOWN);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z - length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y, z - length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y, z);
	glEnd();
	//glDisable(GL_TEXTURE_2D);
}

void circle(float r, float temp, float R, float g, float b){
	glColor3f(R, g, b);
	glBegin(GL_POLYGON);
	for (float angle = 0.0f; angle <= (2.0f*3.14f)*r; angle += 0.2f){
		float x = r*cos(angle);
		float y = r*sin(angle);
		glVertex3f(x, y, temp);
	}
	glEnd();
}

void draw_cylender(float r, float depth, float R, float g, float b){
	glDisable(GL_TEXTURE_2D);
	glColor3ub(R, g, b);
	glBegin(GL_POLYGON);
	for (float angle = 0.0f; angle <= (2.0f*3.14f)*r; angle += 0.2f){
		float x = r*cos(angle);
		float y = r*sin(angle);
		glVertex3f(x, y, 0);
	}
	glEnd();
	glBegin(GL_POLYGON);
	for (float angle = 0.0f; angle <= (2.0f*3.14f)*r; angle += 0.2f){
		float x = r*cos(angle);
		float y = r*sin(angle);
		glVertex3f(x, y, depth);
	}
	glEnd();
	for (float angle = 0.0f; angle <= (2.0f*3.14f)*r; angle += 0.1f){
		float x = r*cos(angle);
		float y = r*sin(angle);
		float next_x = r*cos(angle + 0.1);
		float next_y = r*sin(angle + 0.1);
		glBegin(GL_QUADS);
		//glColor3b(r, g, b);
		glVertex3f(x, y, 0);
		glVertex3f(next_x, next_y, 0);
		glVertex3f(next_x, next_y, depth);
		glVertex3f(x, y, depth);
		glEnd();
	}
	glColor3f(1, 1, 1);
	glEnable(GL_TEXTURE_2D);
}