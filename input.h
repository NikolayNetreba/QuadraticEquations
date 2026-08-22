#pragma once

#include "colors.h"
#include "calc.h"
#include "output.h"
#include <stdio.h>
#include <assert.h>
#include <stddef.h>

#define MAX_OP_LEN 100
#define MAX_OP_LEN_STR "99"
#define SCAN_CHECK 3

typedef enum {
    OP_STATUS_EXIT = 400,
    OP_STATUS_OK = 0,
    OP_STATUS_IMPOSSIBLE = 500,
    OP_STATUS_DO_IT_AGAIN = 401
} opStatus;
// Если хочешь добавить еще опций, не забудь добавить их в scan_op
typedef enum {
    op_console = 'c',
    op_exit = 'e',
    op_file = 'f'
} opChoose;

opStatus input_coefficients(double *a, double *b, double *c);
void scan_op(opChoose *op);
void choose_option(opChoose *op);
void scan_coefficient(double *a, double *b, double *c);
FILE *scan_file_name(void);
opStatus read_from_file(double *a, double *b, double *c, FILE *file);
int check_and_clear_buffer(void);
void clear_buffer(void);
void handle_op_status(const double a, const double b, const double c, opStatus* state);


