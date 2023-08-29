#include "utility.h"
#include "computer.h"
#include "camera_functions.h"
#include "grid.h"
#include <time.h>
#include "ant.h"

using namespace std;

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glut32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"GLAUX.LIB")

//Project --> property --> c/c++ --> preprocessor --> preprocessor definitions --> _CRT_SECURE_NO_WARNINGS
//Project --> property --> c/c++ --> preprocessor --> preprocessor definitions -->  _CRT_NONSTDC_NO_DEPRECATE


HDC			hDC = NULL;		// Private GDI Device Context
HGLRC		hRC = NULL;		// Permanent Rendering Context
HWND		hWnd = NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application

bool	keys[256];			// Array Used For The Keyboard Routine
bool	active = TRUE;		// Window Active Flag Set To TRUE By Default
bool	fullscreen = FALSE;	// Fullscreen Flag Set To Fullscreen Mode By Default

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height == 0)										// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}

	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 1000.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

// ===============================================================================================================
//computer
Computer MyComputer;
const float s = MyComputer.s;
const int ground_y = MyComputer.ground_y;

// ant declerations
set<Ant*> ants;
GLTexture ant_texture;
float ant_speed = 0;
const float ant_speed_increase = 0.0025;
const int ant_count = 35;
int ants_left = ant_count;
float ant_y = ground_y + 1;
const float ant_pos[ant_count][4] = {
	{ 6, ant_y, 9.25, 90 }, { 7.5, ant_y, 7, 90 }, { 9.5, ant_y, 6.5, 180 }, { 8.25, ant_y, 10.5, 0 }, { 9.5, ant_y, 10.75, 90 }, { 7.25, ant_y, 11, 90 }, { 5.25, ant_y, 12.25, 0 }, //CPU
	{ 8, ant_y, -7, 180 }, { 7, ant_y, -11.4, 270 }, { 8.2, ant_y, -3, 0 }, { 6.75, ant_y, -1, 0 }, { 10, ant_y, -1, 180 }, { 9.6, ant_y, -6, 180 }, { 10.4, ant_y, -10, 180 },//RAM
	{ 3.5, ant_y, -6, 180 }, { 0.5, ant_y, -10.25, 180 }, { -4, ant_y, -7, 180 }, { -5.5, ant_y, -11.5, 270 }, { -7.5, ant_y, -4.5, 180 }, { -8.5, ant_y, -9, 180 }, { -11, ant_y, -11.5, 270 }, //SSD
	{ -4, ant_y, 1, 270 }, { -5, ant_y, 3, 0 }, { -6, ant_y, -1.5, 180 }, { -7, ant_y, 0.25, 270 }, { -7.5, ant_y, 2, 0 }, { -9, ant_y, 3, 270 }, { -9.5, ant_y , -1, 270}, //GPU
	{ -3.25, ant_y, 12, 0 }, { -4, ant_y, 8, 180 }, { -9, ant_y, 8, 270 }, { -10, ant_y, 10, 315 }, { -10, ant_y, 12, 315 }, { -11, ant_y, 12, 270 }, { -11.5, ant_y , 7.5, 270}, //HDD
};

//bullet
set<Bullet*> bullets;
const float kill_range = 1;
time_t shootBulletStartTime = time(0);

//health and immunity
bool immune = false,start = true;
int health = 100,lasthealth=0;
int immunetime = 0;
//camera related
bool firstPerson = true;
time_t cameraSwitchStartTime = time(0);


//SOUND
//Sound sound1;
//Sound shootingSound;

/*bool shootingSoundIsPlaying = false;
time_t shootingSoundStartTime;

INIT initialize = INIT(); // Sound Initialize
Sound shootingSound;
Sound sound2;*/

//===================================================================================================================================

