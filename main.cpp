#include "main.h"

int main() {
  double a = 0.0, b = 0.0, c = 0.0;

  opStatus state = OP_STATUS_EXIT;
  do {
    state = input_coefficients(&a, &b, &c);
    handle_op_status(a, b, c, &state);
  } while (state == OP_STATUS_DO_IT_AGAIN);

  return 0;
}


