#define TX_COMPILED
#include "TXLib.h"
#include "createGraph.h"
#include "calc.h"
#include <stdio.h>
#include <assert.h>

const double initialScale = 25;
const int shift = 25;
const int buffSize = 20;
const double graphScale = 1.5;
const COLORREF blue = RGB(0, 191, 255);

void createGraph(coeff* eqCoeff, eqRoots* rootsOfEq) {
    assert(eqCoeff);

    double x0 = 0.0, y0 = 0.0;
    // printf("%d", rootsOfEq->nRoots);
    if (rootsOfEq->nRoots == ONE_ROOT){
        x0 = rootsOfEq->x1;
    } else {
        //assert(is_zero(eqCoeff->a));
        x0 = -eqCoeff->b / (2 * eqCoeff->a);
        y0 = find_y(eqCoeff, x0);
    }

    screenParams screen = {
        .width  = txGetExtentX(),
        .height = txGetExtentY(),
        .halfWidth  = screen.width  / 2,
        .halfHeight = screen.height / 2,
        .scaleX = initialScale,
        .scaleY = initialScale,
    };

    txCreateWindow(screen.width, screen.height);
    //txClearConsole();
    calculate_scale(x0, y0, &screen);
    // printf("%d", rootsOfEq->nRoots);

    txSetColor(TX_WHITE, 1);
    createLine(screen);

    while(!txGetAsyncKeyState(VK_ESCAPE)) {
         draw_graph(screen, eqCoeff);
        bool changeFlag = change_scale(&screen.scaleX, &screen.scaleY);
        if (changeFlag) {
            txSetFillColor(TX_BLACK);
            txClear();

            createLine(screen);
            changeFlag = false;
        }
    }
}

void draw_graph(screenParams screen, coeff* eqCoeff) {
    assert(eqCoeff != NULL);

    for(double x = -screen.width; x < screen.width; x += 0.01) {
        double y = find_y(eqCoeff, x);
        txSetPixel(x * screen.scaleX + screen.halfWidth, -y * screen.scaleY + screen.halfHeight, blue);
    }
}

void createLine(screenParams screen) { // create
    txLine(0, screen.halfHeight, screen.width, screen.halfHeight);
    txLine(screen.halfWidth, 0, screen.halfWidth, screen.height);

    print_scale(screen.scaleX, screen.scaleY);

    draw_axes(screen);
}

void draw_axes(screenParams screen) {
    const int stepX = (int)screen.width / 6,
              stepY = (int)screen.height / 6;
    char buffer[buffSize] = {}, negBuffer[buffSize] = {};

    txTextOut(screen.halfWidth - shift, screen.halfHeight + shift, "0");
    for (int x = (int)screen.halfWidth + stepX, y = (int)screen.halfHeight + stepY, cnt = 1; cnt < 3;
    x += stepX, y += stepY, cnt += 1){
        //draw X axis
        int number = (int)round((x - screen.halfWidth) / screen.scaleX);
        snprintf(buffer, sizeof(buffer), "%d", number);
        snprintf(negBuffer, sizeof(negBuffer), "%d", -number);

        txTextOut(x, screen.halfHeight + shift, buffer);
        txTextOut(x - cnt * 2 * stepX, screen.halfHeight + shift, negBuffer);

        //draw Y axis
        number = (int)round((y - screen.halfHeight) / screen.scaleY);
        snprintf(buffer, sizeof(buffer), "%d", number);
        snprintf(negBuffer, sizeof(negBuffer), "%d", -number);

        txTextOut(screen.halfWidth - shift, y, negBuffer);
        txTextOut(screen.halfWidth - shift, y - cnt * 2 * stepY, buffer);
    }
}

void print_scale(double scaleX, double scaleY){
    char bufferX[buffSize] = {}, bufferY[buffSize] = {};
    const int rounding = 100;
    const int shiftX = 25, shiftY = 25;
    snprintf(bufferX, sizeof(bufferX), "scaleX: %lf", round(scaleX * rounding) / rounding);
    snprintf(bufferY, sizeof(bufferY), "scaleY: %lf", round(scaleY * rounding) / rounding);

    txTextOut(shiftX, shiftY, bufferX);
    txTextOut(shiftX, shiftY * 2, bufferY);
}

void calculate_scale(double x0, double y0, screenParams* screen) {
    assert(screen != NULL);

    double maxX = screen->halfWidth * 0.5; // 0.5
    double maxY = screen->halfHeight * 0.5;

    if (fabs(x0) > maxX / screen->scaleX) {
        screen->scaleX = maxX / fabs(x0);
    }

    if (fabs(y0) > maxY / screen->scaleY) {
        screen->scaleY = maxY / fabs(y0);
    }
}

bool change_scale(double* scaleX, double* scaleY) {
    assert(scaleX != NULL);
    assert(scaleY != NULL);

    bool changeFlag = false;
    if(txGetAsyncKeyState(VK_RIGHT)) {
        (*scaleX) *= graphScale;
        changeFlag = true;
    }
    if(txGetAsyncKeyState(VK_LEFT)) {
        (*scaleX) /= graphScale;
        changeFlag = true;
    }
    if(txGetAsyncKeyState(VK_DOWN)) {
        (*scaleY) /= graphScale;
        changeFlag = true;
    }
    if(txGetAsyncKeyState(VK_UP)) {
        (*scaleY) *= graphScale;
        changeFlag = true;
    }

    return changeFlag;
}

double find_y(coeff* eqCoeff, double x) {
    assert(eqCoeff != NULL);
    return eqCoeff->a * x * x + eqCoeff->b * x + eqCoeff->c;
}
