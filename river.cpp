
//Headers
#include<windows.h>
#include<stdio.h>
//#include"mywindow.h"
#include<GL/gl.h>
#include<GL/glu.h>
#include"circle.h"
//macro
#define WINWIDTH 800
#define WINHEIGHT 600


//library linking
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")
//global function decelarations
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//global variable decelarations
DWORD dwStyle;
WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) };
bool gbFullscreen = false;
HWND ghwnd = NULL;
FILE* gpfile = NULL;
HDC ghdc = NULL;
HGLRC ghrc = NULL;
bool gbActiveWindow = false;
GLUquadric* head = NULL;
GLUquadric* neak = NULL;
GLUquadric* body = NULL;
GLUquadric* leftjoint = NULL;
GLUquadric* rightjoint = NULL;
GLUquadric* leftupperarm = NULL;
GLUquadric* rightupperarm = NULL;
GLUquadric* leftlowerarm = NULL;
GLUquadric* righlowerarm = NULL;
GLUquadric* lefthand = NULL;
GLUquadric* tree = NULL;
int left_shoulder = 0;
int left_elbow = 0;
float body1 = 0.0f;
int neak1 = 0;
int right_shoulder = 0;
int right_elbow = 0;
int left_upper_leg = 0;
int right_upper_leg = 0;
int left_lower_leg = 0;
int right_lower_leg = 0;
float boy_x = 2.0f;
float  W_Angle = 3.0f;
int wing_1 = 0;
int wing_2 = 0;
float b_x=-3.0f;
float b2_x = 3.0f;
GLUquadric* quadric = NULL;
GLfloat lightAmbient[] = { 0.0f,0.0f,0.0f,1.0f };//gray light
GLfloat lightDiffuse[] = { 1.0f,1.0f,1.0f,1.0f };
GLfloat lightSpecular[] = { 1.0f,1.0f,1.0f,1.0f };
GLfloat lightPosition[] = { 2.0f,5.0f,5.0f,0.0f };

GLfloat materialAmbient[4];
GLfloat materialDiffuse[4];
GLfloat materialSpecular[4];
GLfloat  materialshininess;


float X = 0.0f;
float y = 0.0f;
float g_x = -4.0f;
int flag = 0;
int r_x;
int flag1 = 0;
float g_z = 0.0f;
float l_z = 2.0f;

//float b_color_y;
//float b_color_z;
//float h_color_x;
//float h_color_y;
//float h_color_z;
struct node
{
    float translate_pos;
	float body_color_x;
   float body_color_y;
   float body_color_z;
   float head_color_x;
   float head_color_y;
   float head_color_z;
	struct node* next;
};

typedef struct node NODE;
typedef struct node* PNODE;
typedef struct node** PPNODE;


