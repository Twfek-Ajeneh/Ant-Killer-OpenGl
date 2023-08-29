//***************************************************************************
//  BULLET 
//***************************************************************************
#pragma once

#include <glut.h>		
#include "ant.h"
#include <set>

class Bullet
{
public:
	float step = 6, speed;
	float lookX, lookY, lookZ;
	float posX, posY, posZ;
	float X, Y, Z;
	float R;

public:
	Bullet();
	Bullet(float pX, float pY, float pZ, float lX, float lY, float lZ, float r, float step_speed);
	void setCurrentCoordinates();
	void draw(); // draw bullet 
	float get_posX();
	float get_posY();
	float get_posZ();
	static void draw_X(float s);
private:
	void drawSphere(float r, int lats, int longs);
};


