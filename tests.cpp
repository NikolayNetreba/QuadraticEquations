#include "tests.h"

int main() {
    FILE *file = scan_file_name();
    do_unit_tests(file);

    int range = 0;
    Choose_value(&range, "Range");
    int test_count = 0;
    Choose_value(&test_count, "Number of repetitions");
    do_stress_tests(range, test_count);
}

void Choose_value(int *value, const char *message){
    int countScanf = 0;
    do{
    printf(MAKE_YELLOW("Choose the %s: "), message);
    countScanf = scanf("%d", value);
    if (countScanf != 1){
        printf(MAKE_RED("insufficient variables entered, do it again.\n")"-------------------------------------------------\n");
        clear_buffer();
    }
    } while(countScanf != 1);
}

bool check_stress_tests(const double a, const double b, const double c, const double x1, const double x2, const roots nRoots) {
    bool result = false;
    double disc = find_discriminant(a, b, c);
    switch(nRoots){
        case NO_ROOTS:
            result = (is_zero(a) && is_zero(b) && !is_zero(c)) || (disc < 0);
            break;
        case ONE_ROOT:
            result = is_zero(a*x1*x1 + b*x1 + c);
            break;
        case TWO_ROOTS:
            result = is_zero(a*x1*x1 + b*x1 + c) && is_zero(a*x2*x2 + b*x2 + c);
            break;
        case INF_ROOTS:
            result = (is_zero(a) && is_zero(b) && is_zero(c));
            break;
        default:
            break;
    };
    return result;
}

void print_stress_test_result(int index, double a, double b, double c, double x1, double x2,roots nRoots, int success) {
    if (success) {
            printf(MAKE_GREEN("%d Unit test passed\n"), index);
    } else {
        printf("-------------------------------------------------\n"
                MAKE_RED("%d Unit test FAILED: ") "a = %lg, b = %lg, c = %lg,\n"
                MAKE_BLUE("Got: ") "%d roots, x1 = %lg, x2 = %lg\n"
                "-------------------------------------------------\n",
                index, a, b, c, nRoots, x1, x2);
    }
}

void do_stress_tests(const int range, const int count){
    for (int i = 0; i < count;  ++i){
        int a = rand() % range - (range / 2);
        int b = rand() % range - (range / 2);
        int c = rand() % range - (range / 2);

        double x1 = 0, x2 = 0;
        roots nRoots = solve_quadratic_equations(a, b, c, &x1, &x2);
        bool result = check_stress_tests(a, b, c, x1, x2, nRoots);
        print_stress_test_result(i, a, b, c, x1, x2, nRoots, result);
    }
}

opStatus read_from_unit_tests(double *a, double *b, double *c, int *nRootsRef,
                              double *x1Ref, double *x2Ref, FILE *file) {
    assert(a != NULL);
    assert(b != NULL);
    assert(c != NULL);
    assert(nRootsRef != NULL);
    assert(x1Ref != NULL);
    assert(x2Ref != NULL);
    assert(file != NULL && "Path is null");

    int scanCount = fscanf(file, "%lf%lf%lf%d%lf%lf", a, b, c, nRootsRef, x1Ref, x2Ref);
    return to_process_scan_count(scanCount);
}

opStatus to_process_scan_count(int scanCount){
    if (scanCount == END_SCAN_COUNT) {
        printf(MAKE_CYAN("Unit tests completed.\n"));
        return OP_STATUS_EXIT;
    }
    if (scanCount != FILE_SCAN_COUNT) {
        printf(MAKE_RED("insufficient variables entered, do it again.\n")
        "-------------------------------------------------\n");
        clear_buffer();
        return OP_STATUS_DO_IT_AGAIN;
    }
    return OP_STATUS_OK;
}

bool is_success(double x1, double x2, double x1Ref, double x2Ref, roots nRoots, int nRootsRef){
    bool success = (nRoots == nRootsRef);
    if (success && nRoots == 2) {
            success = ((is_equal(x1, x1Ref) && is_equal(x2, x2Ref)) ||
                       (is_equal(x1, x2Ref) && is_equal(x2, x1Ref)));
        } else if (success && nRoots == 1) {
            success = is_equal(x1, x1Ref);
    }

    return success;
}

void print_unit_result(int index, double a, double b, double c, int nRootsRef,
                  double x1Ref, double x2Ref, roots nRoots, double x1,
                  double x2, int success) {
    if (success) {
            printf(MAKE_GREEN("%d Unit test passed\n"), index);
    } else {
        printf("-------------------------------------------------\n"
                MAKE_RED("%d Unit test FAILED: ") "a = %lg, b = %lg, c = %lg,\n"
                MAKE_YELLOW("Expected: ") "%d roots, x1 = %lg, x2 = %lg,\n"
                MAKE_BLUE("Got: ") "%d roots, x1 = %lg, x2 = %lg\n"
                "-------------------------------------------------\n",
                index, a, b, c, nRootsRef, x1Ref, x2Ref, nRoots, x1, x2);
    }
}

void do_unit_tests(FILE *file) {
    opStatus state = OP_STATUS_EXIT;
    int index = 0;
    do {
        index++;
        double a = 0, b = 0, c = 0, x1 = 0, x2 = 0, x1Ref = 0, x2Ref = 0;
        int nRootsRef = 0;
        roots nRoots = NO_ROOTS;

        state = read_from_unit_tests(&a, &b, &c, &nRootsRef, &x1Ref, &x2Ref, file);

        if (state == OP_STATUS_EXIT){
            break;
        }
        if (state == OP_STATUS_DO_IT_AGAIN){
            continue;
        }

        nRoots = solve_quadratic_equations(a, b, c, &x1, &x2);
        bool success = is_success(x1, x2, x1Ref, x2Ref, nRoots, nRootsRef);

        print_unit_result(index, a, b, c, nRootsRef, x1Ref, x2Ref, nRoots, x1, x2, success);
    } while (state != OP_STATUS_EXIT);

    fclose(file);
}
