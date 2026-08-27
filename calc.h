#ifndef CALC_H
#define CALC_H

#include "structures.h"

/**
 @brief Главная функция-диспетчер для решения квадратного уравнения
 @param [in] a Коэффициент при x^2.
 @param [in] b Коэффициент при x.
 @param [in] c Свободный член.
 @param [out] x1 Указатель для записи первого корня.
 @param [out] x2 Указатель для записи второго корня.
 @return Статус решения из перечисления #roots.
*/
roots solve_quadratic_equations(coeff eqCoeff, EqRoots *rootsOfEq);

/**
 @brief Функция для решения уравнений линейного вида.
*/
roots solve_linear(coeff eqCoeff, EqRoots *rootsOfEq);

/**
 @brief Функция для решения уравнений квадратного вида.
*/
roots solve_square(coeff eqCoeff, EqRoots *rootsOfEq);

/**
 @brief Проверяет равно ли число 0 с учетом погрешности EPS
*/
bool is_zero (const double val);

/**
 @brief Подсчитывает дискриминант квадратного уравнения.
*/
double find_discriminant(coeff eqCoeff);

bool is_equal(double a, double b);
#endif

