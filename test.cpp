//#include <TXLib.h>
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
    verify_it(0, "hi");


}



