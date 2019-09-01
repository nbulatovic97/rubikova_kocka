#ifndef VAR_H
#define VAR_H

#include <Eigen/Eigen>
#include <bitset>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
#include <GL/freeglut.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <stdio.h>
#include <assert.h>
#include <map>
#include <set>
#include <string.h>
#include <deque>
#include <queue>
#include <stack>


using namespace std;
using namespace Eigen;

//podesavanje velicine kocke (2 ili 3)
#define CUBE_SIZE 3

//definisanje skracenica za for radi preglednijeg koda
#define FOR(i,a,b) for(int i=a;i<=b;++i)
#define FOR0(i,n) for(int i=0;i<n;++i)



extern int layer;


//pravimo klasu tacka za laksi rad sa tackama u prostoru
class tacka {
public:
	double x, y, z;
	tacka() {

	}
	tacka(double px, double py, double pz) {
		x = px;
		y = py;
		z = pz;
	}
};


//pravimo klasu color koja sadrzi parametre RGBA koju koristimo za bojenje nekih objekata
class color {

public:
	GLfloat r, g, b, a;

	color() {
		r = 0;
		g = 0;
		b = 0;
		a = 1;
	}

	color(float ir, float ig, float ib) {
		r = ir;
		g = ig;
		b = ib;
		a = 1;
	}

	GLfloat* getArray() {
		float c[4];
		c[0] = r;
		c[1] = g;
		c[2] = b;
		c[3] = a;
		return c;
	}
};

//ideja ove klase je definisanje mogucih pokreta kocke i stanja jedne strancie male kocke u zavisnosti od polozaja u velikoj rubikovoj kocki
//program iscrtava 3x3 kocku kao 27 kocki pa je potrebno razdvojiti unutrasnje i spoljasnje(spoljasnje delimo na 6 razlicitih strana kocke itd...)

class State {

public:
	int faces[6][CUBE_SIZE][CUBE_SIZE];

	State() {
		FOR0(k, 6) {
			FOR0(i, CUBE_SIZE)
				FOR0(j, CUBE_SIZE)
				faces[k][i][j] = k;
		}
	}
	
	bool isSolved() {

		FOR0(k, 6) {
			int color = faces[k][0][0];
			FOR0(j, CUBE_SIZE) {
				FOR0(i, CUBE_SIZE) {
					if (faces[k][j][i] != color)
						return false;
				}
			}
		}
		return true;

	}

	
	void front_anticlock() {

		int t[CUBE_SIZE];

		FOR0(i, CUBE_SIZE) {
			t[i] = faces[4][CUBE_SIZE - 1 - layer][CUBE_SIZE - 1 - i];
			faces[4][CUBE_SIZE - 1 - layer][CUBE_SIZE - 1 - i] = faces[3][CUBE_SIZE - 1 - i][layer];
			faces[3][CUBE_SIZE - 1 - i][layer] = faces[5][layer][i];
			faces[5][layer][i] = faces[2][i][CUBE_SIZE - 1 - layer];
			faces[2][i][CUBE_SIZE - 1 - layer] = t[i];
		}

		if (layer == 0) {
			FOR0(l, CUBE_SIZE / 2) {
				FOR(i, l, CUBE_SIZE - 2 - l) {
					t[i] = faces[0][l][CUBE_SIZE - 1 - i];
					faces[0][l][CUBE_SIZE - 1 - i] = faces[0][CUBE_SIZE - 1 - i][CUBE_SIZE - 1 - l];
					faces[0][CUBE_SIZE - 1 - i][CUBE_SIZE - 1 - l] = faces[0][CUBE_SIZE - 1 - l][i];
					faces[0][CUBE_SIZE - 1 - l][i] = faces[0][i][l];
					faces[0][i][l] = t[i];
				}
			}
		}

	}

