#include "main.h"

int main() {
  coeff eqCoeff = {};

  opStatus state = OP_STATUS_EXIT;
  do {
    state = input_coefficients(&eqCoeff);
    handle_op_status(eqCoeff, &state);
  } while (state == OP_STATUS_DO_IT_AGAIN);

  return 0;
}


