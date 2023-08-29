#include "camera.h"
#include "computer.h"
#include <math.h>
#include<iostream>

using namespace std;


//camera
Camera MyCamera;


//when changing speed change rspeed and yspeed;

//camera related variables: 
/*const double pi = 3.14, r = 5, rspeed = 0.021, y_speed = 0.06;
double lX, lY, lZ = (-1 * r);
double angle_h = -1.57, max = (pi * 2);*/

/*void ThirdPersonCamera(float lookX, float lookY, float lookZ){
	MyCamera.Position.y = 2.5;
	glColor3b(1, 1, 1);
	drawMyCube(lookX, lookY, lookZ, 1, 1, 1, 0, 0, 0);
}*/


void FirstPersonCamera(bool* keys, float speed, int scale){
	if (keys['S']){
		//lY -= y_speed;
		MyCamera.RotateX(-2 * speed);
	}
	if (keys['W']){
		//lY += y_speed;
		MyCamera.RotateX(2 * speed);
	}
	if (keys['D']){
		//lY = 0;

		/*angle_h += rspeed;
		if (angle_h > max) angle_h -= max;
		lX = cos(angle_h)*r;
		lZ = sin(angle_h)*r;
		*/

		MyCamera.RotateY(-2 * speed);
	}
	if (keys['A'] ){
		//lY = 0;

		/*angle_h -= rspeed;
		if (angle_h < 0) angle_h += max;
		lX = cos(angle_h)*r;
		lZ = sin(angle_h)*r;
		*/

		MyCamera.RotateY(2 * speed);
	}
	if (keys[VK_UP]){
		MyCamera.MoveForward(1 * speed, scale);
	}
	if (keys[VK_DOWN]){
		MyCamera.MoveForward(-1 * speed, scale);
	}
	if (keys[VK_RIGHT]){
		MyCamera.MoveRight(1 * speed, scale);
	}
	if (keys[VK_LEFT]){
		MyCamera.MoveRight(-1 * speed, scale);
	}
}