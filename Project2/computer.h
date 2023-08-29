#include "utility.h"

#pragma once


class Computer{
public:
	//changing the scale means changing some values in ant.cpp for ant killing us or noticing us//
	const float s = 15;   // scale
	const float ground_y = -2;
	//angle to rotate GPU fan
	float angle = 0.0;


	// images
	int SKYBOX_UP, SKYBOX_SIDES, SKYBOX_DOWN;
	int BLACK, RAM, GPU_FAN, GPU_SIDE;
	int CPU_FRONT, CPU_SIDES, CPU_DOWN, CPU_INSIDE, CPU_INSIDE_SIDE, CPU_CIRCUIT;
	int box, green, grey, GPU, SSD, SSD1, SSD2, SSD3, SSD4, SSD6;
	
	//fan related variables
	Model_3DS fan;
	GLTexture blades, center;


	//functions
	void Draw_ground(float x, float y, float z, float width, float height, float length){
		x = x - width / 2;
		z = z - length / 2;
		//glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, SKYBOX_DOWN);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z + length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y, z + length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y, z);
		glEnd();
		//glDisable(GL_TEXTURE_2D);
	}

	void Draw_Skybox(float x, float y, float z, float width, float height, float length)
	{
		// Center the Skybox around the given x,y,z position
		x = x - width / 2;
		y = y - height / 2;
		z = z - length / 2;
		//glEnable(GL_TEXTURE_2D);

		// Draw Front side
		glBindTexture(GL_TEXTURE_2D, SKYBOX_SIDES);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z + length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z + length);
		glEnd();

		// Draw Back side
		glBindTexture(GL_TEXTURE_2D, SKYBOX_SIDES);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
		glEnd();