//WinMain()
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//function decarations
	void Initialize(void);   //can be Init()
	void Display(void);
	//variable declarations
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("My App");
	int x, y, x1, y1;
	bool bDone = false;
	//code
	x = GetSystemMetrics(SM_CXSCREEN);
	y = GetSystemMetrics(SM_CYSCREEN);
	x1 = ((x / 2) - (800 / 2));
	y1 = ((y / 2) - (600 / 2));
	//initialization of WNDCLASSEX
	if (fopen_s(&gpfile, "RRH_LOG.txt", "w") != 0)
	{
		MessageBox(NULL, TEXT("Cannot create desired file"), TEXT("ERROR"), MB_OK);
		exit(0);
	}
	else
	{
		fprintf(gpfile, "log file successfully created. program start sucessfully");
	}

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);//GDI function
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	//register above class
	RegisterClassEx(&wndclass);

	//create window
	//to use style here use CreateWindowEx add style WS_EX 
	hwnd = CreateWindowEx(WS_EX_APPWINDOW,
		szAppName,
		TEXT("RENUKA HAJARE"),
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
		x1,
		y1,
		WINWIDTH,
		WINHEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL);
	ghwnd = hwnd;
	Initialize();
	ShowWindow(hwnd, iCmdShow);
	SetForegroundWindow(hwnd);// reassure top window wihout children wihout siblings
	SetFocus(hwnd);//for WM_SETFOCUS
	//Game loop
	while (bDone == false)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				bDone = true;
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			if (gbActiveWindow == true)
			{
				//here you should call update function for openGL rendering

				//here you should call Display function for openGL rendering

				Display();  //or draw or render
			}
		}
	}

	return((int)msg.wParam);

}
// the parameter form MSG structure
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// local function declration
	void ToggleFullscreen(void);
	void Resize(int, int);
	void Uninitialize(void);






	//code
	switch (iMsg)
	{
	case WM_SETFOCUS:
		gbActiveWindow = true;
		break;
	case WM_KILLFOCUS:
		gbActiveWindow = false;
		break;
	case WM_ERASEBKGND:
		return(0);
	case WM_SIZE:
		Resize(LOWORD(lParam), HIWORD(lParam));
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hwnd);
			break;
		case WM_CLOSE:
			DestroyWindow(hwnd);
			break;
		case 0X46:
		case 0X66:
			ToggleFullscreen();
			break;
		default:
			break;
		}
		break;

	case WM_CHAR:
		switch (wParam)
		{
		case 's':
			left_shoulder = (left_shoulder + 5) % 360;
			right_shoulder = (right_shoulder - 5) % 360;
			break;
		case 'S':
			left_shoulder = (left_shoulder -5) % 360;
			right_shoulder = (right_shoulder + 5) % 360;
			break;
		case 'e':
			left_elbow = (left_elbow + 5) % 360;
			right_elbow = (right_elbow - 5) % 360;

			break;
		case 'E':
			left_elbow = (left_elbow - 5) % 360;
			right_elbow = (right_elbow + 5) % 360;

			break;
		case 'L':
			left_upper_leg = (left_upper_leg + 5) % 360;
			right_upper_leg = (right_upper_leg - 5) % 360;
			break;
		case 'l':
			left_upper_leg = (left_upper_leg - 5) % 360;
			right_upper_leg = (right_upper_leg + 5) % 360;
			break;
		case 'T':
			left_lower_leg = (left_lower_leg + 5) % 360;
			right_lower_leg = (right_lower_leg - 5) % 360;
			break;
		case 't':
			left_lower_leg = (left_lower_leg - 5) % 360;
			right_lower_leg = (right_lower_leg + 5) % 360;
			break;
		case 'P':
		    fprintf(gpfile, "leftshoulder=%d",left_shoulder);
			fprintf(gpfile, "/t righthoulder=%d", right_shoulder);

			break;
		case 'B':
			body1 = body1 + 1.0f;
			neak1 = (neak1 + 5) % 360;

			break;
		case 'N':
			neak1 = (neak1 + 5) % 360;
			break;
		case 'n':
			neak1 = (neak1 - 5) % 360;
			break;
		}

		break;



	case WM_DESTROY:
		Uninitialize();
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
void ToggleFullscreen(void)
{
	// local variable declration
	MONITORINFO mi = { sizeof(MONITORINFO) };

	//code
	if (gbFullscreen == false)
	{
		dwStyle = GetWindowLong(ghwnd, GWL_STYLE);
		if (dwStyle & WS_OVERLAPPEDWINDOW)
		{
			if (GetWindowPlacement(ghwnd, &wpPrev) && GetMonitorInfo(MonitorFromWindow(ghwnd, MONITORINFOF_PRIMARY), &mi))
			{
				SetWindowLong(ghwnd, GWL_STYLE, (dwStyle & ~WS_OVERLAPPEDWINDOW));
				SetWindowPos(ghwnd, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right - mi.rcMonitor.left, mi.rcMonitor.bottom - mi.rcMonitor.top, SWP_NOZORDER | SWP_FRAMECHANGED);

			}
		}
		ShowCursor(FALSE);
		gbFullscreen = true;
	}
	else
	{
		SetWindowLong(ghwnd, GWL_STYLE, (dwStyle | WS_OVERLAPPEDWINDOW));
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_FRAMECHANGED | SWP_NOZORDER);
		ShowCursor(TRUE);
		gbFullscreen = false;
	}



}

void Initialize(void)
{
	//function declaration
	void Resize(int, int);
	// variable decaration
	PIXELFORMATDESCRIPTOR pfd;
	int iPixelformatindex;
	//code
	ghdc = GetDC(ghwnd);

	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cRedBits = 8;
	pfd.cGreenBits = 8;
	pfd.cBlueBits = 8;
	pfd.cAlphaBits = 8;

	iPixelformatindex = ChoosePixelFormat(ghdc, &pfd);

	if (iPixelformatindex == 0)
	{
		fprintf(gpfile, "ChoosePixelFormat() failed\n");
		DestroyWindow(ghwnd);
	}
	if (SetPixelFormat(ghdc, iPixelformatindex, &pfd) == FALSE)
	{
		fprintf(gpfile, "SetPixelFormat() failed\n");
		DestroyWindow(ghwnd);
	}
	ghrc = wglCreateContext(ghdc);
	if (ghrc == NULL)
	{
		fprintf(gpfile, "wglCreateContext() failed\n");
		DestroyWindow(ghwnd);
	}
	if (wglMakeCurrent(ghdc, ghrc) == FALSE)
	{
		fprintf(gpfile, "wglCreateContext() failed");
		DestroyWindow(ghwnd);
	}



	//3d
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	//SetClearColor
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);


	//lighting
	glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpecular);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPosition);


	//warmup call for Resize()
	Resize(WINWIDTH, WINHEIGHT);
}

