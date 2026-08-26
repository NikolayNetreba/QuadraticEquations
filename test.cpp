#define WIN32_LEAN_AND_MEAN
#include "TXLib.h"
#include <stdio.h>
#include <assert.h>

#define EPS 1e-9

#define verify_it(condition, message)\
        if(!(condition)){\
            printf(stderr, "file: %s, lint: %d, fall: %s", __FILE__, __LINE__, message);\
        }

double is_it_dot(double a, double b, double c, double x){
    return a*x*x + b*x + c;
}

bool is_zero(const double val) {
  return fabs(val) < EPS;
}

void calculate_scale(double xv, double yv, double pX, double pY, double* scaleX, double* scaleY) {
    double maxX = pX * 0.65;
    double maxY = pY * 0.65;

    if (!is_zero(fabs(xv))) {
        *scaleX = maxX / fabs(xv);
    }

    if (!is_zero(fabs(yv))) {
        *scaleY = maxY / fabs(yv);
    }
}

int main(){
    double a = 1, b = 0, c = 2;
    double xv = -b / (2 * a), yv = is_it_dot(a, b, c, xv);
    POINT sizeOfWindow = txGetExtent();
    double pX = sizeOfWindow.x / 2, pY  = sizeOfWindow.y / 2;
    double scaleX = 1.0;
    double scaleY = 1.0;
    calculate_scale(xv, yv, pX, pY, &scaleX, &scaleY);
    txCreateWindow(sizeOfWindow.x, sizeOfWindow.y);
    txClearConsole();
    txSetColor(TX_WHITE, 1);
    txLine(0, pY, sizeOfWindow.x, pY);
    txLine(pX, 0, pX, sizeOfWindow.y);

    for(double x = -pX; x < pX; x += 0.05){
        double y = is_it_dot(a, b, c, x);
        txSetPixel(x * scaleX + pX, -y * scaleY + pY, RGB(0, 191, 255));
    }
}



