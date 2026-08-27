#ifndef CREATEGRAPH_H
#define CREATEGRAPH_H

#include <windows.h>
#include "structures.h"

void calculate_scale(double xv, double yv, double pX, double pY, double* scaleX, double* scaleY);
bool change_scale(double* scaleX, double* scaleY);
void creatLine(POINT sizeOfWindow, double halfX, double halfY, double scaleX, double scaleY);
void crateGraph(coeff eqCoeff);
double is_it_dot(double a, double b, double c, double x);
void printScale(double scaleX, double scaleY);
#endif
