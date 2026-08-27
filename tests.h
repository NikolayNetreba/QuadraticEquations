#ifndef TESTS_H
#define TESTS_H

#include "structures.h"

#define END_SCAN_COUNT -1
#define FILE_SCAN_COUNT 6

void start_tests() ;
void do_unit_tests(FILE* file);
opStatus read_from_unit_tests(coeff *eqCoeff, EqRoots *RefRootsOfEq, FILE *file);
opStatus process_scan_count(int scanCount);
bool is_success(EqRoots RootsOfEq, EqRoots RefRootsOfEq);
void print_unit_result(int index, coeff eqCoeff, EqRoots RefRootsOfEq,
                    EqRoots RootsOfEq, int success);
void choose_value(int *value, const char *message);
void do_stress_tests(const int range, const int count);
void print_stress_test_result(int index, coeff eqCoeff, EqRoots rootsOfEq, int success);
bool check_stress_tests(coeff eqCoeff, EqRoots rootsOfEq);
#endif
