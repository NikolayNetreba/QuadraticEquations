#ifndef TESTS_H
#define TESTS_H
#include "calc.h"
#include "input.h"

#define END_SCAN_COUNT -1
#define FILE_SCAN_COUNT 6

void do_unit_tests(FILE* file);
opStatus read_from_unit_tests(double *a, double *b, double *c, int* nRootsRef, double* x1Ref, double* x2Ref, FILE *file);
opStatus to_process_scan_count(int scanCount);
bool is_success(double x1, double x2, double x1Ref, double x2Ref, roots nRoots, int nRootsRef);
void print_unit_result(int index, double a, double b, double c, int nRootsRef,
                  double x1Ref, double x2Ref, roots nRoots, double x1,
                  double x2, int success);
void Choose_value(int *value, const char *message);
void do_stress_tests(const int range, const int count);
void print_stress_test_result(int index, double a, double b, double c, double x1, double x2,roots nRoots, int success);
bool check_stress_tests(const double a, const double b, const double c, const double x1, const double x2, const roots nRoots);

#endif
