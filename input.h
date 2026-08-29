#ifndef INPUT_H
#define INPUT_H

/**
 @file
 @brief Считывание корней из консоли, из файла
 @details также следить за жизненным циклом программы
 */

#include <stdio.h>
#include <stddef.h>
#include "structures.h"

#define MAX_OP_LEN 100
#define MAX_OP_LEN_STR "99"
#define NUMBER_SCANS 3

// Если хочешь добавить еще опций, не забудь добавить их в scan_op
typedef enum {
    op_console = 'c',
    op_exit = 'e',
    op_file = 'f',
    op_test = 't',
} opChoose;

typedef enum {
    op_yes = 'y',
    op_no = 'n',
} opYN;

/**
 @brief считывает выбор пользователя: консоль, файл, тест, выход
 @param [out] op выбор пользователя
*/
void scan_op(opChoose *op);

/**
 @brief считывает выбор пользователя: рисовать или не рисовать график
 @return выбор пользователя
*/
opYN scan_yes_or_no();

/**
 @brief дает выбор пользователю: консоль, файл, тест, выход
 @param [out] op выбор пользователя
*/
void choose_option(opChoose *op);

/**
 @brief считывает коэффициенты с консоли
 @param [out] eqCoeff введенные коэффициенты уравнения
 */
void scan_coefficient(coeff *eqCoeff);

/**
 @brief считывает имя файла
 @return указатель на файл [FILE]
*/
FILE *scan_file_name(void);

/**
 @brief обрабатывает выбор пользователя из choose_option()
 @param [in] eqCoeff введенные коэффициенты уравнения
 @return жизненный цикл
 */
opStatus input_coefficients(coeff* eqCoeff);

/**
 @brief считывает коэффициенты с файла
 @return введенные коэффициенты
*/
opStatus read_from_file(coeff *eqCoeff, FILE *file);

/**
 @brief очищает буфер и проверяет наличие буфера на мусор
 @return 1 - есть мусор, 0 - нету
 */
int check_and_clear_buffer();

/**
 @brief очищает буфер
 */
void clear_buffer();

/**
 @brief регулирует жизненный цикл программы
 @param [in] eqCoeff введенные коэффициенты уравнения
 @param [out] state жизненный цикл
 */
void handle_op_status(coeff eqCoeff, opStatus* state);
#endif