int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.50f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

	// set initial camera location
	MyCamera.Position.x = 1*s;
	MyCamera.Position.z = (12.4)*s;

	// skybox
	MyComputer.SKYBOX_UP = LoadTexture("data/skybox/up2.bmp", 255);
	MyComputer.SKYBOX_DOWN = LoadTexture("data/skybox/floor.bmp", 255);
	MyComputer.SKYBOX_SIDES = LoadTexture("data/skybox/sides.bmp", 255);

	// RAM
	MyComputer.RAM = LoadTexture("data/ram.bmp");

	//GPU
	MyComputer.GPU_FAN = LoadTexture("data/gpu_sides.bmp");
	MyComputer.GPU_SIDE = LoadTexture("data/up2.bmp");

	//CPU
	MyComputer.CPU_FRONT = LoadTexture("data/cpu_front.bmp");
	MyComputer.CPU_SIDES = LoadTexture("data/cpu_side.bmp");
	MyComputer.CPU_DOWN = LoadTexture("data/cpu_down.bmp");
	MyComputer.CPU_INSIDE = LoadTexture("data/cpu_inside.bmp");
	MyComputer.CPU_INSIDE_SIDE = LoadTexture("data/cpu_inside_side.bmp");
	MyComputer.CPU_CIRCUIT = LoadTexture("data/cpu_circuit.bmp");

	//STORAGE
	MyComputer.SSD = LoadTexture("data/SSD.bmp");
	MyComputer.SSD1 = LoadTexture("data/SSD1.bmp");
	MyComputer.SSD2 = LoadTexture("data/SSD2.bmp");
	MyComputer.SSD3 = LoadTexture("data/SSD3.bmp");
	MyComputer.SSD4 = LoadTexture("data/SSD4.bmp");

	MyComputer.green = LoadTexture("data/green.bmp");
	MyComputer.grey = LoadTexture("data/grey.bmp");
	MyComputer.box = LoadTexture("data/silver.bmp");

	// DECLARE ANTS
	Ant ant;
	ant_texture.LoadBMP("data/ant.bmp");
	for (int i = 0; i < ant_count; i++){
		int strength = ant.set_Strength(ant_pos[i][0], ant_pos[i][2]);
		//cout << strength << endl;
		ants.insert(new Ant(ant_pos[i][0] * s, ant_pos[i][1], ant_pos[i][2] * s,ant_pos[i][3] ,ant_texture, "data/ant.3ds",strength));
	}

	//fan
	MyComputer.center.LoadBMP("data/black.bmp");
	MyComputer.blades.LoadBMP("data/gpu_sides.bmp");

	MyComputer.fan.Load("data/computer_fan.3ds");
	MyComputer.fan.pos.x = 0 * s;
	MyComputer.fan.pos.y = 0 * s;
	MyComputer.fan.pos.z = 0 * s;
	MyComputer.fan.scale = 8 * s;

	MyComputer.fan.Materials[0].tex = MyComputer.blades;//blade
	MyComputer.fan.Materials[1].tex = MyComputer.center;//circle


	//INIT initalie = INIT();
	//initalie.InitOpenAL();


	//sound1 = Sound("data/fan.wav");
	//shootingSound = Sound("data/shot.wav");


	// SOUND
	//initialize.InitOpenAL(); // initialize sound from OpenAl
	//shootingSound = Sound("data/shot.wav");

	//GL_CLAMP   GL_REPEAT  
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	initialize_GRID();
	initialize_Bullet_GRID();
	/*for (int j = n - 1; j >= 0; j--){
	for (int i = n - 1; i >= 0; i--){
	cout << GRID[i][j] << " ";
	}
	cout << endl;
	}*/

	return TRUE;										// Initialization Went OK

}
/*void sound(){
	if (keys['O']){
		sound1.Play();
	}
	if (keys['R']){
		sound1.Stop();
	}
}*/