	void front_clock() {

		int t[CUBE_SIZE];

		FOR0(i, CUBE_SIZE) {
			t[i] = faces[4][CUBE_SIZE - 1 - layer][i];
			faces[4][CUBE_SIZE - 1 - layer][i] = faces[2][CUBE_SIZE - 1 - i][CUBE_SIZE - 1 - layer];
			faces[2][CUBE_SIZE - 1 - i][CUBE_SIZE - 1 - layer] = faces[5][layer][CUBE_SIZE - 1 - i];
			faces[5][layer][CUBE_SIZE - 1 - i] = faces[3][i][layer];
			faces[3][i][layer] = t[i];
		}

		if (layer == 0) {
			FOR0(l, CUBE_SIZE / 2) {
				FOR(i, l, CUBE_SIZE - 2 - l) {
					t[i] = faces[0][l][i];
					faces[0][l][i] = faces[0][CUBE_SIZE - 1 - i][l];
					faces[0][CUBE_SIZE - 1 - i][l] = faces[0][CUBE_SIZE - 1 - l][CUBE_SIZE - 1 - i];
					faces[0][CUBE_SIZE - 1 - l][CUBE_SIZE - 1 - i] = faces[0][i][CUBE_SIZE - 1 - l];
					faces[0][i][CUBE_SIZE - 1 - l] = t[i];
				}
			}
		}

	}

	void back_anticlock() {
		int t[CUBE_SIZE];

		FOR0(i, CUBE_SIZE) {
			t[i] = faces[4][layer][i];
			faces[4][layer][i] = faces[2][CUBE_SIZE - 1 - i][layer];
			faces[2][CUBE_SIZE - 1 - i][layer] = faces[5][CUBE_SIZE - 1 - layer][CUBE_SIZE - 1 - i];
			faces[5][CUBE_SIZE - 1 - layer][CUBE_SIZE - 1 - i] = faces[3][i][CUBE_SIZE - 1 - layer];
			faces[3][i][CUBE_SIZE - 1 - layer] = t[i];
		}

		if (layer == 0) {
			FOR0(l, CUBE_SIZE / 2) {
				FOR(i, l, CUBE_SIZE - 2 - l) {
					t[i] = faces[1][l][CUBE_SIZE - 1 - i];
					faces[1][l][CUBE_SIZE - 1 - i] = faces[1][CUBE_SIZE - 1 - i][CUBE_SIZE - 1 - l];
					faces[1][CUBE_SIZE - 1 - i][CUBE_SIZE - 1 - l] = faces[1][CUBE_SIZE - 1 - l][i];
					faces[1][CUBE_SIZE - 1 - l][i] = faces[1][i][l];
					faces[1][i][l] = t[i];
				}
			}
		}
	}

	void back_clock() {
		int t[CUBE_SIZE];

		FOR0(i, CUBE_SIZE) {
			t[i] = faces[4][layer][CUBE_SIZE - 1 - i];
			faces[4][layer][CUBE_SIZE - 1 - i] = faces[3][CUBE_SIZE - 1 - i][CUBE_SIZE - 1 - layer];
			faces[3][CUBE_SIZE - 1 - i][CUBE_SIZE - 1 - layer] = faces[5][CUBE_SIZE - 1 - layer][i];
			faces[5][CUBE_SIZE - 1 - layer][i] = faces[2][i][layer];
			faces[2][i][layer] = t[i];
		}

		if (layer == 0) {
			FOR0(l, CUBE_SIZE / 2) {
				FOR(i, l, CUBE_SIZE - 2 - l) {
					t[i] = faces[1][l][i];
					faces[1][l][i] = faces[1][CUBE_SIZE - 1 - i][l];
					faces[1][CUBE_SIZE - 1 - i][l] = faces[1][CUBE_SIZE - 1 - l][CUBE_SIZE - 1 - i];
					faces[1][CUBE_SIZE - 1 - l][CUBE_SIZE - 1 - i] = faces[1][i][CUBE_SIZE - 1 - l];
					faces[1][i][CUBE_SIZE - 1 - l] = t[i];
				}
			}
		}
	}

