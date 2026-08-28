#ifndef STRUCTURES_H
#define STRUCTURES_H

/**
 @brief
*/
#define EPS 1e-9

#define LINE "-------------------------------------------------\n"

/**
 @brief
*/
typedef enum {
    NO_ROOTS = 0,
    ONE_ROOT = 1,
    TWO_ROOTS = 2,
    INF_ROOTS = -1,
} roots;

struct coeff {
    double a, b, c;
};

struct eqRoots {
    double x1, x2;
    roots nRoots;
};

typedef enum {
    OP_STATUS_OK = 0,
    OP_STATUS_EXIT = 1,
    OP_STATUS_TEST = 2,
    OP_STATUS_IMPOSSIBLE = 3,
    OP_STATUS_DO_IT_AGAIN = 4
} opStatus;

#endif