int DrawGLScene(GLvoid)									// Here's Where We Do All The Drawing
{
	//SetCursorPos(0,0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	Bullet::draw_X(s); 
	//immmuntiy
	if (immune)
	{
		immunetime++;
	}
	if (immunetime == 150)
	{
		immunetime = 0;
		immune = false;
	}
	//health printing
	if (health != lasthealth && !start)
	{
		cout << "Health: " << health << "  Health Lost: "<< lasthealth-health<<endl;
		lasthealth = health;
	}
	else if (start)
	{
		cout << "Health: " << health << endl;
		lasthealth = health;
		start = false;
	}
	//output some stuff on the screen
	string string_output = "Health: " + to_string(health);
	float output_x = 0.35, output_y = 0.35, output_z = -1;
	const char *char_output_1 = &string_output[0];
	output(0.35, 0.35, -1, char_output_1);
	string_output = "Ants left: " + to_string(ants_left);
	const char *char_output_2 = &string_output[0];
	output(-0.45, 0.35, -1, char_output_2);
	if (ants_left == 0){
		string_output = "!!WELL DONE!!";
		const char *char_output_3 = &string_output[0];
		output(-0.025, 0, -0.2, char_output_3);
	}
	//end of output 

	MyCamera.Render();
	MyCamera.Position.y = 1;

	// SOUND
	//sound();
	/*if (shootingSoundIsPlaying && time(0) - shootingSoundStartTime == 2) {
	shootingSoundIsPlaying = false;
	shootingSound.Stop();
	}*/

	// get my current pos 
	float posX = MyCamera.Position.x;
	float posY = MyCamera.Position.y;
	float posZ = MyCamera.Position.z;
	/*float lookX = MyCamera.Position.x + lX;
	float lookZ = MyCamera.Position.z + lZ;
	float lookY = MyCamera.Position.y + lY;*/

	FirstPersonCamera(keys, 0.5, s);
	if (keys['G'] && (time(0) - cameraSwitchStartTime >= 0.5)){ // switch between two cameras with time so it changes only once ebery 0.5 second
		cameraSwitchStartTime = time(0);
		firstPerson = !firstPerson;
		cout << firstPerson << endl;
	}

	// draw ants
	for (auto ant : ants){
		pair<float, float> newPos = ant->getAntNextStep(posX, posY ,posZ,s, ant_speed,health,immune);
		if (checkMovement(newPos.first, newPos.second, s)){
			ant->assignPosition(newPos.first, newPos.second);
		}
		ant->draw();
	}
	glEnable(GL_TEXTURE_2D);
	//draw everything with texture here
	MyComputer.Draw_Skybox(0, 0, 0, 26 * s, 26 * s, 26 * s);

	MyComputer.Draw_ground(0, ground_y, 0, 26 * s, 26 * s, 26 * s);

	MyComputer.Draw_RAM((7) * s, ground_y, 1 * s);

	MyComputer.Draw_GPU();

	MyComputer.Draw_CPU(4*s , ground_y, 13*s , 7*s , 2.5*s , 8*s); // make z = 13

	MyComputer.Draw_Storage();

	MyComputer.Draw_Fan();
	

	glDisable(GL_TEXTURE_2D);


	// third person
	/*if (!firstPerson){
		ThirdPersonCamera(lookX, lookY, lookZ);
	}*/

	// handle bullet

	
	if (keys[' '] && (time(0) - shootBulletStartTime >= 0.5)){
		shootBulletStartTime = time(0);
		//sound
		/*shootingSound.Play();
		shootingSoundIsPlaying = true;
		shootingSoundStartTime = time(0);*/

		bullets.insert(new Bullet(MyCamera.Position.x, MyCamera.Position.y, MyCamera.Position.z, MyCamera.View.x, MyCamera.View.y, MyCamera.View.z, 0.2, 1));
	}

	// draw bullets
	for (auto bullet : bullets){
		bullet->draw();
	}


	//check if bullets outside borders or killed ants;
	vector<Ant*> toKillAnts;
	vector<Bullet*> toKillBullets;
	for (auto bullet : bullets){
		float X = bullet->get_posX(), Y = bullet->get_posY(), Z = bullet->get_posZ();
		if (!checkBulletMovement(X, Z, s)
			|| (X >= 13 * s) || (X <= (-1 * 13 * s))
			|| (Z >= 13 * s) || (Z <= -1 * 13 * s)
			|| (Y >= 13 * s) || (Y <= (-1 * 13 * s))
			){
			//if bullet is out of skybox range
			toKillBullets.push_back(bullet);
		}
		else{
			for (auto ant : ants){
				if ((X <= ant->get_posX() + kill_range && X >= ant->get_posX() - kill_range)
					&& (Y <= ant->get_posY() + kill_range && Y >= ant->get_posY() - kill_range)
					&& (Z <= ant->get_posZ() + kill_range && Z >= ant->get_posZ() - kill_range)
					){
					ants_left--;
					cout << "ANTS LEFT: " << ants_left << endl;
					if ((ant_count - ants_left) % 7 == 0) {
						ant_speed += ant_speed_increase;
						cout << "AREA CLEARED FROM ANTS\n";
					}
					toKillAnts.push_back(ant);
					toKillBullets.push_back(bullet);
					break;
				}
			}
		}
	}

	//kill ants and bullets
	for (auto ant : toKillAnts){
		ants.erase(ant);
	}
	for (auto bullet : toKillBullets){
		bullets.erase(bullet);
	}


	

	// draw glass

	//RAM
	Draw_Glass(6 * s, ground_y + 0.1, 2 * s, 6 * s, 2 * s, 14 * s, 1 , 1, 1, 1, 0);

	//CPU
	Draw_Glass(4*s, ground_y, 13*s, 7*s, s , 3.5*s , false, true, false, false, false);
	Draw_Glass(4*s, ground_y, 8.5*s , 7*s , s ,  3.5*s , false, true, false, false, false);
	Draw_Glass(4*s , ground_y + (1 * s) , 13*s, 7*s , 1.5*s , 8*s, false, true, false, false, false);

	//STORAGE
	Draw_Glass(-12 * s, ground_y + 0.1, -4 * s, 16 * s, 2 * s, 8 * s, 1, 1, 1, 1,0);

	//GPU
	Draw_Glass(-9.7 * s, ground_y + 0.1, 4 * s + 0.2, 6.7 * s, 3 * s, 6 * s + 0.5, false, true, false, true, true);

	glFlush();


	//SwapBuffers(hDC);
	return TRUE;
}

