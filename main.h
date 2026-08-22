#pragma once
/**
 @file
 @brief Программа для решения квадратных и линейных уравнений.
 @details Включает считывание коэффициентов с клавиатуры, очистку буфера ввода,
 вычисление дискриминанта и обработку всех частных случаев (включая равенство нулю).
*/

#include "colors.h"
#include "calc.h"
#include "input.h"
#include "output.h"
#include <stdlib.h>
#include <windows.h>


/**
 @brief Отлов ошибок пользователя.
 @param [in] condition Проверяемое условие.
 @param [in] message Сообщение об ошибке.
*/
#define verify_it(condition, message) \
    if (!(condition)) { \
        printf(message); \
        abort(); \
    }