	void left_anticlock() {

		int t[CUBE_SIZE];

		FOR0(i, CUBE_SIZE) {
			t[i] = faces[4][CUBE_SIZE - 1 - i][layer];
			faces[4][CUBE_SIZE - 1 - i][layer] = faces[0][CUBE_SIZE - 1 - i][layer];
			faces[0][CUBE_SIZE - 1 - i][layer] = faces[5][CUBE_SIZE - 1 - i][layer];
			faces[5][CUBE_SIZE - 1 - i][layer] = faces[1][i][CUBE_SIZE - 1 - layer];
			faces[1][i][CUBE_SIZE - 1 - layer] = t[i];
		}

		if (layer == 0) {
			FOR0(l, CUBE_SIZE / 2) {
				FOR(i, l, CUBE_SIZE - 2 - l) {
					t[i] = faces[2][l][CUBE_SIZE - 1 - i];
					faces[2][l][CUBE_SIZE - 1 - i] = faces[2][CUBE_SIZE - 1 - i][CUBE_SIZE - 1 - l];
					faces[2][CUBE_SIZE - 1 - i][CUBE_SIZE - 1 - l] = faces[2][CUBE_SIZE - 1 - l][i];
					faces[2][CUBE_SIZE - 1 - l][i] = faces[2][i][l];
					faces[2][i][l] = t[i];
				}
			}
		}
	}

	void left_clock() {

		int t[CUBE_SIZE];

		FOR0(i, CUBE_SIZE) {
			t[i] = faces[4][i][layer];
			faces[4][i][layer] = faces[1][CUBE_SIZE - 1 - i][CUBE_SIZE - 1 - layer];
			faces[1][CUBE_SIZE - 1 - i][CUBE_SIZE - 1 - layer] = faces[5][i][layer];
			faces[5][i][layer] = faces[0][i][layer];
			faces[0][i][layer] = t[i];
		}

		if (layer == 0) {
			FOR0(l, CUBE_SIZE / 2) {
				FOR(i, l, CUBE_SIZE - 2 - l) {
					t[i] = faces[2][l][i];
					faces[2][l][i] = faces[2][CUBE_SIZE - 1 - i][l];
					faces[2][CUBE_SIZE - 1 - i][l] = faces[2][CUBE_SIZE - 1 - l][CUBE_SIZE - 1 - i];
					faces[2][CUBE_SIZE - 1 - l][CUBE_SIZE - 1 - i] = faces[2][i][CUBE_SIZE - 1 - l];
					faces[2][i][CUBE_SIZE - 1 - l] = t[i];
				}
			}
		}

	}

	void right_anticlock() {

		int t[CUBE_SIZE];

		FOR0(i, CUBE_SIZE) {
			t[i] = faces[4][i][CUBE_SIZE - 1 - layer];
			faces[4][i][CUBE_SIZE - 1 - layer] = faces[1][CUBE_SIZE - 1 - i][layer];
			faces[1][CUBE_SIZE - 1 - i][layer] = faces[5][i][CUBE_SIZE - 1 - layer];
			faces[5][i][CUBE_SIZE - 1 - layer] = faces[0][i][CUBE_SIZE - 1 - layer];
			faces[0][i][CUBE_SIZE - 1 - layer] = t[i];
		}

		if (layer == 0) {
			FOR0(l, CUBE_SIZE / 2) {
				FOR(i, l, CUBE_SIZE - 2 - l) {
					t[i] = faces[3][l][CUBE_SIZE - 1 - i];
					faces[3][l][CUBE_SIZE - 1 - i] = faces[3][CUBE_SIZE - 1 - i][CUBE_SIZE - 1 - l];
					faces[3][CUBE_SIZE - 1 - i][CUBE_SIZE - 1 - l] = faces[3][CUBE_SIZE - 1 - l][i];
					faces[3][CUBE_SIZE - 1 - l][i] = faces[3][i][l];
					faces[3][i][l] = t[i];
				}
			}
		}

	}

