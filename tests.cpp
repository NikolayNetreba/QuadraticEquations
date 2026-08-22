#include "tests.h"


int main(){
    FILE* file = scan_file_name();
    start_unit_tests(file);
}

opStatus read_from_unit_tests(double *a, double *b, double *c,
                              int* nRootsRef, double* x1Ref, double* x2Ref,
                              FILE *file, int* scanCount) {
  assert(a != NULL);
  assert(b != NULL);
  assert(c != NULL);
  assert(file != NULL && "Path is null");

  *scanCount = fscanf(file, "%lf%lf%lf%d%lf%lf", a, b, c, nRootsRef, x1Ref, x2Ref);
  printf("for bug %lg %lg %lg %d %lg %lg", *a, *b, *c, *nRootsRef, *x1Ref, *x2Ref);
  if (*scanCount == -1) {
    printf("EOF");
    return OP_STATUS_EXIT;
  }
  if (*scanCount != 6 && *scanCount != 5) {
    printf(MAKE_RED("insufficient variables entered, do it again.\n")"-------------------------------------------------\n");
    return OP_STATUS_DO_IT_AGAIN;
  }
  return OP_STATUS_OK;
}

void start_unit_tests(FILE* file){
    opStatus state = OP_STATUS_EXIT;
    do{
        double a = 0, b = 0, c = 0, x1 = 0, x2 = 0, x1Ref = 0, x2Ref = 0;
        int nRootsRef = 0, scanCount = 0;
        roots nRoots = ZERO_ROOTS;
        state = read_from_unit_tests(&a, &b, &c, &nRootsRef, &x1Ref, &x2Ref, file, &scanCount);
        nRoots = solve_quadratic_equations(a, b, c, &x1, &x2);

        if (scanCount == 5){
            if (nRoots == TWO_ROOTS){
                printf(MAKE_RED("Test FAILED:")"a = %lg, b = %lg, c = %lg,"
                MAKE_YELLOW("Expected:") " %d roots, x1 = %lg, x2 = noRoot, "
                "got: %d roots, x1 = %lg, x2 = %lg\n-------------------------------------------------\n", a, b, c, nRootsRef, x1Ref, nRoots, x1, x2);
            } else {
                if (nRoots != nRootsRef || !is_zero(fabs(x1Ref - x1))){
                    printf(MAKE_RED("Test FAILED:")"a = %lg, b = %lg, c = %lg,"
                MAKE_YELLOW("Expected:") " %d roots, x1 = %lg, x2 = noRoot, "
                "got: %d roots, x1 = %lg, x2 = %lg\n-------------------------------------------------\n", a, b, c, nRootsRef, x1Ref, nRoots, x1, x2);
                }
            }
        } else if (scanCount == 6) {
            if (nRoots == ONE_ROOT){
                printf(MAKE_RED("Test FAILED:")"a = %lg, b = %lg, c = %lg,"
                MAKE_YELLOW("Expected:") " %d roots, x1 = %lg, x2 = %lg, "
                "got: %d roots, x1 = %lg, x2 = noRoot\n-------------------------------------------------\n", a, b, c, nRootsRef, x1Ref, x2Ref, nRoots, x1);
            } else {
                if (nRoots != nRootsRef ||\
                    !((is_zero(fabs(x1Ref - x1)) && is_zero(fabs(x2Ref - x2))) ||\
                    (is_zero(fabs(x1Ref - x2)) && is_zero(fabs(x2Ref - x1))))){
                    printf(MAKE_RED("Test FAILED:")"a = %lg, b = %lg, c = %lg,"
                           MAKE_YELLOW("Expected:") " %d roots, x1 = %lg, x2 = %lg, "
                           "got: %d roots, x1 = %lg, x2 = %lg\n-------------------------------------------------\n", a, b, c, nRootsRef, x1Ref, x2Ref, nRoots, x1, x2);
                }
            }
        } else {
            printf("pass\n");
        }
    } while(state != OP_STATUS_EXIT);
    fclose(file);
}
