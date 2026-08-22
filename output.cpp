#include "output.h"

void print_root(const double x1, const double x2, const roots nRoot) {
  switch (nRoot) {
  case ZERO_ROOTS:
    printf(MAKE_YELLOW("zero root, x1 = x2 = none\n")"-------------------------------------------------\n");
    break;
  case ONE_ROOT:
    printf(MAKE_GREEN("one root, x1 = x2 = %g\n")"-------------------------------------------------\n", x1);
    break;
  case TWO_ROOTS:
    printf(MAKE_GREEN("two root, x1 = %g x2 = %g\n")"-------------------------------------------------\n", x1, x2);
    break;
  case INF_ROOTS:
    printf(MAKE_CYAN("Infinite number of roots\n")"-------------------------------------------------\n");
    break;
  case ERROR_ROOTS:
    printf(MAKE_RED("ERROR\n")"-------------------------------------------------\n");
    break;
  default:
    printf(MAKE_RED("IDK\n")"-------------------------------------------------\n");
  }
}