	void right_clock() {

		int t[CUBE_SIZE];

		FOR0(i, CUBE_SIZE) {
			t[i] = faces[4][CUBE_SIZE - 1 - i][CUBE_SIZE - 1 - layer];
			faces[4][CUBE_SIZE - 1 - i][CUBE_SIZE - 1 - layer] = faces[0][CUBE_SIZE - 1 - i][CUBE_SIZE - 1 - layer];
			faces[0][CUBE_SIZE - 1 - i][CUBE_SIZE - 1 - layer] = faces[5][CUBE_SIZE - 1 - i][CUBE_SIZE - 1 - layer];
			faces[5][CUBE_SIZE - 1 - i][CUBE_SIZE - 1 - layer] = faces[1][i][layer];
			faces[1][i][layer] = t[i];
		}

		if (layer == 0) {
			FOR0(l, CUBE_SIZE / 2) {
				FOR(i, l, CUBE_SIZE - 2 - l) {
					t[i] = faces[3][l][i];
					faces[3][l][i] = faces[3][CUBE_SIZE - 1 - i][l];
					faces[3][CUBE_SIZE - 1 - i][l] = faces[3][CUBE_SIZE - 1 - l][CUBE_SIZE - 1 - i];
					faces[3][CUBE_SIZE - 1 - l][CUBE_SIZE - 1 - i] = faces[3][i][CUBE_SIZE - 1 - l];
					faces[3][i][CUBE_SIZE - 1 - l] = t[i];
				}
			}
		}

	}

	void up_anticlock() {

		int t[CUBE_SIZE];

		FOR0(i, CUBE_SIZE) {
			t[i] = faces[1][layer][i];
			faces[1][layer][i] = faces[3][layer][i];
			faces[3][layer][i] = faces[0][layer][i];
			faces[0][layer][i] = faces[2][layer][i];
			faces[2][layer][i] = t[i];
		}

		if (layer == 0) {
			FOR0(l, CUBE_SIZE / 2) {
				FOR(i, l, CUBE_SIZE - 2 - l) {
					t[i] = faces[4][l][CUBE_SIZE - 1 - i];
					faces[4][l][CUBE_SIZE - 1 - i] = faces[4][CUBE_SIZE - 1 - i][CUBE_SIZE - 1 - l];
					faces[4][CUBE_SIZE - 1 - i][CUBE_SIZE - 1 - l] = faces[4][CUBE_SIZE - 1 - l][i];
					faces[4][CUBE_SIZE - 1 - l][i] = faces[4][i][l];
					faces[4][i][l] = t[i];
				}
			}
		}
	}

	void up_clock() {

		int t[CUBE_SIZE];

		FOR0(i, CUBE_SIZE) {
			t[i] = faces[1][layer][CUBE_SIZE - 1 - i];
			faces[1][layer][CUBE_SIZE - 1 - i] = faces[2][layer][CUBE_SIZE - 1 - i];
			faces[2][layer][CUBE_SIZE - 1 - i] = faces[0][layer][CUBE_SIZE - 1 - i];
			faces[0][layer][CUBE_SIZE - 1 - i] = faces[3][layer][CUBE_SIZE - 1 - i];
			faces[3][layer][CUBE_SIZE - 1 - i] = t[i];
		}

		if (layer == 0) {
			FOR0(l, CUBE_SIZE / 2) {
				FOR(i, l, CUBE_SIZE - 2 - l) {
					t[i] = faces[4][l][i];
					faces[4][l][i] = faces[4][CUBE_SIZE - 1 - i][l];
					faces[4][CUBE_SIZE - 1 - i][l] = faces[4][CUBE_SIZE - 1 - l][CUBE_SIZE - 1 - i];
					faces[4][CUBE_SIZE - 1 - l][CUBE_SIZE - 1 - i] = faces[4][i][CUBE_SIZE - 1 - l];
					faces[4][i][CUBE_SIZE - 1 - l] = t[i];
				}
			}
		}
	}

