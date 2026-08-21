#include<stdio.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include"main.h"

int main() {
    double a = 0.0, b = 0.0, c = 0.0;
    opStatus state = OP_EXIT;
    do{ // TODO - в отдельную функцию
        state = input_coefficients(&a, &b, &c);

        switch (state) {
            case OP_DO_IT_AGAIN:
                continue;
            case OP_EXIT:
                printf("Bye!\n");
                return 0;

            case OP_OK: {
                double x1 = 0.0, x2 = 0.0;
                roots nRoot = solve_quadratic_equations(a, b, c, &x1, &x2);
                print_root(x1, x2, nRoot);
                return 0;
            }

            case OP_IMPOSSIBLE:
            default:
                printf("OP_IMPOSSIBLE\n");
                return 1;
        }
    } while (state == OP_DO_IT_AGAIN);
}

void scan_coefficient (double* a, double* b, double* c) {
    int scanCount = 0;
    do {
        printf ("Enter the coefficients: a, b, c:\n");
        scanCount = scanf ("%lf%lf%lf", a, b, c);

        if (scanCount != 3) {
            printf ("insufficient variables entered, do it again.\n");
            clear_buffer ();
        }
    } while (scanCount != 3);
}

void choose_option (char* op){
    printf("Choose an option:\n"
           "c - enter from the console\n"
           "f - enter from the file\n"
           "e - exit\n");


    while (scanf(" %1[cfe]", op) != 1) { // TODO - решить проблему с вводом cfe, проверять buffer
        printf("Try it again: ");
        clear_buffer ();
    }
    clear_buffer ();
}

FILE* scan_file_name () {
    FILE* file = NULL;
    char fileName[MAX_OP_LEN] = "";
    do {
        printf("Enter the file name: ");
        if (scanf("%" MAX_OP_LEN_STR "s", fileName) != 1) {
            clear_buffer();
            continue;
        }

        file = fopen(fileName, "r");
        if (file == NULL) {
            printf("File not found or cannot be opened!\n");
        }
    } while (file == NULL);
    return file;
}

opStatus input_coefficients (double* a, double* b, double* c) {// TODO - assert
    char op = 'e';
    choose_option (&op);

    switch (op) {
        case 'c':
            scan_coefficient(a, b, c);
            return OP_OK;// TODO - OP_STATUS_OK

        case 'f': {
            FILE* file = scan_file_name ();
            opStatus state = read_from_file (a, b, c, file);
            return state;
        }
        case 'e':
            return OP_EXIT;
        default:
            return OP_IMPOSSIBLE;
    }
}

opStatus read_from_file (double* a, double* b, double* c, FILE* file){
    verify_it (file != NULL, "Path is null");// TODO - assert

    int scanCount = 0;
    scanCount = fscanf (file, "%lf%lf%lf", a, b, c);
    if (scanCount != 3) {
        printf ("insufficient variables entered, do it again.\n");
        return OP_DO_IT_AGAIN;
    }
    fclose(file);
    return OP_OK;
}

void clear_buffer () {
    int trash = 0;
    while ((trash = getchar ()) != '\n' && trash != EOF);
}

bool is_zero (const double val) {
    return fabs (val) < EPS;
}

double find_discriminant (const double a, const double b, const double c) {
    return b * b - 4 * a * c;
}

void print_root (const double x1, const double x2, const roots nRoot) {
    switch(nRoot) {
        case ZERO_ROOTS:
            printf ("zero root, x1 = x2 = none");
            break;
        case ONE_ROOT:
            printf ("one root, x1 = x2 = %g", x1);
            break;
        case TWO_ROOTS:
            printf ("two root, x1 = %g x2 = %g", x1, x2);
            break;
        case INF:
            printf ("infinite");
            break;
        case ERROR:
            printf ("ERROR");
            break;
        default:
            printf ("IDK");
    }
}

roots solve_linear (const double b, const double c, double* x1) {
    assert (x1 != NULL);

    if (is_zero(b) && is_zero(c)) {
        return INF; // TODO
    }

    if (is_zero(b)) {
        return ERROR; //
    }

    *x1 = -c / b + 0.0;
    return ONE_ROOT;
}

roots solve_square (const double a, const double b, const double c, double* x1, double* x2) {
    assert (x1 != NULL);
    assert (x2 != NULL);
    assert (x1 != x2);

    if (is_zero(c)) {
        *x1 = 0;
        *x2 = -b / a + 0.0;
        return TWO_ROOTS;
    }

    double disc = find_discriminant(a, b, c);
    if (disc > 0) {
        double sqDisc = sqrt (disc);
        *x1 = (-b + sqDisc) / (2 * a);
        *x2 = (-b - sqDisc) / (2 * a);
        return TWO_ROOTS;
    }
    if (is_zero(disc)) {
        *x1 = -b / (2 * a) + 0.0;
        return ONE_ROOT;
    }
    return ZERO_ROOTS;
}

roots solve_quadratic_equations (const double a, const double b, const double c, double* x1, double* x2) {
    assert (x1 != NULL);
    assert (x2 != NULL);
    assert (x1 != x2);

    if (is_zero(a)) {
        return solve_linear (b, c, x1);
    } else {
        return solve_square (a, b, c, x1, x2);
    }
}