		// Draw Left side
		glBindTexture(GL_TEXTURE_2D, SKYBOX_SIDES);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z + length);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z + length);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);
		glEnd();

		// Draw Right side
		glBindTexture(GL_TEXTURE_2D, SKYBOX_SIDES);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z + length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
		glEnd();

		// Draw Up side
		glBindTexture(GL_TEXTURE_2D, SKYBOX_UP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y + height, z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y + height, z + length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
		glEnd();

		// Draw Down side
		/*glBindTexture(GL_TEXTURE_2D, SKYBOX);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z + length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y, z + length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y, z);
		glEnd();*/

		glColor3f(1, 1, 1);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		//glDisable(GL_TEXTURE_2D);
	}

	void Draw_RAM(float x, float y, float z){
		for (int i = 0; i < 3; i++){
			Draw_Building(x + (2 * i*s), ground_y, z, 0.1*s, 1 * s, 12 * s, BLACK, BLACK, RAM, RAM, BLACK, BLACK, true, true, true, true, true, true);
		}
	}

	void Draw_GPU(){
		glPushMatrix();
		glTranslated(-11.4*s, 1.4*s, 4 * s);
		glRotated(angle, 0, 0,1);
		Draw_Fan_GPU();
		angle += 0.5;
		glPopMatrix();
		//cout << angle << "\n";
		//Draw_Building(-13 * s + 0.1, ground_y + 0.1, 2 * s, 10 * s, 3 * s, 4 * s,BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, true, true, true, true, true, true);
		//fan frame
		//left
		Draw_Building(-13 * s + 0.1, ground_y + 0.1, 4 * s, 0.3 * s, 3 * s, 6 * s, GPU_SIDE, GPU_SIDE, GPU_SIDE, GPU_SIDE, GPU_SIDE, GPU_SIDE, true, true, true, true, true, true);
		//up
		Draw_Building(-13 * s + 0.1, ground_y + 0.1 + (3 * s), 4 * s, 10 * s, 0.3 * s, 6 * s, GPU_SIDE, GPU_SIDE, GPU_SIDE, GPU_SIDE, GPU_SIDE, GPU_SIDE, true, true, true, true, true, true);
		//right
		Draw_Building(-10 * s + 0.1, ground_y + 0.1, 4 * s, 0.3 * s, 3 * s, 6 * s, GPU_SIDE, GPU_SIDE, GPU_SIDE, GPU_SIDE, GPU_SIDE, GPU_SIDE, true, true, true, true, true, true);
		//down
		Draw_Building(-13 * s + 0.1, ground_y + 0.1, 4 * s, 3.2 * s, 0.3 * s, 6 * s, GPU_SIDE, GPU_SIDE, GPU_SIDE, GPU_SIDE, GPU_SIDE, GPU_SIDE, true, true, true, true, true, true);

		//
		//1
		Draw_Building(-9 * s + 0.1, ground_y + 0.1, 2 * s, 1 * s, 0.2 *s, 2 * s, CPU_CIRCUIT, CPU_CIRCUIT, CPU_CIRCUIT, CPU_CIRCUIT, CPU_CIRCUIT, CPU_CIRCUIT, true, true, true, true, true, true);
		//2
		Draw_Building(-6 * s + 0.1, ground_y + 0.1, 3 * s, 0.5 * s, 0.2 *s, 2 * s, CPU_CIRCUIT, CPU_CIRCUIT, CPU_CIRCUIT, CPU_CIRCUIT, CPU_CIRCUIT, CPU_CIRCUIT, true, true, true, true, true, true);
		//3
		Draw_Building(-4 * s + 0.1, ground_y + 0.1, 4 * s, 1 * s, 3 * s, 2 * s, GPU_SIDE, GPU_SIDE, GPU_SIDE, GPU_SIDE, GPU_SIDE, GPU_SIDE, true, true, true, true, true, true);
		//4
		Draw_Building(-4 * s + 0.1, ground_y + 0.1, 0 * s, 1 * s, 3 * s, 2 * s, GPU_SIDE, GPU_SIDE, GPU_SIDE, GPU_SIDE, GPU_SIDE, GPU_SIDE, true, true, true, true, true, true);

	}

	void Draw_CPU(float x, float y, float z, float width, float height, float length){
		//main building
		Draw_Building(x, y, z, width, height, length, CPU_DOWN, CPU_DOWN, CPU_SIDES, CPU_SIDES, CPU_FRONT, CPU_FRONT, true, true, false, true, true, true);
		Draw_Building(x, y + 0.1, z - 0.6, width - 1.2, height - 0.6, length - 1.2, CPU_INSIDE, CPU_DOWN, CPU_INSIDE, CPU_INSIDE, CPU_INSIDE, CPU_INSIDE, true, true, false, true, true, true);
		glDisable(GL_TEXTURE_2D);
		glColor3ub(43, 60, 58);
		glBegin(GL_QUADS);
		glVertex3f(x, y, z);
		glVertex3f(x, y + height, z);
		glVertex3f(x, y + height, z - 0.6);
		glVertex3f(x, y, z - 0.6);
		glVertex3f(x, y, z - (8 * s) + 0.6);
		glVertex3f(x, y + height, z - (8 * s) + 0.6);
		glVertex3f(x, y + height, z - (8 * s));
		glVertex3f(x, y, z - (8 * s));
		glEnd();
		glColor3f(1, 1, 1);
		glEnable(GL_TEXTURE_2D);
		//cpu
		Draw_Building(x + (2.5*s), y, z - (3 * s), width - (5 * s), height - (2.3*s), length - (6 * s), CPU_FRONT, BLACK, CPU_INSIDE_SIDE, CPU_INSIDE_SIDE, CPU_INSIDE_SIDE, CPU_INSIDE_SIDE, true, true, true, true, true, true);

		glPushMatrix();
		glColor3ub(207, 169, 64);
		glTranslated(x + (4.5*s) - 0.2, -2.4, z - (3.3*s));
		drawSphere(2, 10, 10, 4);
		for (int i = 0; i < 14; i++)
			glTranslated(0, 0, -1), drawSphere(2, 10, 10, 4);
		glColor3d(1, 1, 1);
		glPopMatrix();

		glPushMatrix();
		glColor3ub(207, 169, 64);
		glTranslated(x + (4.2 * s), -2.4, z - (5 * s) + 0.2);
		glRotatef(90, 0, 1, 0);
		drawSphere(2, 10, 10, 4);
		for (int i = 0; i < 14; i++)
			glTranslated(0, 0, -1), drawSphere(2, 10, 10, 4);
		glColor3d(1, 1, 1);
		glPopMatrix();

		glPushMatrix();
		glColor3ub(207, 169, 64);
		glTranslated(x + (2.8 * s) - 0.2, -2.4, z - (3 * s) - 0.2);
		glRotatef(-90, 0, 1, 0);
		drawSphere(2, 10, 10, 4);
		for (int i = 0; i < 14; i++)
			glTranslated(0, 0, -1), drawSphere(2, 10, 10, 4);
		glColor3d(1, 1, 1);
		glPopMatrix();

		glPushMatrix();
		glColor3ub(207, 169, 64);
		glTranslated(x + (2.5*s) + 0.2, -2.4, z - (4.7*s));
		glRotatef(-180, 0, 1, 0);
		drawSphere(2, 10, 10, 4);
		for (int i = 0; i < 14; i++)
			glTranslated(0, 0, -1), drawSphere(2, 10, 10, 4);
		glColor3d(1, 1, 1);
		glPopMatrix();


		//circuit
		glPushMatrix();
		glTranslatef(x + (0.75 * s), y, z - (7.25 * s));
		glRotatef(-90, 1, 0, 0);
		draw_cylender(2, height - (1.5*s), 43, 60, 58);
		glRotatef(90, 1, 0, 0);
		glTranslated(0, 1.4 * s, 0);
		drawSphere(2, 10, 10, 1);
		glTranslatef(0, -1.4 * s, 0);
		glTranslatef(0, 0, 6.5*s);
		glRotatef(-90, 1, 0, 0);
		draw_cylender(2, height - (1.5*s), 43, 60, 58);
		glRotatef(90, 1, 0, 0);
		glTranslated(0, 1.4 * s, 0);
		drawSphere(2, 10, 10, 1);
		glTranslatef(0, -1.4 * s, 0);
		glTranslatef(5.5*s, 0, 0);
		glRotatef(-90, 1, 0, 0);
		draw_cylender(2, height - (1.5*s), 43, 60, 58);
		glRotatef(90, 1, 0, 0);
		glTranslated(0, 1.4 * s, 0);
		drawSphere(2, 10, 10, 1);
		glTranslatef(0, -1.4 * s, 0);
		glTranslatef(0, 0, -6.5*s);
		glRotatef(-90, 1, 0, 0);
		draw_cylender(2, height - (1.5*s), 43, 60, 58);
		glRotatef(90, 1, 0, 0);
		glTranslated(0, 1.4 * s, 0);
		drawSphere(2, 10, 10, 1);
		glTranslatef(0, -1.4 * s, 0);
		glPopMatrix();

		Draw_Building(x + (2.5*s), y, z - (6.5 * s), width - (5 * s), height - (2.33*s), length - (7.5*s), CPU_CIRCUIT, CPU_CIRCUIT, CPU_CIRCUIT, CPU_CIRCUIT, CPU_CIRCUIT, CPU_CIRCUIT, true, true, true, true, true, true);
		Draw_Building(x + (2.5*s), y, z - (1 * s), width - (5 * s), height - (2.33*s), length - (7.5*s), CPU_CIRCUIT, CPU_CIRCUIT, CPU_CIRCUIT, CPU_CIRCUIT, CPU_CIRCUIT, CPU_CIRCUIT, true, true, true, true, true, true);

		Draw_Building(x + (1 * s), y, z - (2.5 * s), width - (6.5*s), height - (2.33*s), length - (7.5*s), CPU_CIRCUIT, CPU_CIRCUIT, CPU_CIRCUIT, CPU_CIRCUIT, CPU_CIRCUIT, CPU_CIRCUIT, true, true, true, true, true, true);
		Draw_Building(x + (1 * s), y, z - (4 * s), width - (6.5*s), height - (2.33*s), length - (7.5*s), CPU_CIRCUIT, CPU_CIRCUIT, CPU_CIRCUIT, CPU_CIRCUIT, CPU_CIRCUIT, CPU_CIRCUIT, true, true, true, true, true, true);
		Draw_Building(x + (1 * s), y, z - (5.5 * s), width - (6.5*s), height - (2.33*s), length - (7.5*s), CPU_CIRCUIT, CPU_CIRCUIT, CPU_CIRCUIT, CPU_CIRCUIT, CPU_CIRCUIT, CPU_CIRCUIT, true, true, true, true, true, true);

		Draw_Building(x + (5.5 * s), y, z - (2.5 * s), width - (6.5*s), height - (2.33*s), length - (7.5*s), CPU_CIRCUIT, CPU_CIRCUIT, CPU_CIRCUIT, CPU_CIRCUIT, CPU_CIRCUIT, CPU_CIRCUIT, true, true, true, true, true, true);
		Draw_Building(x + (5.5 * s), y, z - (4 * s), width - (6.5*s), height - (2.33*s), length - (7.5*s), CPU_CIRCUIT, CPU_CIRCUIT, CPU_CIRCUIT, CPU_CIRCUIT, CPU_CIRCUIT, CPU_CIRCUIT, true, true, true, true, true, true);
		Draw_Building(x + (5.5 * s), y, z - (5.5 * s), width - (6.5*s), height - (2.33*s), length - (7.5*s), CPU_CIRCUIT, CPU_CIRCUIT, CPU_CIRCUIT, CPU_CIRCUIT, CPU_CIRCUIT, CPU_CIRCUIT, true, true, true, true, true, true);

		// glass and door
		/*Draw_Glass(x , y , z , width , height - (1.5*s) , length- (4.5*s) , false , true , false , false , false);
		Draw_Glass(x, y, z - (4.5*s), width, height - (1.5*s), length - (4.5*s), false, true, false, false, false);
		Draw_Glass(x, y+(1*s), z, width, height - (1*s), length, false, true, false, false, false);*/
	}
	void Draw_Fan_GPU()
	{
		for (float i = 0.0; i < 360.0; i += 30.0)
		{
			glPushMatrix();
			glRotated(i, 0, 0, 1);
			Draw_Building(0 * s + 0.1, 0 + 0.1, 0 * s, 0.1 * s, 1 * s, 5.9 * s, GPU_FAN, GPU_FAN, GPU_FAN, GPU_FAN, GPU_FAN, GPU_FAN, true, true, true, true, true, true);
			glPopMatrix();
		}
	}
	void Draw_Fan(){
		glPushMatrix();
		glTranslated(0 * s, (12) * s, 0 * s);
		//glRotated(90, -9 * s, 8 * s, 6 * s);
		glRotated(90, 0, 0, 1);
		glRotated(180, 1, 0, 0);
		fan.rot.x += 4;
		fan.Draw();
		glPopMatrix();
	}

	void drow_SSD(float x, float y, float z, float width, float height, float length, float i){

		//  draw ship
		Draw_Building(x * s, ground_y + y, z * s,
			width * s, height * s, length* s,
			SSD, BLACK, green, green, green, green, 1, 1, 1, 1, 1, 1);

		//draw quad  1
		Draw_Building((1.5 - i)* s, ground_y + 0.8, -5.95 * s,
			1.15 * s, 0.09 * s, 0.9 * s,
			SSD1, BLACK, grey, grey, grey, grey, 1, 1, 1, 1, 1, 1);


		//draw quad  2
		glPushMatrix();
		Draw_Building((2.024 - i) * s, ground_y + 0.8, -7.35 * s,
			0.69* s, 0.09 * s, 0.955 * s,
			SSD2, grey, grey, grey, grey, grey, 1, 1, 1, 1, 1, 1);
		glPopMatrix();

		//draw quad  3
		glPushMatrix();
		Draw_Building((1.23 - i) * s, ground_y + 0.8, -8.54 * s,
			1.63* s, 0.09 * s, 0.87 * s,
			SSD3, grey, grey, grey, grey, grey, 1, 1, 1, 1, 1, 1);
		glPopMatrix();

		//draw quad  4
		glPushMatrix();
		Draw_Building((1.23 - i) * s, ground_y + 0.8, -9.62 * s,
			1.63* s, 0.09 * s, 0.87 * s,
			SSD3, grey, grey, grey, grey, grey, 1, 1, 1, 1, 1, 1);
		glPopMatrix();

		//draw quad  5
		glPushMatrix();
		Draw_Building((1.415 - i) * s, ground_y + 0.8, -5.4 * s,
			0.18* s, 0.09 * s, 0.15 * s,
			SSD3, grey, grey, grey, grey, grey, 1, 1, 1,1 ,1 ,1 );
		glPopMatrix();

		//draw quad  6
		glPushMatrix();
		Draw_Building((1.703 - i) * s, ground_y + 0.8, -5.35 * s,
			0.18* s, 0.05 * s, 0.15 * s,
			SSD4, SSD4, SSD4, SSD4, SSD4, SSD4, 1, 1, 1,1 ,1 ,1);
		glPopMatrix();



	}

	void Draw_Storage(){
		/*Draw_Building(-12 * s, ground_y +0.1 , -4 * s,
		16 * s, 5 * s, 8 * s,
		box, SKYBOX, box, box, box, box);*/

		/////      DRAW  ssd    

		drow_SSD(-11, 0.3, -5, 2, 0.09, 6, 12);


		drow_SSD(-7, 0.3, -5, 2, 0.09, 6, 8);

		drow_SSD(-3, 0.3, -5, 2, 0.09, 6, 4);

		drow_SSD(1, 0.3, -5, 2, 0.09, 6, 0);
	}

};