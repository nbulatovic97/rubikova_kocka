#include <stdlib.h>
#include <windows.h>
#include "func.h"
#include "var.h"
#include "key_mou.h"
#include "model.h"
#include "cal.h"


int layer = 0;
int width = 1150, height = 700;

//parametri koji se koriste za animaciju dugmeta
float button::x_par_butt = 0.07;
float button::y_par_butt = 0.05;
float button::clickdelay = 200;

bool change = false;
bool isTransition = false;
bool isMousePressed = false;

int px = -1, py = -1;
float xscreen = 0, fromXScreen = 0, toXScreen = 0;
float yscreen = 0, fromYScreen = 0, toYScreen = 0;
float perc = 0;
float camX = -0, camY = 0, camZ = 0;
float viewportX = 8, viewportY = 5;

double brzina =0.001; //brzina kretanja kamere
int rotationType = 0; //tip rotacije kocke
const double PI = 3.1415926535;
double rorationSpeed = 0.15;  // brzina rotacije prilikom pomeranja kocke
double totalRotation = 0;

Vector3d rotationAxis;

//definisanje parametara svakog od dugmica

button butt_start = button(0.5, -0.5, 1.5, 1.5, color(0, 0.7, 0), color(0, 0, 0), "ZAPOCNI ->");
button butt_exit = button(-2.0, -0.5, 1.5, 1.5, color(0.8, 0, 0), color(1, 1, 1), "ISKLJUCI");
button butt_nazad = button(4.5, -2, 0.5, 0.3, color(0.9, 0.9, 0.2), color(0, 0, 1), "<--");
button butt_resi = button(6.0, -2 , 0.95, 0.3, color(0.0, 0.75, 0.0), color(0, 0.0, 0), "RESENJE");


State kocka;
Quaterniond camera = Quaterniond{ AngleAxisd{1, Vector3d{0.5,0.5,0}} }; //pocetna pozicija gleda na kocku pod uglom tako da se vide 3 strane kocke umesto samo prednja 2D strana

double* matrix = new double[16];
vector<char> moveList;
vector<tacka> rotationQueue;
Quaterniond cubesRotation[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE];


//main funkcija
int main(int argc, char* argv[]) {

	// Inicijalizujemo GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	
	glClearDepth(1.0f);

	//pravim prozor
	glutInitWindowSize(width, height);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Rubikova kocka");
	
	
	inicijalizuj();


	// podesavanje pozadine
	glClearColor(0.75, 0.75, 0.75, 1); 

	//Enable blok
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	
	
	
	//Ukljucujemo blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	
	//podesavanje parametara svetlosti
	GLfloat position[] = { 1,-10,4,1 };
	GLfloat ambient[] = { 1,1,1,1 };
	GLfloat diffuse[] = { 1,1,1,1 };
	GLfloat specular[] = { 1,1,1,1 };

	//Inicijalizujemo osobine svetlosti 
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, specular); //koristim bez, ali ostavljam opciju 
	

	glLoadIdentity();
	glutMainLoop();
	return 0;

}