GLvoid KillGLWindow(GLvoid)								// Properly Kill The Window
{
	if (fullscreen)										// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL, 0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);								// Show Mouse Pointer
	}

	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL, NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		hRC = NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd, hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hDC = NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL", hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;									// Set hInstance To NULL
	}
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
*	title			- Title To Appear At The Top Of The Window				*
*	width			- Width Of The GL Window Or Fullscreen Mode				*
*	height			- Height Of The GL Window Or Fullscreen Mode			*
*	bits			- Number Of Bits To Use For Color (8/16/24/32)			*
*	fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*/

BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left = (long)0;			// Set Left Value To 0
	WindowRect.right = (long)width;		// Set Right Value To Requested Width
	WindowRect.top = (long)0;				// Set Top Value To 0
	WindowRect.bottom = (long)height;		// Set Bottom Value To Requested Height

	fullscreen = fullscreenflag;			// Set The Global Fullscreen Flag

	hInstance = GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc = (WNDPROC)WndProc;					// WndProc Handles Messages
	wc.cbClsExtra = 0;									// No Extra Window Data
	wc.cbWndExtra = 0;									// No Extra Window Data
	wc.hInstance = hInstance;							// Set The Instance
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground = NULL;									// No Background Required For GL
	wc.lpszMenuName = NULL;									// We Don't Want A Menu
	wc.lpszClassName = "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}

	if (fullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth = width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight = height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel = bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL, "The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?", "GL template", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			{
				fullscreen = FALSE;		// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL, "Program Will Now Close.", "ERROR", MB_OK | MB_ICONSTOP);
				return FALSE;									// Return FALSE
			}
		}
	}

	if (fullscreen)												// Are We Still In Fullscreen Mode?
	{
		dwExStyle = WS_EX_APPWINDOW;								// Window Extended Style
		dwStyle = WS_POPUP;										// Windows Style
		ShowCursor(FALSE);										// Hide Mouse Pointer
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle = WS_OVERLAPPEDWINDOW;							// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd = CreateWindowEx(dwExStyle,							// Extended Style For The Window
		"OpenGL",							// Class Name
		title,								// Window Title
		dwStyle |							// Defined Window Style
		WS_CLIPSIBLINGS |					// Required Window Style
		WS_CLIPCHILDREN,					// Required Window Style
		0, 0,								// Window Position
		WindowRect.right - WindowRect.left,	// Calculate Window Width
		WindowRect.bottom - WindowRect.top,	// Calculate Window Height
		NULL,								// No Parent Window
		NULL,								// No Menu
		hInstance,							// Instance
		NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd =				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		bits,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

	if (!(hDC = GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!SetPixelFormat(hDC, PixelFormat, &pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(hRC = wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!wglMakeCurrent(hDC, hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	ShowWindow(hWnd, SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen

	if (!InitGL())									// Initialize Our Newly Created GL Window
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Initialization Failed.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	return TRUE;									// Success
}

LRESULT CALLBACK WndProc(HWND	hWnd,			// Handle For This Window
	UINT	uMsg,			// Message For This Window
	WPARAM	wParam,			// Additional Message Information
	LPARAM	lParam)			// Additional Message Information
{
	switch (uMsg)									// Check For Windows Messages
	{
	case WM_ACTIVATE:							// Watch For Window Activate Message
	{
													if (!HIWORD(wParam))					// Check Minimization State
													{
														active = TRUE;						// Program Is Active
													}
													else
													{
														active = FALSE;						// Program Is No Longer Active
													}

													return 0;								// Return To The Message Loop
	}

	case WM_SYSCOMMAND:							// Intercept System Commands
	{
													switch (wParam)							// Check System Calls
													{
													case SC_SCREENSAVE:					// Screensaver Trying To Start?
													case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
														return 0;							// Prevent From Happening
													}
													break;									// Exit
	}

	case WM_CLOSE:								// Did We Receive A Close Message?
	{
													PostQuitMessage(0);						// Send A Quit Message
													return 0;								// Jump Back
	}

	case WM_KEYDOWN:							// Is A Key Being Held Down?
	{
													keys[wParam] = TRUE;					// If So, Mark It As TRUE
													return 0;								// Jump Back
	}

	case WM_KEYUP:								// Has A Key Been Released?
	{
													keys[wParam] = FALSE;					// If So, Mark It As FALSE
													return 0;								// Jump Back
	}

	case WM_SIZE:								// Resize The OpenGL Window
	{
													ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));  // LoWord=Width, HiWord=Height
													return 0;								// Jump Back
	}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE	hInstance,			// Instance
	HINSTANCE	hPrevInstance,		// Previous Instance
	LPSTR		lpCmdLine,			// Command Line Parameters
	int			nCmdShow)			// Window Show State
{
	MSG		msg;									// Windows Message Structure
	BOOL	done = FALSE;								// Bool Variable To Exit Loop

	// Ask The User Which Screen Mode They Prefer
	//if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
	{
		fullscreen = FALSE;							// Windowed Mode
	}

	// Create Our OpenGL Window
	if (!CreateGLWindow("OpenGL template", 640, 480, 16, fullscreen))
	{
		return 0;									// Quit If Window Was Not Created
	}

	while (!done)									// Loop That Runs While done=FALSE
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))	// Is There A Message Waiting?
		{
			if (msg.message == WM_QUIT)				// Have We Received A Quit Message?
			{
				done = TRUE;							// If So done=TRUE
			}
			else									// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);				// Translate The Message
				DispatchMessage(&msg);				// Dispatch The Message
			}
		}
		else										// If There Are No Messages
		{
			// Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()
			if (active)								// Program Active?
			{
				if (keys[VK_ESCAPE])				// Was ESC Pressed?
				{
					done = TRUE;						// ESC Signalled A Quit
				}
				else								// Not Time To Quit, Update Screen
				{
					DrawGLScene();					// Draw The Scene
					SwapBuffers(hDC);				// Swap Buffers (Double Buffering)
				}
			}

			if (keys[VK_F1])						// Is F1 Being Pressed?
			{
				keys[VK_F1] = FALSE;					// If So Make Key FALSE
				KillGLWindow();						// Kill Our Current Window
				fullscreen = !fullscreen;				// Toggle Fullscreen / Windowed Mode
				// Recreate Our OpenGL Window
				if (!CreateGLWindow("OpenGL template", 640, 480, 16, fullscreen))
				{
					return 0;						// Quit If Window Was Not Created
				}
			}
		}
	}

	// Shutdown
	KillGLWindow();									// Kill The Window
	return (msg.wParam);							// Exit The Program
}

int main(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{
	return WinMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow);;
}
