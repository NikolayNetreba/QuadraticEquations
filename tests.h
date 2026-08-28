#ifndef TESTS_H
#define TESTS_H

#include "structures.h"

#define END_SCAN_COUNT -1
#define FILE_SCAN_COUNT 6

void start_tests() ;
void do_unit_tests(FILE* file);
opStatus read_from_unit_tests(coeff *eqCoeff, eqRoots *RefRootsOfEq, FILE *file);
opStatus process_scan_count(int scanCount);
bool is_success(eqRoots RootsOfEq, eqRoots RefRootsOfEq);
void print_unit_result(int index, coeff eqCoeff, eqRoots RefRootsOfEq,
                    eqRoots RootsOfEq, int success);
void choose_value(int *value, const char *message);
void do_stress_tests(const int range, const int count);
void print_stress_test_result(int index, coeff eqCoeff, eqRoots rootsOfEq, int success);
bool check_stress_tests(coeff eqCoeff, eqRoots rootsOfEq);
#endif
