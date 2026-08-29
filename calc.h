#ifndef CALC_H
#define CALC_H

/**
 @file
 @brief Отвечает за подсчеты корней
 */

#include "structures.h"

/**
 @brief Главная функция-диспетчер для решения квадратного уравнения
 @param [in] eqCoeff коэффициенты уравнения
 @param [out] rootsOfEq Указатель для записи корней
 @return Статус решения из перечисления #roots.
*/
roots solve_quadratic_equations(coeff eqCoeff, eqRoots *rootsOfEq);

/**
 @brief Функция для решения уравнений линейного вида.
 @param [in] eqCoeff коэффициенты уравнения
 @param [out] rootsOfEq Указатель для записи корней
 @return Статус решения из перечисления #roots
*/
roots solve_linear(coeff eqCoeff, eqRoots *rootsOfEq);

/**
 @brief Функция для решения уравнений квадратного вида.
 @param [in] eqCoeff коэффициенты уравнения
 @param [out] rootsOfEq Указатель для записи корней
 @return Статус решения из перечисления #roots
*/
roots solve_square(coeff eqCoeff, eqRoots *rootsOfEq);

/**
 @brief Проверяет равно ли число 0 с учетом погрешности EPS
*/
bool is_zero (const double val);

/**
 @brief Подсчитывает дискриминант квадратного уравнения.
 @param [in] eqCoeff коэффициенты уравнения
*/
double find_discriminant(coeff eqCoeff);

/**
 @brief Проверяет равны ли элементы
 @param [in] a 1й элемент
 @param [in] b 2й элемент
*/
bool is_equal(double a, double b);

#endif