void Resize(int width, int height)
{
	//code
	if (height == 0)
		height = 1;
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
}
void Display(void)
{
	void Boy(void);
	void Tree(void);
	void Bird(float, float, float, float, float, float);
	void boat(void);
	void boat2(void);
	void girl(void);
	void InsertLast(PPNODE,float, float,float ,float, float,float,float );
	//code
	PNODE Head = NULL;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -3.0f);



	//river
	glBegin(GL_QUADS);

	glColor3f(0.0f, 0.5f, 1.0f);
	glVertex3f(7.0f, 0.1f, 0.0f);
	glVertex3f(-7.0f, 0.1f, 0.0f);
	glVertex3f(-7.0f, 0.05f, 0.0f);
	glVertex3f(7.0f, 0.05f, 0.0f);

	glColor3f(0.0f, 0.5f, 0.7f);
	glVertex3f(7.0f, 0.05f, 0.0f);
	glVertex3f(-7.0f, 0.05f, 0.0f);
	glVertex3f(-7.0f, 0.0f, 0.0f);
	glVertex3f(7.0f, 0.0f, 0.0f);

	glColor3f(0.0f, 0.4f, 0.7f);
	glVertex3f(7.0f, 0.0f, 0.0f);
	glVertex3f(-7.0f, 0.0f, 0.0f);
	glVertex3f(-7.0f, -0.05f, 0.0f);
	glVertex3f(7.0f, -0.05f, 0.0f);

	glColor3f(0.0f, 0.3f, 0.6f);
	glVertex3f(7.0f, -0.05f, 0.0f);
	glVertex3f(-7.0f, -0.05f, 0.0f);
	glVertex3f(-7.0f, -0.15f, 0.0f);
	glVertex3f(7.0f, -0.15f, 0.0f);


	glColor3f(0.0f, 0.2f, 0.5f);
	glVertex3f(7.0f, -0.15f, 0.0f);
	glVertex3f(-7.0f, -0.15f, 0.0f);
	glVertex3f(-7.0f, -0.30f, 0.0f);
	glVertex3f(7.0f, -0.30f, 0.0f);


	glEnd();

	//sky
	glBegin(GL_QUADS);
	glColor3f(0.4f, 0.7f, 1.0f);
	glVertex3f(7.0f, 5.0f, 0.0f);
	glVertex3f(-7.0f, 5.0f, 0.0f);
	glVertex3f(-7.0f, 0.1f, 0.0f);
	glVertex3f(7.0f, 0.1f, 0.0f);
	glEnd();

	//sun
	glColor3f(1.0f, 1.0f, 0.0f);
	circle(0.2f, 0.2f, 0.8f, 0.8f);

	//ground

	glBegin(GL_QUADS);
	glColor3f(0.59f, 0.41f, 0.31f);
	glVertex3f(7.0f, -0.3f, 0.0f);
	glVertex3f(-7.0f, -0.3f, 0.0f);
	glVertex3f(-7.0f, -0.4f, 0.0f);
	glVertex3f(7.0f, -0.4f, 0.0f);

	glColor3f(0.65f, 0.50f, 0.39f);
	glVertex3f(7.0f, -0.4f, 0.0f);
	glVertex3f(-7.0f, -0.4f, 0.0f);
	glVertex3f(-7.0f, -7.0f, 0.0f);
	glVertex3f(7.0f, -7.0f, 0.0f);
	glEnd();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	girl();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	Tree();


	InsertLast(&Head, 0.0f,1.0f, 0.43f, 0.78f, 1.0, 0.1, 0.68f);
	InsertLast(&Head, 1.0f,0.87f, 0.58f, 0.98f, 0.53, 0.12, 0.47f);
	InsertLast(&Head, 2.0f, 1.0, 0.5, 0.0f, 1.0, 0.25, 0.0f);
	InsertLast(&Head, 3.0f,0.80, 0.90, 0.0, 1.0, 1.0, 0.0f);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	boat();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	boat2();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	  
      Boy();








	

   

   
	SwapBuffers(ghdc);


}
void Boy(void)
{
	//BOY
	//glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glScalef(0.5f, 0.5f, 0.5f);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glTranslatef(boy_x, -0.2f, -3.0f);
	glPushMatrix();
	glRotatef(90, 0.0f, 1.0f, 0.0f);
	glPushMatrix();
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	body = gluNewQuadric();
	glColor3f(1.0f, 0.0f, 0.0f);
	gluCylinder(body, 0.1f, 0.15f, 0.3f, 30, 30);
	glPopMatrix();




	//  right UPPER HAND
	glPushMatrix();
	glTranslatef(0.14f, 0.279f, 0.0f);
	glRotatef((GLfloat)right_shoulder, 1.0f, 0.0f, 0.0f);
	glPushMatrix();
	rightupperarm = gluNewQuadric();
	glRotatef(8.0f, 0.0f, 0.0f, 1.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	gluCylinder(rightupperarm, 0.025, 0.025, 0.18, 30, 30);
	glPopMatrix();

	//RIGHT lOWER hand
	glTranslatef(0.02f, -0.15f, 0.0f);
	glRotatef((GLfloat)right_elbow, 1.0f, 0.0f, 0.0f);
	glPushMatrix();
	righlowerarm = gluNewQuadric();
	glRotatef(9.0f, 0.0f, 0.0f, 1.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	gluCylinder(righlowerarm, 0.025, 0.025, 0.18, 30, 30);
	glPopMatrix();
	glPopMatrix();
	//glPopMatrix();




	//LEFT UPPER ARM
	glPushMatrix();
	glTranslatef(-0.14f, 0.279f, 0.0f);
	glRotatef((GLfloat)left_shoulder, 1.0f, 0.0f, 0.0f);
	glPushMatrix();
	rightupperarm = gluNewQuadric();
	glRotatef(-8.0f, 0.0f, 0.0f, 1.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	gluCylinder(rightupperarm, 0.025, 0.025, 0.18, 30, 30);
	glPopMatrix();


	//left lOWER hand
	glTranslatef(-0.019f, -0.15f, 0.0f);
	glRotatef((GLfloat)left_elbow, 1.0f, 0.0f, 0.0f);
	glPushMatrix();
	righlowerarm = gluNewQuadric();
	glRotatef(-9.0f, 0.0f, 0.0f, 1.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	gluCylinder(righlowerarm, 0.025, 0.025, 0.18, 30, 30);
	glPopMatrix();
	glPopMatrix();

	//RIGHT legs
	glPushMatrix();
	glTranslatef(0.05f, -0.011f, 0.0f);
	glRotatef((GLfloat)right_upper_leg, 1.0f, 0.0f, 0.0f);
	glPushMatrix();
	leftjoint = gluNewQuadric();
	//glRotatef(1.0f, 0.0f, 0.0f, 1.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	//color red 0.137255 green 0.137255 blue 0.556863
	glColor3f(0.13755, 0.13755, 0.556863);
	gluCylinder(leftjoint, 0.05, 0.03, 0.15, 30, 30);
	glPopMatrix();


	glTranslatef(0.0f, -0.15, 0.0);
	glRotatef((GLfloat)right_lower_leg, 1.0f, 0.0f, 0.0f);
	glPushMatrix();
	rightjoint = gluNewQuadric();
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(rightjoint, 0.03, 0.03, 0.16, 30, 30);
	glPopMatrix();
	glPopMatrix();



	//LEFT LEG
	glPushMatrix();
	glTranslatef(-0.05f, -0.011f, 0.0f);
	glRotatef((GLfloat)left_upper_leg, 1.0f, 0.0f, 0.0f);
	glPushMatrix();
	leftjoint = gluNewQuadric();
	//glRotatef(1.0f, 0.0f, 0.0f, 1.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(leftjoint, 0.05, 0.03, 0.15, 30, 30);
	glPopMatrix();


	glTranslatef(0.0f, -0.15, 0.0);
	glRotatef((GLfloat)left_lower_leg, 1.0f, 0.0f, 0.0f);
	glPushMatrix();
	rightjoint = gluNewQuadric();
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(rightjoint, 0.03, 0.03, 0.16, 30, 30);
	glPopMatrix();
	glPopMatrix();




	//Neak
	glPushMatrix();
	glTranslatef(0.0f, 0.34f, 0.0);
	glRotatef((GLfloat)neak1, 0.0, 1.0f, 0.0f);
	glPushMatrix();
	neak = gluNewQuadric();
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glColor3f(0.92f, 0.78f, 0.62f);
	gluCylinder(neak, 0.03, 0.03, 0.04, 30, 30);
	glPopMatrix();




	//HEAD
	glTranslatef(0.0f, 0.09f, 0.0);
	glPushMatrix();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	head = gluNewQuadric();
	//glScalef(0.1f, 0.1f, 0.8f);
	gluSphere(head, 0.1f, 30, 30);
	//SolidSphere(0.1f,30,30);
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
	
	
	
		boy_x = boy_x - 0.004f;
	
}


void Tree(void)
{

	//TREE
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHTING);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(1.85f, 0.3f, -3.0f);
	materialAmbient[0] = 0.0f;
	materialAmbient[1] = 0.0f;
	materialAmbient[2] = 0.0f;
	materialAmbient[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);

	materialDiffuse[0] = 0.52f;
	materialDiffuse[1] = 0.37f;
	materialDiffuse[2] = 0.26f;
	materialDiffuse[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);

	materialSpecular[0] = 1.0f;
	materialSpecular[1] = 1.0f;
	materialSpecular[2] = 1.0f;
	materialSpecular[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);

	materialshininess = 50.0f;
	glMaterialf(GL_FRONT, GL_SHININESS, materialshininess);


	tree = gluNewQuadric();
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(tree, 0.1, 0.1, 0.7, 30, 30);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(1.8f, -0.1f, -3.0f);
	materialAmbient[0] = 0.0f;
	materialAmbient[1] = 0.0f;
	materialAmbient[2] = 0.0f;
	materialAmbient[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);
	materialDiffuse[0] = 0.196078f;
	materialDiffuse[1] = 0.8f;
	materialDiffuse[2] = 0.196078f;
	materialDiffuse[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);

	materialSpecular[0] = 1.0f;
	materialSpecular[1] = 1.0f;
	materialSpecular[2] = 1.0f;
	materialSpecular[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);

	materialshininess = 50.0f;
	glMaterialf(GL_FRONT, GL_SHININESS, materialshininess);
	//glTranslatef(0.0, 0.9f, 0.0f);
	glRotatef(-90, 1.0f, 0.0f, 0.0f);
	//glRotatef( 90.0f, 1.0f, 0.0f, 0.0f);
	SolidCone(0.5, 0.5, 16, 16);





	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(1.8f, 0.1f, -3.0f);
	materialAmbient[0] = 0.0f;
	materialAmbient[1] = 0.0f;
	materialAmbient[2] = 0.0f;
	materialAmbient[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);
	materialDiffuse[0] = 0.0f;
	materialDiffuse[1] = 1.0f;
	materialDiffuse[2] = 0.498039f;
	materialDiffuse[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);

	materialSpecular[0] = 1.0f;
	materialSpecular[1] = 1.0f;
	materialSpecular[2] = 1.0f;
	materialSpecular[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);

	materialshininess = 0.6 * 128;
	glMaterialf(GL_FRONT, GL_SHININESS, materialshininess);
	//glTranslatef(0.0, 0.9f, 0.0f);
	glRotatef(-90, 1.0f, 0.0f, 0.0f);
	//glRotatef( 90.0f, 1.0f, 0.0f, 0.0f);
	SolidCone(0.4, 0.4, 16, 16);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(1.8f, 0.3f, -3.0f);
	materialAmbient[0] = 0.0f;
	materialAmbient[1] = 0.0f;
	materialAmbient[2] = 0.0f;
	materialAmbient[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);

	materialDiffuse[0] = 0.0f;
	materialDiffuse[1] = 1.0f;
	materialDiffuse[2] = 0.0f;
	materialDiffuse[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);

	materialSpecular[0] = 1.0f;
	materialSpecular[1] = 1.0f;
	materialSpecular[2] = 1.0f;
	materialSpecular[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);

	materialshininess = 50.0f;
	glMaterialf(GL_FRONT, GL_SHININESS, materialshininess);
	//glTranslatef(0.0, 0.9f, 0.0f);
	glRotatef(-90, 1.0f, 0.0f, 0.0f);
	//glRotatef( 90.0f, 1.0f, 0.0f, 0.0f);
	SolidCone(0.3, 0.3, 16, 16);

	
	//tree 2
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-1.85f, 0.3f, -3.0f);
	materialAmbient[0] = 0.0f;
	materialAmbient[1] = 0.0f;
	materialAmbient[2] = 0.0f;
	materialAmbient[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);

	materialDiffuse[0] = 0.52f;
	materialDiffuse[1] = 0.37f;
	materialDiffuse[2] = 0.26f;
	materialDiffuse[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);

	materialSpecular[0] = 1.0f;
	materialSpecular[1] = 1.0f;
	materialSpecular[2] = 1.0f;
	materialSpecular[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);

	materialshininess = 50.0f;
	glMaterialf(GL_FRONT, GL_SHININESS, materialshininess);


	tree = gluNewQuadric();
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(tree, 0.1, 0.1, 0.7, 30, 30);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-1.8f, -0.1f, -3.0f);
	materialAmbient[0] = 0.0f;
	materialAmbient[1] = 0.0f;
	materialAmbient[2] = 0.0f;
	materialAmbient[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);
	materialDiffuse[0] = 0.196078f;
	materialDiffuse[1] = 0.8f;
	materialDiffuse[2] = 0.196078f;
	materialDiffuse[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);

	materialSpecular[0] = 1.0f;
	materialSpecular[1] = 1.0f;
	materialSpecular[2] = 1.0f;
	materialSpecular[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);

	materialshininess = 50.0f;
	glMaterialf(GL_FRONT, GL_SHININESS, materialshininess);
	//glTranslatef(0.0, 0.9f, 0.0f);
	glRotatef(-90, 1.0f, 0.0f, 0.0f);
	//glRotatef( 90.0f, 1.0f, 0.0f, 0.0f);
	SolidCone(0.5, 0.5, 16, 16);





	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-1.8f, 0.1f, -3.0f);
	materialAmbient[0] = 0.0f;
	materialAmbient[1] = 0.0f;
	materialAmbient[2] = 0.0f;
	materialAmbient[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);
	materialDiffuse[0] = 0.0f;
	materialDiffuse[1] = 1.0f;
	materialDiffuse[2] = 0.498039f;
	materialDiffuse[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);

	materialSpecular[0] = 1.0f;
	materialSpecular[1] = 1.0f;
	materialSpecular[2] = 1.0f;
	materialSpecular[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);

	materialshininess = 0.6 * 128;
	glMaterialf(GL_FRONT, GL_SHININESS, materialshininess);
	//glTranslatef(0.0, 0.9f, 0.0f);
	glRotatef(-90, 1.0f, 0.0f, 0.0f);
	//glRotatef( 90.0f, 1.0f, 0.0f, 0.0f);
	SolidCone(0.4, 0.4, 16, 16);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(-1.8f, 0.3f, -3.0f);
	materialAmbient[0] = 0.0f;
	materialAmbient[1] = 0.0f;
	materialAmbient[2] = 0.0f;
	materialAmbient[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, materialAmbient);

	materialDiffuse[0] = 0.0f;
	materialDiffuse[1] = 1.0f;
	materialDiffuse[2] = 0.0f;
	materialDiffuse[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, materialDiffuse);

	materialSpecular[0] = 1.0f;
	materialSpecular[1] = 1.0f;
	materialSpecular[2] = 1.0f;
	materialSpecular[3] = 1.0f;
	glMaterialfv(GL_FRONT, GL_SPECULAR, materialSpecular);

	materialshininess = 50.0f;
	glMaterialf(GL_FRONT, GL_SHININESS, materialshininess);
	//glTranslatef(0.0, 0.9f, 0.0f);
	glRotatef(-90, 1.0f, 0.0f, 0.0f);
	//glRotatef( 90.0f, 1.0f, 0.0f, 0.0f);
	SolidCone(0.3, 0.3, 16, 16);

	

	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHTING);

}