	void down_anticlock() {

		int t[CUBE_SIZE];

		FOR0(i, CUBE_SIZE) {
			t[i] = faces[0][CUBE_SIZE - 1 - layer][CUBE_SIZE - 1 - i];
			faces[0][CUBE_SIZE - 1 - layer][CUBE_SIZE - 1 - i] = faces[3][CUBE_SIZE - 1 - layer][CUBE_SIZE - 1 - i];
			faces[3][CUBE_SIZE - 1 - layer][CUBE_SIZE - 1 - i] = faces[1][CUBE_SIZE - 1 - layer][CUBE_SIZE - 1 - i];
			faces[1][CUBE_SIZE - 1 - layer][CUBE_SIZE - 1 - i] = faces[2][CUBE_SIZE - 1 - layer][CUBE_SIZE - 1 - i];
			faces[2][CUBE_SIZE - 1 - layer][CUBE_SIZE - 1 - i] = t[i];
		}

		if (layer == 0) {
			FOR0(l, CUBE_SIZE / 2) {
				FOR(i, l, CUBE_SIZE - 2 - l) {
					t[i] = faces[5][l][CUBE_SIZE - 1 - i];
					faces[5][l][CUBE_SIZE - 1 - i] = faces[5][CUBE_SIZE - 1 - i][CUBE_SIZE - 1 - l];
					faces[5][CUBE_SIZE - 1 - i][CUBE_SIZE - 1 - l] = faces[5][CUBE_SIZE - 1 - l][i];
					faces[5][CUBE_SIZE - 1 - l][i] = faces[5][i][l];
					faces[5][i][l] = t[i];
				}
			}
		}

	}

	void down_clock() {

		int t[CUBE_SIZE];

		FOR0(i, CUBE_SIZE) {
			t[i] = faces[0][CUBE_SIZE - 1 - layer][i];
			faces[0][CUBE_SIZE - 1 - layer][i] = faces[2][CUBE_SIZE - 1 - layer][i];
			faces[2][CUBE_SIZE - 1 - layer][i] = faces[1][CUBE_SIZE - 1 - layer][i];
			faces[1][CUBE_SIZE - 1 - layer][i] = faces[3][CUBE_SIZE - 1 - layer][i];
			faces[3][CUBE_SIZE - 1 - layer][i] = t[i];
		}

		if (layer == 0) {
			FOR0(l, CUBE_SIZE / 2) {
				FOR(i, l, CUBE_SIZE - 2 - l) {
					t[i] = faces[5][l][i];
					faces[5][l][i] = faces[5][CUBE_SIZE - 1 - i][l];
					faces[5][CUBE_SIZE - 1 - i][l] = faces[5][CUBE_SIZE - 1 - l][CUBE_SIZE - 1 - i];
					faces[5][CUBE_SIZE - 1 - l][CUBE_SIZE - 1 - i] = faces[5][i][CUBE_SIZE - 1 - l];
					faces[5][i][CUBE_SIZE - 1 - l] = t[i];
				}
			}
		}

	}

	bool operator<(const State& rhs) const {

		FOR0(k, 6) {
			FOR0(j, CUBE_SIZE) {
				FOR0(i, CUBE_SIZE) {
					if (faces[k][j][i] != rhs.faces[k][j][i])
						return faces[k][j][i] < rhs.faces[k][j][i];
				}
			}
		}
		return false;

	}

	bool operator>(const State& rhs) const {

		FOR0(k, 6) {
			FOR0(j, 3) {
				FOR0(i, 3) {
					if (faces[k][j][i] != rhs.faces[k][j][i])
						return faces[k][j][i] > rhs.faces[k][j][i];
				}
			}
		}
		return false;
	}

	bool operator==(const State& rhs) const {

		FOR0(k, 6) {
			FOR0(j, 3) {
				FOR0(i, 3) {
					if (faces[k][j][i] != rhs.faces[k][j][i])
						return false;
				}
			}
		}
		return true;
	}


};

//klasa button napravljena za olaksano baratanje sa dugmicima u boji i sa tekstom

class button {
	static float x_par_butt; 
	static float y_par_butt;
	static float clickdelay;
public:
	bool isAnimating;
	float x, y;
	float xoff, yoff;
	float w, h;
	color bg, fg;
	 
	string text;

	button() {
		isAnimating = false;
		x = 0;
		y = 0;
		xoff = yoff = 0;
		w = 1;
		h = 0.35;
		bg = color(0.9, 0.9, 0.9);
		fg = color(0, 0, 0);
		text = "Button";
	}

