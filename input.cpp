#include "input.h"

void handle_op_status(const double a, const double b, const double c, opStatus* state) {
  switch (*state) {
  case OP_STATUS_DO_IT_AGAIN:
    break ;
  case OP_STATUS_EXIT:
    printf(MAKE_MAGENTA("Bye!\n"));
    return;
  case OP_STATUS_OK: {
    double x1 = 0.0, x2 = 0.0;
    roots nRoot = solve_quadratic_equations(a, b, c, &x1, &x2);
    print_root(x1, x2, nRoot);
    break;
  }
  case OP_STATUS_IMPOSSIBLE:
  default:
    printf(MAKE_RED("OP_IMPOSSIBLE\n"));
    break;
  }
  *state = OP_STATUS_DO_IT_AGAIN;
}

opStatus input_coefficients(double *a, double *b, double *c) {
  assert(a != NULL);
  assert(b != NULL);
  assert(c != NULL);

  opChoose op = op_exit;
  choose_option(&op);

  switch (op) {
    case op_console: {
      scan_coefficient(a, b, c);
      return OP_STATUS_OK;
    }
    case op_file: {
      FILE *file = scan_file_name();
      opStatus state = read_from_file(a, b, c, file);
      return state;
    }
    case op_exit: {
      return OP_STATUS_EXIT;
    }
    default: {
      return OP_STATUS_IMPOSSIBLE;
    }
  }
}

void scan_op(opChoose *op) {
  assert(op != NULL);
  char temp = ' ';

  while (scanf(" %1[cfe]", &temp) != 1) {
    printf(MAKE_RED("Try it again: "));
    clear_buffer();
  }

  *op = (opChoose)temp;
}

void choose_option(opChoose *op) {
  assert(op != NULL);

  printf(MAKE_CYAN("Choose an option:\n")
         MAKE_GREEN("c ")"- enter from the console\n"
         MAKE_BLUE("f ")"- enter from the file\n"
         MAKE_MAGENTA("e ")"- exit\n");

  int sumOfChar = 0;
  do {
    scan_op(op);
    sumOfChar = check_and_clear_buffer();
    if (sumOfChar != 0)
      printf(MAKE_RED("Try it again: "));
  } while (sumOfChar != 0);
}

void scan_coefficient(double *a, double *b, double *c) {
  assert(a != NULL);
  assert(b != NULL);
  assert(c != NULL);

  int scanCount = 0, sumOfChar = 0;
  do {
    printf(MAKE_YELLOW("Enter the coefficients: a, b, c:\n"));
    scanCount = scanf("%lf%lf%lf", a, b, c);
    sumOfChar = check_and_clear_buffer();

    if (scanCount != SCAN_CHECK || sumOfChar != 0) {
      printf(MAKE_RED("insufficient variables entered, do it again.\n")"-------------------------------------------------\n");
    }
  } while (scanCount != SCAN_CHECK || sumOfChar != 0);
}

FILE *scan_file_name() {
  FILE *file = NULL;
  char fileName[MAX_OP_LEN] = "";
  do {
    printf(MAKE_YELLOW("Enter the file name: "));
    if (scanf("%" MAX_OP_LEN_STR "s", fileName) != 1) {
      clear_buffer();
      continue;
    }

    file = fopen(fileName, "r");
    if (file == NULL) {
      printf(MAKE_RED("File not found or cannot be opened!\n")"-------------------------------------------------\n");
    }
  } while (file == NULL);
  return file;
}

opStatus read_from_file(double *a, double *b, double *c, FILE *file) {
  assert(a != NULL);
  assert(b != NULL);
  assert(c != NULL);
  assert(file != NULL && "Path is null");

  int scanCount = fscanf(file, "%lf%lf%lf", a, b, c);
  if (scanCount != SCAN_CHECK) {
    printf(MAKE_RED("insufficient variables entered, do it again.\n")"-------------------------------------------------\n");
    return OP_STATUS_DO_IT_AGAIN;
  }
  fclose(file);
  return OP_STATUS_OK;
}

int check_and_clear_buffer() {
  int trash = 0, totalSum = 0;
  while ((trash = getchar()) != '\n' && trash != EOF) {
    totalSum += trash - ' ';
  }
  return totalSum;
}

void clear_buffer() {
  int trash = 0;
  while ((trash = getchar()) != '\n' && trash != EOF);
}
