#include<stdio.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include"main.h"

int main() {
    double a = 0.0, b = 0.0, c = 0.0;
    int scanCount = 0;
    scanСoefficient(&a, &b, &c, &scanCount);

    double x1 = 0, x2 = 0;
    roots nRoot = solve_quadratic_equations (a, b, c, &x1, &x2);
    print_root (x1, x2, nRoot);
    return 0;
}

void scanСoefficient (double* a, double* b, double* c, int* scanCount) {
    do {
        printf ("Enter the coefficients: a, b, c: ");
        *scanCount = scanf ("%lf%lf%lf", a, b, c);

        if (*scanCount != 3) {
            printf ("insufficient variables entered, do it again.\n");
            clear_the_buffer ();
        }
    } while (*scanCount != 3);
}

void clear_the_buffer () {
    int trash = 0;
    while ((trash = getchar ()) != '\n' && trash != EOF);
}

bool is_zero (const double val) {
    return fabs (val) < EPS;
}

double find_discriminant (const double a, const double b, const double c) {
    return b * b - 4 * a * c;
}

void print_root (const double x1, const double x2, const roots nRoot) {
    switch(nRoot) {
        case ZERO:
            printf ("zero root, x1 = x2 = none");
            break;
        case ONE:
            printf ("one root, x1 = x2 = %g", x1);
            break;
        case TWO:
            printf ("two root, x1 = %g x2 = %g", x1, x2);
            break;
        case INF:
            printf ("infinite");
            break;
        case ERROR:
            printf ("ERROR");
            break;
        default:
            printf ("IDK");
    }
}

roots solve_linear (const double b, const double c, double* x1) {
    if (is_zero(b) && is_zero(c)) {
        return INF;
    }

    if (is_zero(b)) {
        return ERROR;
    }

    *x1 = -c / b + 0.0;
    return ONE;
}

roots solve_square (const double a, const double b, const double c, double* x1, double* x2) {
    if (is_zero(c)) {
        *x1 = 0;
        *x2 = -b / a + 0.0;
        return TWO;
    }
    double disc = find_discriminant(a, b, c);
    if (disc > 0) {
        double sqDisc = sqrt (disc);
        *x1 = (-b + sqDisc) / (2 * a);
        *x2 = (-b - sqDisc) / (2 * a);
        return TWO;
    }
    if (is_zero(disc)) {
        *x1 = -b / (2 * a) + 0.0;
        return ONE;
    }
    return ZERO;
}

roots solve_quadratic_equations (const double a, const double b, const double c, double* x1, double* x2) {
    assert (x1 != NULL);
    assert (x2 != NULL);
    assert (x1 != x2);

    if (is_zero(a)) {
        return solve_linear (b, c, x1);
    } else {
        return solve_square (a, b, c, x1, x2);
    }
}