void Bird(float b_color_x, float b_color_y, float b_color_z, float h_color_x, float h_color_y, float h_color_z)
{
	glTranslatef(W_Angle, 0.7f, -3.0f);
	glScalef(0.5f, 0.5f, 0.5f);
	//glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glPushMatrix();
	//glColor3f(1.0f, 0.43f, 0.78f);
	glColor3f(b_color_x, b_color_y, b_color_z);
	glPushMatrix();
	glScalef(1.5f, 0.8f, 1.0f);
	quadric = gluNewQuadric();
	gluSphere(quadric, 0.15f, 30, 30);
	glPopMatrix();

	//wing
	glPushMatrix();
	//glTranslatef(0.8f, 0.4f, 0.0f);
	glRotatef(wing_1, 1.0, 0.0, 0.0f);
	glBegin(GL_TRIANGLES);
	//glColor3f(1.0, 0.1, 0.68f);
	glColor3f(h_color_x, h_color_y, h_color_z);
	glVertex3f(0.08f, 0.0f, 0.0f);
	glVertex3f(-0.08f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.4f);
	glEnd();
	glPopMatrix();

	//wing 2
	glPushMatrix();
	//glTranslatef(0.8f, 0.4f, 0.0f);
	glRotatef(wing_2, 1.0, 0.0, 0.0f);
	glBegin(GL_TRIANGLES);
	//glColor3f(1.0, 0.1, 0.68f);
	glColor3f(h_color_x, h_color_y, h_color_z);
	glVertex3f(0.08f, 0.0f, 0.0f);
	glVertex3f(-0.08f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, -0.4f);
	glEnd();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-0.26f, 0.1f, 0.0f);
	//glColor3f(1.0, 0.1, 0.68f);
	glColor3f(h_color_x, h_color_y, h_color_z);
	quadric = gluNewQuadric();
	gluSphere(quadric, 0.1f, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glRotatef(70.0f, 1.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glColor3f(h_color_x, h_color_y, h_color_z);
	glVertex3f(0.4f, 0.08f, 0.0f);
	glVertex3f(0.2f, 0.05f, 0.0f);
	glVertex3f(0.2f, -0.05f, 0.0f);
	glVertex3f(0.4f, -0.08f, 0.0f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0f, 0.0f, 0.0f);
	glTranslatef(-0.35f, 0.1f, 0.0f);
	glRotatef(-60.0f, 0.0f, 1.0f, 0.0f);
	SolidCone(0.03f, 0.09f, 30, 30);
	glPopMatrix();


	//glPushMatrix();
	//glTranslatef(-0.20f, 0.1f, 1.0f);
	//glColor3f(0.0f, 1.0f, 0.0f);
	//quadric = gluNewQuadric();
	//gluSphere(quadric, 0.01, 30, 30);
	//circle(0.01f, 0.01f, -0.10f, 0.05f);
	//glPopMatrix();
	glPopMatrix();



	wing_1 = (wing_1 + 3) % 360;
	wing_2 = (wing_2 - 3) % (-360);
	W_Angle = W_Angle - 0.001f;
}

void boat(void)
{
	
	glTranslatef(b_x, 0.1f, -3.0f);
	glScalef(0.6f, 0.6f, 0.6f);
	glBegin(GL_POLYGON);
	glColor3f(0.6f, 0.5f, 0.5f);
	glVertex3f(-0.5f, 0.2f, 0.0f);
	glVertex3f(-1.5f, 0.2f, 0.0f);
	glVertex3f(-1.2f, 0.0f, 0.0f);
	glVertex3f(-0.8f, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.5f, 0.0f);
	glVertex3f(-0.7, 0.2f, 0.0f);
	glVertex3f(-0.9, 0.4f, 0.0f);
	glVertex3f(-0.9, 0.2f, 0.0f);


	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.647059f, 0.164706f, 0.164706f);
	glVertex3f(-0.9, 0.7f, 0.0f);
	glVertex3f(-1.2, 0.2f, 0.0f);
	glVertex3f(-0.9, 0.2f, 0.0f);

	glEnd();

	b_x = b_x + 0.001f;

}
void boat2(void)
{
	glTranslatef(b2_x, -0.1f, -3.0f);
	glScalef(0.6f, 0.6f, 0.6f);
	glRotatef(180, 0.0f, 1.0f, 0.0f);
	glBegin(GL_POLYGON);
	glColor3f(0.6f, 0.5f, 0.5f);
	glVertex3f(0.5f, 0.2f, 0.0f);
	glVertex3f(-0.5f, 0.2f, 0.0f);
	glVertex3f(-0.2f, 0.0f, 0.0f);
	glVertex3f(0.2f, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 1.0f, 0.0f);
	glVertex3f(0.3, 0.2f, 0.0f);
	glVertex3f(0.1, 0.4f, 0.0f);
	glVertex3f(0.1, 0.2f, 0.0f);

	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.1, 0.7f, 0.0f);
	glVertex3f(-0.2, 0.2f, 0.0f);
	glVertex3f(0.1, 0.2f, 0.0f);

	glEnd();
	b2_x = b2_x - 0.001f;
}

