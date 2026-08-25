#define WIN32_LEAN_AND_MEAN
#include "TXLib.h"
#include <stdio.h>
#include <assert.h>

#define verify_it(condition, message)\
        if(!(condition)){\
            printf(stderr, "file: %s, lint: %d, fall: %s", __FILE__, __LINE__, message);\
        }

double is_it_dot(double a, double b, double c, double x){
    return a*x*x + b*x + c;
}

bool is_it_in(double xv, double yv){
    long X = txGetExtentX();
    long Y = txGetExtentY();
    if (xv < 0 || xv > X)
        return false;
    if (yv < 0 || yv > Y)
        return false;
    return true;
}

void set_scale(double* scale, double a, double b, double c, double xv, double yv){
    while(!is_it_in(xv * *scale, yv * *scale)){
        *scale /= 5;
    }
}

int main(){
    double a = 1, b = 100, c = 100;
    double xv = -b / (2 * a), yv = is_it_dot(a, b, c, xv);
    double scale = 1;
    POINT sizeOfWindow = txGetExtent();
    double pX = sizeOfWindow.x / 2, pY  = sizeOfWindow.y / 2;
    set_scale(&scale, a, b, c, xv + pX, -yv + pY);
    txCreateWindow(sizeOfWindow.x, sizeOfWindow.y);
    txClearConsole();
    txSetColor(TX_WHITE, 1);
    txLine(0, sizeOfWindow.y / 2, sizeOfWindow.x, sizeOfWindow.y / 2);
    txLine(sizeOfWindow.x / 2, 0, sizeOfWindow.x / 2, sizeOfWindow.y);

    for(double x = -(1920 / 2); x < (1920 / 2); x += 0.08){
        double y = is_it_dot(a, b, c, x);
        txSetPixel(x * scale + pX, -y * scale + pY, TX_PINK);
    }
}



