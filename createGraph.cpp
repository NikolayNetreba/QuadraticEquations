#define TX_COMPILED
#include "TXLib.h"
#include "createGraph.h"
#include "calc.h"
#include <stdio.h>
#include <assert.h>

const double initialScale = 25;
const int shift = 25;
const COLORREF blue = RGB(0, 191, 255);
const int buffSize = 20;

void crateGraph(coeff* eqCoeff) {
    assert(eqCoeff != NULL);

    double xv = -eqCoeff->b / (2 * eqCoeff->a), yv = find_y(eqCoeff, xv);
    screenParams screen = {
    .Width = txGetExtentX(),       .Height = txGetExtentY(),
    .halfWidth = screen.Width / 2, .halfHeight = screen.Height / 2,
    .scaleX = initialScale,        .scaleY = initialScale,
    };

    txCreateWindow(screen.Width, screen.Height);
    txClearConsole();

    calculate_scale(xv, yv, &screen);

    txSetColor(TX_WHITE, 1);
    creatLine(screen);
    while(!txGetAsyncKeyState(VK_ESCAPE)) {
        draw_graph(screen, eqCoeff);

        bool flag = change_scale(&screen.scaleX, &screen.scaleY);
        if (flag) {
            txSetFillColor(TX_BLACK);
            txClear();

            creatLine(screen);
            flag = false;
        }
    }

}

void draw_graph(screenParams screen, coeff* eqCoeff) {
    assert(eqCoeff != NULL);

    for(double x = -screen.Width; x < screen.Width; x += 0.01) {
        double y = find_y(eqCoeff, x);
        txSetPixel(x * screen.scaleX + screen.Width / 2, -y * screen.scaleY + screen.Height / 2, blue);
    }
}

void creatLine(screenParams screen) {
    txLine(0, screen.halfHeight, screen.Width, screen.halfHeight);
    txLine(screen.halfWidth, 0, screen.halfWidth, screen.Height);

    print_scale(screen.scaleX, screen.scaleY);

    txTextOut(screen.halfWidth - shift, screen.halfHeight + shift, "0");
    draw_axes(screen);
}

void draw_axes(screenParams screen) {
    const int stepX = (int)screen.Width / 6, stepY = (int)screen.Height / 6;
    char buffer[buffSize] = {}, negBuffer[buffSize] = {};

    for (int x = (int)screen.halfWidth + stepX, y = (int)screen.halfHeight + stepY, cnt = 1; cnt < 3;
    x += stepX, y += stepY, cnt += 1){
        //draw X axis
        int number = (int)round((x - screen.halfWidth) / screen.scaleX);
        snprintf(buffer, sizeof(buffer), "%i", number);
        snprintf(negBuffer, sizeof(negBuffer), "%i", -number);

        txTextOut(x, screen.halfHeight + shift, buffer);
        txTextOut(x - cnt * 2 * stepX, screen.halfHeight + shift, negBuffer);

        //draw Y axis
        number = (int)round((y - screen.halfHeight) / screen.scaleY);
        snprintf(buffer, sizeof(buffer), "%i", number);
        snprintf(negBuffer, sizeof(negBuffer), "%i", -number);

        txTextOut(screen.halfWidth - shift, y, negBuffer);
        txTextOut(screen.halfWidth - shift, y - cnt * 2 * stepY, buffer);
    }
}

void print_scale(double scaleX, double scaleY){
    char bufferX[buffSize] = {}, bufferY[buffSize] = {};
    snprintf(bufferX, sizeof(bufferX), "scaleX: %lf", round(scaleX * 100) / 100);
    snprintf(bufferY, sizeof(bufferY), "scaleY: %lf", round(scaleY * 100) / 100);

    txTextOut(25, 25, bufferX);
    txTextOut(25, 50, bufferY);
}

void calculate_scale(double xv, double yv, screenParams* screen) {
    assert(screen != NULL);

    double maxX = screen->halfWidth * 0.5;
    double maxY = screen->halfHeight * 0.5;

    if (fabs(xv) > maxX) {
        screen->scaleX = maxX / fabs(xv);
    }

    if (fabs(yv) > maxY) {
        screen->scaleY = maxY / fabs(yv);
    }
}

bool change_scale(double* scaleX, double* scaleY) {
    assert(scaleX != NULL);
    assert(scaleY != NULL);

    bool fl = false;
    if(txGetAsyncKeyState(VK_RIGHT)) {
        (*scaleX) *= 1.5;
        fl = true;
    }
    if(txGetAsyncKeyState(VK_LEFT)) {
        (*scaleX) /= 1.5;
        fl = true;
    }
    if(txGetAsyncKeyState(VK_DOWN)) {
        (*scaleY) /= 1.5;
        fl = true;
    }
    if(txGetAsyncKeyState(VK_UP)) {
        (*scaleY) *= 1.5;
        fl = true;
    }

    return fl;
}

double find_y(coeff* eqCoeff, double x) {
    return eqCoeff->a * x * x + eqCoeff->b*x + eqCoeff->c;
}
