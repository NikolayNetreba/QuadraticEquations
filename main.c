#include<stdio.h>
#include<math.h>
#include<assert.h>
#include"main.h"

enum Roots {

};

int main() {
    double a = 0.0, b = 0.0, c = 0.0;
    int scanCount = 0;
    do {
        printf("Enter the coefficients: a, b, c: ");
        scanCount = scanf("%lf%lf%lf", &a, &b, &c);

        if (scanCount != 3) {
            printf("insufficient variables entered, do it again.\n");
            int ch; // PIZDEC
            while ((ch = getchar()) != '\n' && ch != EOF);
        }
    } while (scanCount != 3);

    double x1 = 0, x2 = 0;
    int nRoot = solve_quadratic_equations (a, b, c, &x1, &x2);
    print_root (x1, x2, nRoot);
    return 0;
}

int is_zero (const double val) {
    return fabs (val) < EPS;
}

double find_disc (const double a, const double b, const double c) {
    return b * b - 4 * a * c;
}

void print_root(double x1, double x2, int nRoot) {
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
        default:
            printf ("ERROR");
    }
}

int solve_linear (const double b, const double c, double* x1) {
    if (is_zero(b) && is_zero(c)) {
        return INF;
    }

    if (is_zero(b)) {
        return ERROR;
    }

    *x1 = -c / b + 0.0;
    return ONE;
}

int solve_square (const double a, const double b, const double c, double* x1, double* x2) {

    if (is_zero(c)) {
        *x1 = 0;
        *x2 = -b / a + 0.0;
        return TWO;
    }
    double disc = find_disc(a, b, c);
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

int solve_quadratic_equations (const double a, const double b, const double c, double* x1, double* x2) {
    assert (x1 != NULL);
    assert (x2 != NULL);

    if (is_zero(a)) {
        return solve_linear (b, c, x1);
    } else {
        return solve_square (a, b, c, x1, x2);
    }
}
