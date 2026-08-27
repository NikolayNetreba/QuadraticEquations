#define TX_COMPILED
#include "TXLib.h"
#include "createGraph.h"
#include "calc.h"
#include <stdio.h>
#include <assert.h>

void crateGraph(coeff eqCoeff) {
    double a = eqCoeff.a, b = eqCoeff.b, c = eqCoeff.c;
    double xv = -b / (2 * a), yv = is_it_dot(a, b, c, xv);

    POINT sizeOfWindow = txGetExtent();
    double halfX = sizeOfWindow.x / 2, halfY  = sizeOfWindow.y / 2;
    txCreateWindow(sizeOfWindow.x, sizeOfWindow.y);
    txClearConsole();

    double scaleX = 25.0;
    double scaleY = 25.0;
    calculate_scale(xv, yv, halfX, halfY, &scaleX, &scaleY);

    txSetColor(TX_WHITE, 1);
    creatLine(sizeOfWindow, halfX, halfY, scaleX, scaleY);
    while(!txGetAsyncKeyState(VK_ESCAPE)) {
        for(double x = -halfX; x < halfX; x += 0.01) {
            double y = is_it_dot(a, b, c, x);
            txSetPixel(x * scaleX + halfX, -y * scaleY + halfY, RGB(0, 191, 255));
        }
        bool fl = change_scale(&scaleX, &scaleY);
        if (fl) {
            txSetFillColor(TX_BLACK);
            txClear();
            creatLine(sizeOfWindow, halfX, halfY, scaleX, scaleY);
            //printf("X = %lf, Y = %lf", scaleX, scaleY);
            fl = false;
        }
    }

}

void printScale(double scaleX, double scaleY){
    char bufferX[20], bufferY[20];
    snprintf(bufferX, sizeof(bufferX), "scaleX: %lf", round(scaleX * 100) / 100);
    snprintf(bufferY, sizeof(bufferY), "scaleY: %lf", round(scaleY * 100) / 100);

    txTextOut(25, 25, bufferX);
    txTextOut(25, 50, bufferY);
}

void calculate_scale(double xv, double yv, double halfX, double halfY, double* scaleX, double* scaleY) {
    assert(scaleX != NULL);
    assert(scaleY != NULL);

    double maxX = halfX * 0.5;
    double maxY = halfY * 0.5;

    if (fabs(xv) > maxX) {
        *scaleX = maxX / fabs(xv);
    }

    if (fabs(yv) > maxY) {
        *scaleY = maxY / fabs(yv);
    }
}

bool change_scale(double* scaleX, double* scaleY) {
    assert(scaleX != NULL);
    assert(scaleY != NULL);

    bool fl = false;
    if(txGetAsyncKeyState(VK_UP)) {
        (*scaleX) *= 1.5;
        fl = true;
    }
    if(txGetAsyncKeyState(VK_DOWN)) {
        (*scaleX) /= 1.5;
        fl = true;
    }
    if(txGetAsyncKeyState(VK_LEFT)) {
        (*scaleY) /= 1.5;
        fl = true;
    }
    if(txGetAsyncKeyState(VK_RIGHT)) {
        (*scaleY) *= 1.5;
        fl = true;
    }

    return fl;
}

void creatLine(POINT sizeOfWindow, double halfX, double halfY, double scaleX, double scaleY) {
    txLine(0, halfY, sizeOfWindow.x, halfY);
    txLine(halfX, 0, halfX, sizeOfWindow.y);

    printScale(scaleX, scaleY);

    char buffer[20], negBuffer[20];
    txTextOut(halfX - 25, halfY + 25, "0");

    for (int x = int(halfX + (sizeOfWindow.x / 6)), cnt = 1; cnt < 3; x += (int)(sizeOfWindow.x / 6), cnt += 1){
        snprintf(buffer, sizeof(buffer), "%i", (int)round((x - halfX) / scaleX));
        snprintf(negBuffer, sizeof(negBuffer), "%i", -(int)round((x - halfX) / scaleX));
        txTextOut(x, halfY + 25, buffer);
        txTextOut(x - cnt * (sizeOfWindow.x / 3), halfY + 25, negBuffer);

    }
    for (int y = int(halfY + (sizeOfWindow.y / 6)), cnt = 1; cnt < 3; y += (int)(sizeOfWindow.y / 6), cnt += 1){
        snprintf(buffer, sizeof(buffer), "%i", (int)round((y - halfY) / scaleY));
        snprintf(negBuffer, sizeof(negBuffer), "%i", -(int)round((y - halfY) / scaleY));

        txTextOut(halfX - 25, y, negBuffer);
        txTextOut(halfX - 25, y - cnt * (sizeOfWindow.y / 3) , buffer);
    }
}

double is_it_dot(double a, double b, double c, double x) {
    return a*x*x + b*x + c;
}
