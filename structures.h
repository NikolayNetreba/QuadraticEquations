#ifndef STRUCTURES_H
#define STRUCTURES_H

/**
 @brief Константа для сравнения чисел с плавающей точкой с нулем.
*/
#define EPS 1e-9

#define LINE "-------------------------------------------------\n"

/**
 @brief Перечисление статусов и количество корней уравнения.
*/
typedef enum {
    NO_ROOTS = 0,    ///< Уравнение не имеет решений.
    ONE_ROOT = 1,      ///< Уравнение имеет 1 решение.
    TWO_ROOTS = 2,     ///< Уравнение имеет 2 решения.
    INF_ROOTS = -1,   ///< Уравнение имеет бесконечное кол-во корней.
} roots;

struct coeff {
    double a, b, c;
};

struct EqRoots {
    double x1, x2;
    roots nRoots;
};

typedef enum {
    OP_STATUS_EXIT = 400,
    OP_STATUS_OK = 0,
    OP_STATUS_TEST = 100,
    OP_STATUS_IMPOSSIBLE = 500,
    OP_STATUS_DO_IT_AGAIN = 401
} opStatus;

#endif
