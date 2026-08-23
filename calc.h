#ifndef CALC_H
#define CALC_H

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

/**
 @brief Константа для сравнения чисел с плавающей точкой с нулем.
*/
#define EPS 1e-9

/**
 @brief Перечисление статусов и количество корней уравнения.
*/
typedef enum {
    NO_ROOTS = 0,    ///< Уравнение не имеет решений.
    ONE_ROOT = 1,      ///< Уравнение имеет 1 решение.
    TWO_ROOTS = 2,     ///< Уравнение имеет 2 решения.
    INF_ROOTS = -1,   ///< Уравнение имеет бесконечное кол-во корней.
} roots;

/**
 @brief Главная функция-диспетчер для решения квадратного уравнения
 @param [in] a Коэффициент при x^2.
 @param [in] b Коэффициент при x.
 @param [in] c Свободный член.
 @param [out] x1 Указатель для записи первого корня.
 @param [out] x2 Указатель для записи второго корня.
 @return Статус решения из перечисления #roots.
*/
roots solve_quadratic_equations (const double a, const double b, const double c, double* x1, double* x2);

/**
 @brief Функция для решения уравнений линейного вида.
*/
roots solve_linear (const double b, const double c, double* x1);

/**
 @brief Функция для решения уравнений квадратного вида.
*/
roots solve_square (const double a, const double b, const double c, double* x1, double* x2);

/**
 @brief Проверяет равно ли число 0 с учетом погрешности EPS
*/
bool is_zero (const double val);

/**
 @brief Подсчитывает дискриминант квадратного уравнения.
*/
double find_discriminant (const double a, const double b, const double c);

bool is_equal(double a, double b);
#endif

