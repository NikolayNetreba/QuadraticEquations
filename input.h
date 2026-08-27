#ifndef INPUT_H
#define INPUT_H

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

void scan_op(opChoose *op);
opYN scan_yes_or_no();
void choose_option(opChoose *op);
void scan_coefficient(coeff *eqCoeff);
FILE *scan_file_name(void);
opStatus input_coefficients(coeff* eqCoeff);
opStatus read_from_file(coeff *eqCoeff, FILE *file);
int check_and_clear_buffer();
void clear_buffer();
void handle_op_status(coeff eqCoeff, opStatus* state);
#endif

