#ifndef FUNC_H
#define FUNC_H


#include "var.h"

//funkcije za rad samog programa


void stampaj(float x, float y, string text, float size);

void enableTransition();

void exitProgram();

void pronadji_resenje(vector<char>& potezi);

void resi();

void prState();

double radian(double deg);

double* getRotMatrix(Quaterniond& q);

void novaRot();




#endif 