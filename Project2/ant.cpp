#pragma once
#include <windows.h>		// Header File For Windows
#include <gl/GL.h>				// Header File For The OpenGL32 Library
#include <gl/glu.h>	
#include <math.h>
#include <cmath>
#include<set>

#include "ant.h"

#include <stdlib.h>   /* for exit */
#include <iostream> 
using namespace std;

#define SQR(x) (x*x)

const float transfer = (180.0 / 3.141592653589793238463);

Ant::Ant(){
}

Ant::Ant(GLfloat x, GLfloat y, GLfloat z,float rotate,  GLTexture texture, char* path,int strength){
	ant = Model_3DS();
	ant.Load(path);
	ant.pos.x = 0;
	ant.pos.y = 0;
	ant.pos.z = 0;
	ant.scale = 0.05; //0.025
	ant_strength = strength;
	ant_texture = texture;
	rotation_angle = rotate;
	posX = x;
	posY = y;
	posZ = z;
}



void Ant::draw(){
	ant.Materials[0].tex = ant_texture;
	glPushMatrix();
	glTranslated(posX, posY, posZ);
	glRotated(rotation_angle, 0, 1, 0);
	ant.Draw();
	glPopMatrix();
}

float set_rotation_angle_for_camera(float lX, float lZ){
	float length = (sqrt(SQR(lX) + SQR(lZ)));
	lX = lX / length;
	lZ = (lZ / length)*-1;
	float angle = atan2(lZ, lX);
	float rotation_angle = (angle * transfer) + 270;
	return rotation_angle;
}

pair<float, float> Ant::getAntNextStep(float lX, float lY, float lZ, float scale, float speed, int &health, bool &immune){
	float distance = sqrt(SQR((posX - lX)) + SQR((posZ - lZ)));
	if (distance > 4*scale){                         // ant is far away
		return {posX, posZ};
	}
	if (distance > 3 * scale){
		rotation_angle = set_rotation_angle_for_camera(lX - posX, lZ - posZ);
		return{ posX, posZ };
	}
	if (abs(lX - posX) <= 2 && abs(lZ - posZ) <= 0.2*scale){    // ant reached my pos
		if(health <= 0)
		{
			std::cout << "GAME OVER!";
			Sleep(1000);
			exit(0);
		}
		else if (!immune)
		{
			health -= ant_strength;
			immune = true;
			//cout << health << endl;
		}
	}

	// make ant pos (0,0) and camera pos relevant to it
	lX -= posX;
	lZ -= posZ;
	float addX = (speed)*lX;
	float addZ = (speed)*lZ; 
	float newX = posX + addX;
	float newZ = posZ + addZ;

	rotation_angle = set_rotation_angle_for_camera(lX, lZ);

	return { newX, newZ };
}


void Ant::assignPosition(float x, float z){
	posX = x;
	posZ = z;
}

int Ant::set_Strength(float posX,float posZ)
{	
	//cpu
	if (4  <= posX && posX <= 11 && 5 <= posZ  && posZ <= 13)
		return 15;
	//ram
	else if (6 <= posX && posX <= 12 && -12 <= posZ && posZ <= 2)
		return 20;
	//ssd
	else if (-12 <= posX && posX <= 4 && -12 <= posZ && posZ <= -4)
		return 30;
	//gpu
	else if (-13 <= posX && posX <= -3 && -2 <= posZ && posZ <= 4)
		return 25;
	//hdd
	else if (-13 <= posX && posX <= -3 && 7 <= posZ && posZ <= 13)
		return 35;
	else
		return 10;
}

float Ant::get_posX(){
	return posX;
}

float Ant::get_posY(){
	return posY;
}

float Ant::get_posZ(){
	return posZ;
}