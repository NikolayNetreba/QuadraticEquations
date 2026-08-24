#include "tests.h"

void start_tests() {
    FILE *file = scan_file_name();
    do_unit_tests(file);

    int range = 0;
    choose_value(&range, "Range");
    int test_count = 0;
    choose_value(&test_count, "Number of repetitions");

    do_stress_tests(range, test_count);
}

void choose_value(int *value, const char *message) {
    assert(value != NULL);
    assert(message != NULL);

    int countScanf = 0;
    do {
        printf(MAKE_YELLOW("Choose the %s: "), message);
        countScanf = scanf("%d", value);
        if (countScanf != 1) {
            printf(MAKE_RED("insufficient variables entered, do it again.\n")LINE);
            clear_buffer();
        }
    } while(countScanf != 1);
}

bool check_stress_tests(coeff eqCoeff, EqRoots rootsOfEq) {
    bool result = false;
    double a = eqCoeff.a, b = eqCoeff.b, c = eqCoeff.c;
    double x1 = rootsOfEq.x1, x2 = rootsOfEq.x2;
    int nRoots = rootsOfEq.nRoots;

    double disc = find_discriminant(eqCoeff);
    switch(nRoots) {
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
            assert("Visited default, but didn't have to" && 0);
            break;
    };

    return result;
}

void print_stress_test_result(int index, coeff eqCoeff, EqRoots rootsOfEq, int success) {
    if (success) {
            printf(MAKE_GREEN("%d Unit test passed\n"), index);
    } else {
        printf(LINE
                MAKE_RED("%d Unit test FAILED: ") "a = %lg, b = %lg, c = %lg,\n"
                MAKE_BLUE("Got: ") "%d roots, x1 = %lg, x2 = %lg\n"
                LINE,
                index, eqCoeff.a, eqCoeff.b, eqCoeff.c,
                rootsOfEq.nRoots, rootsOfEq.x1, rootsOfEq.x2);
    }
}

void do_stress_tests(const int range, const int count) {
    for (int i = 0; i < count;  ++i) {
        coeff eqCoeff = {
            .a = (double)(rand() % range - (range / 2)),
            .b = (double)(rand() % range - (range / 2)),
            .c = (double)(rand() % range - (range / 2)),
        };
        EqRoots rootsOfEq = {};

        rootsOfEq.nRoots = solve_quadratic_equations(eqCoeff, &rootsOfEq);

        bool result = check_stress_tests(eqCoeff, rootsOfEq);
        print_stress_test_result(i, eqCoeff, rootsOfEq, result);
    }
}

opStatus read_from_unit_tests(coeff *eqCoeff, EqRoots *RefRootsOfEq, FILE *file) {
    assert(eqCoeff != NULL);
    assert(RefRootsOfEq != NULL);
    assert(file != NULL && "Path is null");

    int scanCount = fscanf(file, "%lf%lf%lf%d%lf%lf", &(eqCoeff->a), &(eqCoeff->b), &(eqCoeff->c),
                                                (int*)&(RefRootsOfEq->nRoots),
                                                &(RefRootsOfEq->x1), &(RefRootsOfEq->x2));

    return process_scan_count(scanCount);
}

opStatus process_scan_count(int scanCount) {
    if (scanCount == END_SCAN_COUNT) {
        printf(MAKE_CYAN("Unit tests completed.\n"));
        return OP_STATUS_EXIT;
    }
    if (scanCount != FILE_SCAN_COUNT) {
        printf(MAKE_RED("insufficient variables entered, do it again.\n")
        LINE);
        clear_buffer();
        return OP_STATUS_DO_IT_AGAIN;
    }

    return OP_STATUS_OK;
}

bool is_success(EqRoots RootsOfEq, EqRoots RefRootsOfEq) {
    bool success = (RootsOfEq.nRoots == RefRootsOfEq.nRoots);
    if (!success){
        return success;
    }
    if (RootsOfEq.nRoots == 2) {
        success = ((is_equal(RootsOfEq.x1, RefRootsOfEq.x1) && is_equal(RootsOfEq.x2, RefRootsOfEq.x2)) ||
                   (is_equal(RootsOfEq.x1, RefRootsOfEq.x2) && is_equal(RootsOfEq.x2, RefRootsOfEq.x1)));
    } else if (RootsOfEq.nRoots == 1) {
            success = is_equal(RootsOfEq.x1, RefRootsOfEq.x1);
    }

    return success;
}

void print_unit_result(int index, coeff eqCoeff, EqRoots RefRootsOfEq,
                       EqRoots RootsOfEq, int success) {
    if (success) {
            printf(MAKE_GREEN("%d Unit test passed\n"), index);
    } else {
        printf(LINE
                MAKE_RED("%d Unit test FAILED: ") "a = %lg, b = %lg, c = %lg,\n"
                MAKE_YELLOW("Expected: ") "%d roots, x1 = %lg, x2 = %lg,\n"
                MAKE_BLUE("Got: ") "%d roots, x1 = %lg, x2 = %lg\n"
                LINE,
                index, eqCoeff.a, eqCoeff.b, eqCoeff.c,
                RefRootsOfEq.nRoots, RefRootsOfEq.x1, RefRootsOfEq.x2,
                   RootsOfEq.nRoots,    RootsOfEq.x1,    RootsOfEq.x2);
    }
}

void do_unit_tests(FILE *file) {
    //TODO - as
    opStatus state = OP_STATUS_EXIT;
    int index = 0;
    do {
        index++;
        coeff eqCoeff = {};
        EqRoots RefRootsOfEq = {}, RootsOfEq = {};

        state = read_from_unit_tests(&eqCoeff, &RefRootsOfEq, file);

        if (state == OP_STATUS_EXIT) {
            break;
        }
        if (state == OP_STATUS_DO_IT_AGAIN) {
            continue;
        }

        RootsOfEq.nRoots = solve_quadratic_equations(eqCoeff, &RootsOfEq);
        bool success = is_success(RootsOfEq, RefRootsOfEq);

        print_unit_result(index, eqCoeff, RefRootsOfEq, RootsOfEq, success);
    } while (state != OP_STATUS_EXIT);

    fclose(file);
}