void girl(void)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0f, 0.0f, l_z, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
	glTranslatef(g_x, -0.4f,0.0f);
	glScalef(0.4f, 0.4f, 0.4f);
	glRotatef(r_x, 0.0f, 1.0f, 0.0f);
	glPushMatrix();
	glRotatef(body1, 0.0f, 1.0f, 0.0f);
	glPushMatrix();
	body = gluNewQuadric();
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glColor3f(1.0, 0.5, 0.0f);
	gluCylinder(body, 0.25f, 0.2f, 0.5f, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, -0.5f, 0.0f);
	glRotatef(body1, 0.0f, 1.0f, 0.0f);
	body = gluNewQuadric();
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glColor3f(0.647059f, 0.164706f, 0.164706f);
	gluCylinder(body, 0.2f, 0.35f, 0.2f, 30, 30);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0.0f, -0.7f, 0.0f);
	glRotatef(body1, 0.0f, 1.0f, 0.0f);
	body = gluNewQuadric();
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glColor3f(1.0, 0.5f, 0.0f);
	gluCylinder(body, 0.35f, 0.45f, 0.15f, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, -0.85f, 0.0f);
	glRotatef(body1, 0.0f, 1.0f, 0.0f);
	body = gluNewQuadric();
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glColor3f(1.0, 0.0f, 0.0f);
	gluCylinder(body, 0.45f, 0.55f, 0.20f, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glRotatef((GLfloat)right_shoulder, 1.0f, 0.0f, 0.0f);
	glTranslatef(0.30f, -0.05f, 0.0f);
	glPushMatrix();
	glColor3f(1.0f, 0.5f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(-20.0f, 0.0f, 0.0f, 1.0f);
	rightupperarm = gluNewQuadric();
	gluCylinder(rightupperarm, 0.05f, 0.05f, 0.3, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, -0.29f, 0.0f);
	glRotatef((GLfloat)right_elbow, 1.0f, 0.0f, 0.0f);
	glPushMatrix();
	glColor3f(0.92f, 0.78f, 0.62f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(-20.0f, 0.0f, 0.0f, 1.0f);
	righlowerarm = gluNewQuadric();
	gluCylinder(righlowerarm, 0.05f, 0.05f, 0.3, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, -0.32f, 0.0f);
	quadric = gluNewQuadric();
	gluSphere(quadric, 0.06f, 30, 30);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	//LEFT HAND
	glPushMatrix();
	glRotatef((GLfloat)left_shoulder, 1.0f, 0.0f, 0.0f);
	glTranslatef(-0.30f, -0.05f, 0.0f);
	glPushMatrix();
	glColor3f(1.0f, 0.5f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(20.0f, 0.0f, 0.0f, 1.0f);
	leftupperarm = gluNewQuadric();
	gluCylinder(leftupperarm, 0.05f, 0.05f, 0.3, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, -0.29f, 0.0f);
	glRotatef((GLfloat)left_elbow, 1.0f, 0.0f, 0.0f);
	glPushMatrix();
	glColor3f(0.92f, 0.78f, 0.62f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glRotatef(20.0f, 0.0f, 0.0f, 1.0f);
	righlowerarm = gluNewQuadric();
	gluCylinder(righlowerarm, 0.05f, 0.05f, 0.3, 10, 10);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, -0.32f, 0.0f);
	quadric = gluNewQuadric();
	gluSphere(quadric, 0.06f, 30, 30);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	//neak
	glPushMatrix();
	glTranslatef(0.0f, 0.1f, 0.0);
	glRotatef((GLfloat)neak1, 0.0, 1.0f, 0.0f);
	glPushMatrix();
	neak = gluNewQuadric();
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	gluCylinder(neak, 0.06, 0.06, 0.09, 30, 30);
	glPopMatrix();



	glPushMatrix();
	glTranslatef(0.0f, 0.15f, 0.0);
	glRotatef((GLfloat)neak1, 0.0, 1.0f, 0.0f);
	glPushMatrix();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	head = gluNewQuadric();
	//glScalef(0.1f, 0.1f, 0.8f);
	gluSphere(head, 0.17f, 30, 30);
	//SolidSphere(0.1f,30,30);
	glPopMatrix();
	/*
	glPushMatrix();
	glTranslatef(0.0f, 0.05f, 0.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	quadric = gluNewQuadric();
	gluDisk(quadric, 0.17, 0.25, 30, 30);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 0.20f, 0.0f);
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	quadric = gluNewQuadric();
	gluCylinder(quadric, 0.15, 0.25, 0.15, 30, 30);

	glPopMatrix();
	*/
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	static int i = 0;
	

		r_x = 90;
		if (flag == 0)
		{
			left_shoulder = (left_shoulder - 1) % 360;
			right_shoulder = (right_shoulder + 1) % 360;
			left_upper_leg = (left_upper_leg + 1) % 360;
			right_upper_leg = (right_upper_leg - 1) % 360;
		
			if (right_shoulder == 30 && left_shoulder == -30 && left_upper_leg==30&& right_upper_leg==-30)
			{
				flag = 1;
			}

		}



		else if (flag == 1)
		{

			left_shoulder = (left_shoulder + 1) % 360;
			right_shoulder = (right_shoulder - 1) % 360;
			left_upper_leg = (left_upper_leg - 1) % 360;
			right_upper_leg = (right_upper_leg + 1) % 360;
			if (right_shoulder == -30 && left_shoulder == 30 && left_upper_leg == -30 && right_upper_leg == 30)
				flag = 0;
		}

		g_x = g_x + 0.002;
		if (g_x >= 0.1)
		{
			flag1 = 1;
		}
	

	/*if (flag1 == 1)
	{
		if (r_x < 180)
		{
			r_x = r_x + 1;
		}
		if (flag == 0)
		{
			left_shoulder = (left_shoulder - 1) % 360;
			right_shoulder = (right_shoulder + 1) % 360;
			if (right_shoulder == 30 && left_shoulder == -30)
			{
				flag = 1;
			}
			if (l_z > 0.0f)
			{

				l_z = l_z - 0.01f;
			}
		}



		else if (flag == 1)
		{

			left_shoulder = (left_shoulder + 1) % 360;
			right_shoulder = (right_shoulder - 1) % 360;
			if (right_shoulder == -30 && left_shoulder == 30)
				flag = 0;
		}

	}
	*/
}

void InsertLast(PPNODE last, float x, float b_color_x, float b_color_y, float b_color_z, float h_color_x, float h_color_y, float h_color_z)
{
	PNODE temp = (*last);
	PNODE newn = (PNODE)malloc(sizeof(NODE));
	newn->translate_pos = x;
	newn->body_color_x = b_color_x;
	newn->body_color_y = b_color_y;
	newn->body_color_z = b_color_z;
	newn->head_color_x = h_color_x;
	newn->head_color_y = h_color_y;
	newn->head_color_z = h_color_z;
	newn->next = NULL;

	if ((*last) == NULL)
	{
		(*last) = newn;

	}
	else
	{
		while ((temp)->next != NULL)
		{
			temp = temp->next;
	    }
		temp->next = newn;
	}

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(newn->translate_pos, 0.0f, 0.0f);
	Bird(newn->body_color_x, newn->body_color_y, newn->body_color_z, newn->head_color_x, newn->head_color_y, newn->head_color_z);
}

void Uninitialize(void)
{
	//code

	if (gbFullscreen == true)
	{
		dwStyle = GetWindowLong(ghwnd, GWL_STYLE);
		SetWindowLong(ghwnd, GWL_STYLE, (dwStyle | WS_OVERLAPPEDWINDOW));
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_FRAMECHANGED | SWP_NOZORDER);
		ShowCursor(TRUE);
	}
	if (wglGetCurrentContext() == ghrc)
	{
		wglMakeCurrent(NULL, NULL);
	}

	if (ghrc)
	{
		wglDeleteContext(ghrc);
		ghrc = NULL;
	}
	if (ghdc)
	{
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}


	if (gpfile)
	{
		fprintf(gpfile, "log file is close sucessfully. program ended sucessfully");
		fclose(gpfile);
		gpfile = NULL;
	}

}


