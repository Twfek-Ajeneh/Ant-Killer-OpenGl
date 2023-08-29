#include <windows.h>		// Header File For Windows
#include <gl/GL.h>				// Header File For The OpenGL32 Library
#include <gl/glu.h>	
#include <fstream>
#include <math.h>

#include "bullet.h"

#include <stdlib.h>   /* for exit */
#include <set>

using namespace std;

Bullet::Bullet(){
	
}

Bullet::Bullet(float pX, float pY, float pZ, float lX, float lY, float lZ,float r,float step_speed){
	posX = pX;
	posY = pY;
	posZ = pZ;
	lookX = lX;
	lookY = lY;
	lookZ = lZ;
	R = r;
	speed = step_speed;
}

void Bullet::setCurrentCoordinates(){
	X = posX + (step * lookX);
	Y = posY + (step * lookY);
	Z = posZ + (step * lookZ);
	step += speed;
}

void Bullet::draw_X(float s){
	glDisable(GL_TEXTURE_2D);
	float length = 0.003*s;
	float x = 0, y = 0, z = -3;
	glLineWidth(0.1*s);
	glBegin(GL_LINES);
	glColor3f(0.8, 0, 0);
	glVertex3f(x, y + length, z);
	glVertex3f(x, y - length, z);
	glVertex3f(x + length, y, z);
	glVertex3f(x - length, y, z);
	//„«Ì·…
	/*glVertex3f(x - length, y - length, z);
	glVertex3f(x + length, y + length, z);
	glVertex3f(x + length, y - length, z);
	glVertex3f(x - length, y + length, z);*/
	glEnd();

}


void Bullet::drawSphere(float r, int lats, int longs) {
	float M_PI = 3.14;
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
}

void Bullet::draw(){
	glDisable(GL_TEXTURE_2D);
	glPushMatrix();
	this->setCurrentCoordinates();
	glTranslatef(X, Y, Z);
	glColor3b(1, 1, 1);
	this->drawSphere(R, 20, 20);
	glPopMatrix();
}


float Bullet::get_posX(){
	return X;
}

float Bullet::get_posY(){
	return Y;
}

float Bullet::get_posZ(){
	return Z;
}