	button(float px, float py, float iw, float ih) {
		x = px;
		y = py;
		w = iw;
		h = ih;
		isAnimating = false;
		xoff = yoff = 0;
		bg = color(0.9, 0.9, 0.9);
		fg = color(0, 0, 0);
		text = "Button";
	}

	button(float px, float py, float iw, float ih, color background, color foreground, string disptext) {
		x = px;
		y = py;
		w = iw;
		h = ih;
		isAnimating = false;
		bg = background;
		fg = foreground;
		text = disptext;
		xoff = yoff = 0;
	}

	//iscrtavanje dugmeta

	void draw() {

		glColor3fv(bg.getArray());
		glBegin(GL_POLYGON);
		glVertex3f(x + xoff, y + yoff, 1);
		glVertex3f(x + w + xoff, y + yoff, 1);
		glVertex3f(x + w + xoff, y - h + yoff, 1);
		glVertex3f(x + xoff, y - h + yoff, 1);
		glEnd();

		
			// deo iznad dugmeta koji stvara 3d efekat
			glColor3f(0.3, 0.3, 0.3);
			glBegin(GL_POLYGON);
			glVertex3f(x + xoff, y + yoff, 1);
			glVertex3f(x + w + xoff, y + yoff, 1);
			glVertex3f(x + w + x_par_butt, y + y_par_butt, 0);
			glVertex3f(x + x_par_butt, y + y_par_butt, 0);
			glEnd();

			// deo desno od dugmeta koji stvara 3d efekat
			glColor3f(0.2, 0.2, 0.2);
			glBegin(GL_POLYGON);
			glVertex3f(x + w + xoff, y + yoff, 1);
			glVertex3f(x + w + x_par_butt, y + y_par_butt, 0);
			glVertex3f(x + w + x_par_butt, y - h + y_par_butt, 0);
			glVertex3f(x + w + xoff, y - h + yoff, 1);
			glEnd();
		

		glPushMatrix();
		glTranslatef(x + xoff + (w - text.size() * 0.135) / 2, y + yoff - (h + 0.12) / 2, 1.1);
		glScalef(1 / 800.0, 1 / 800.0, 0);
		glLineWidth(2);
		glColor3fv(fg.getArray());

		FOR0(i, text.size())
			glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, text[i]);
		glPopMatrix();

	}

	bool collision(float px, float py) {
		if (!isAnimating && px > x + xoff && px<x + w + xoff && py>y - h + yoff && py < y + yoff)
			return true;
		return false;
	}

	//animacija pritiskanja dugmeta prilikom pritiskanja istog
	void animate(void actionEvent()) {

		if (isAnimating) {
			xoff += x_par_butt / clickdelay;
			yoff += y_par_butt / clickdelay;

			if (xoff + x >= x + x_par_butt) {
				isAnimating = false;
				actionEvent();
			}
		}
		else {
			xoff = 0;
			yoff = 0;
		}
	}

};


//definisanje eksternih koje delimo (sharedvars)

extern button butt_start;
extern button butt_exit;
extern button butt_resi;
extern button butt_nazad;



extern State kocka;
extern bool isTransition;
extern bool change;
extern bool isMousePressed;
extern vector<char> moveList;

extern vector<tacka> rotationQueue;
extern Quaterniond cubesRotation[CUBE_SIZE][CUBE_SIZE][CUBE_SIZE];
extern Vector3d rotationAxis;
extern double totalRotation;
extern int rotationType;
extern const double PI; // = 3.14
extern double* matrix;

extern float xscreen;
extern float yscreen;
extern double rorationSpeed;
extern float viewportX;
extern float viewportY;
extern int width;
extern int height;
extern float camX;
extern float camY;
extern float camZ;
extern float fromXScreen;
extern float fromYScreen;
extern float toXScreen;
extern float toYScreen;
extern Quaterniond camera;

extern double brzina;
extern float perc;

extern int px;
extern int py;







#endif 
