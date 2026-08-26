#include <TXLib.h>
=======
#define WIN32_LEAN_AND_MEAN
#include "TXLib.h"
>>>>>>> f94cdf3d0fd9a02ae201b3202c25e4cde55a4c08
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <math.h>

#include "structures.h"
#include "colors.h"
// #define NDEBUG

#ifdef NDEBUG
#define verify_it(condition, message) ((void)0)
#else
#define verify_it(condition, message) \
        if (!(condition)){\
        printf(MAKE_YELLOW("%s: %d")" %s\n", __FILE__, __LINE__, message);\
        abort();\
        }
#endif

bool is_zero(const double val) {
  return fabs(val) < EPS;
}

bool is_equal(double a, double b) {
    return is_zero(fabs(a - b));
}

double is_it_dot(double a, double b, double c, double x){
    return a*x*x + b*x + c;
}

int main(){
    txCreateWindow (600, 600);
    txClearConsole()
    double a = 1, b = 0, c = 0;
    for (double x = -2; x < 6; x += 0.00001){
        double y = is_it_dot(a, b, c, x);

        txSetPixel(x * 10 + 300, -y * 10 + 300, RGB(255, 120, 0));
    }


}



