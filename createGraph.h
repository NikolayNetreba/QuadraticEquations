#ifndef CREATEGRAPH_H
#define CREATEGRAPH_H

#include <windows.h>
#include "structures.h"

struct screenParams {
    double width, height;
    double halfWidth, halfHeight;
    double scaleX, scaleY;
};


void calculate_scale(double xv, double yv, screenParams* screen);
bool change_scale(double* scaleX, double* scaleY);
void createLine(screenParams screen);
void createGraph(coeff* eqCoeff, eqRoots* rootsOfEq);
double find_y(coeff* eqCoeff, double x);
void print_scale(double scaleX, double scaleY);
void draw_axes(screenParams screen);
void draw_graph(screenParams screen, coeff* eqCoeff);

#endif /* CREATEGRAPH_H */
