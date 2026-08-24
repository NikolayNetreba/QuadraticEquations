#include "input.h"

void handle_op_status(coeff eqCoeff, opStatus* state) {
  switch (*state) {
  case OP_STATUS_DO_IT_AGAIN:
    break;
  case OP_STATUS_EXIT:
    printf(MAKE_MAGENTA("Bye!\n"));
    return;
  case OP_STATUS_OK: {
    EqRoots rootsOfEq = {};
    rootsOfEq.nRoots = solve_quadratic_equations(eqCoeff, &rootsOfEq);
    print_root(rootsOfEq);
    break;
  }
  case OP_STATUS_TEST:
    start_tests();
    break;
  case OP_STATUS_IMPOSSIBLE:
    printf(MAKE_RED("OP_IMPOSSIBLE\n"));
    break;
  default:
    assert("Visited default, but didn't have to" && 0);
  }
  *state = OP_STATUS_DO_IT_AGAIN;
}

opStatus input_coefficients(coeff* eqCoeff) {
  assert(eqCoeff != NULL);

  opChoose op = op_exit;
  choose_option(&op);

  switch (op) {
    case op_console: {
      scan_coefficient(eqCoeff);
      return OP_STATUS_OK;
    }
    case op_file: {
      FILE *file = scan_file_name();
      opStatus state = read_from_file(eqCoeff, file);
      fclose(file);
      return state;
    }
    case op_test: {
      return OP_STATUS_TEST;
    }
    case op_exit: {
      return OP_STATUS_EXIT;
    }
    default: {
      assert("Visited default, but didn't have to" && 0);
      return OP_STATUS_IMPOSSIBLE;
    }
  }
}

void scan_op(opChoose *op) {
  assert(op != NULL);
  char temp = ' ';

  while (scanf(" %1[cfet]", &temp) != 1) {
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
         MAKE_YELLOW("t ")"- enter tests\n"
         MAKE_MAGENTA("e ")"- exit\n");

  int sumOfChar = 0;
  do {
    scan_op(op);
    sumOfChar = check_and_clear_buffer();
  if (sumOfChar != 0) {
    printf(MAKE_RED("Try it again: "));
  }
  } while (sumOfChar != 0);
}

void scan_coefficient(coeff *eqCoeff) {
  assert(eqCoeff != NULL);

  int scanCount = 0, sumOfChar = 0;
  do {
    printf(MAKE_YELLOW("Enter the coefficients: a, b, c:\n"));
    scanCount = scanf("%lf%lf%lf", &(eqCoeff->a), &(eqCoeff->b), &(eqCoeff->c));
    sumOfChar = check_and_clear_buffer();

    if (scanCount != NUMBER_SCANS || sumOfChar != 0) {
      printf(MAKE_RED("insufficient variables entered, do it again.\n")LINE);
    }
  } while (scanCount != NUMBER_SCANS || sumOfChar != 0);
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
    if (file == NULL){
      fprintf(stderr, MAKE_RED("Error opening file: ")"%s: ", fileName);
      perror("");
      fprintf(stderr, LINE);
    }
  } while (file == NULL);

  return file;
}

opStatus read_from_file(coeff *eqCoeff, FILE *file) {
  assert(eqCoeff != NULL);
  assert(file != NULL && "Path is null");

  int scanCount = fscanf(file, "%lf%lf%lf", &(eqCoeff->a), &(eqCoeff->b), &(eqCoeff->c));
  if (scanCount != NUMBER_SCANS) {
    printf(MAKE_RED("insufficient variables entered, do it again.\n")LINE);
    return OP_STATUS_DO_IT_AGAIN;
  }

  return OP_STATUS_OK;
}

int check_and_clear_buffer() {
  int trash = 0, totalSum = 0;
  while ((trash = getchar()) != '\n' && trash != EOF) {
    if ((trash != ' ') && (trash != '\t'))
      totalSum = 1;
  }

  return totalSum;
}

void clear_buffer() {
  int trash = 0;
  while ((trash = getchar()) != '\n' && trash != EOF);
}
