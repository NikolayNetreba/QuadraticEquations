#include "main.h"
#include <stdlib.h>
#include <windows.h>
#include "colors.h"
#include "structures.h"
#include "calc.h"
#include "input.h"
#include "output.h"
#include "tests.h"

int main() {
  coeff eqCoeff = {};

  opStatus state = OP_STATUS_EXIT;
  do {
    state = input_coefficients(&eqCoeff);
    handle_op_status(eqCoeff, &state);
  } while (state == OP_STATUS_DO_IT_AGAIN);

  return 0;
}


