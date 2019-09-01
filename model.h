#ifndef MODEL_H
#define MODEL_H

#include "var.h"

//funkcije iscrtavanja i animacija objekata

void draw_part(float* a, float* b, float* c, float* d, int face);

void drawCube(float* a, float* b, float* c, float* d,
	float* e, float* f, float* g, float* h,
	int x, int y, int z);

void buildRubiksCube();

void animateButtons();

void doTransition(float fromX, float toX, float fromY, float toY);

void komande();

void prikazi_resenje();

#endif
