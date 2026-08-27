#include <stdio.h>
#include <assert.h>
#include "colors.h"
#include "output.h"

void print_root(EqRoots rootsOfEq) {
  switch (rootsOfEq.nRoots) {
  case NO_ROOTS:
    printf(MAKE_YELLOW("zero root, x1 = x2 = none\n")LINE);
    break;
  case ONE_ROOT:
    printf(MAKE_GREEN("one root, x1 = x2 = %g\n")LINE, rootsOfEq.x1);
    break;
  case TWO_ROOTS:
    printf(MAKE_GREEN("two root, x1 = %g x2 = %g\n")LINE, rootsOfEq.x1, rootsOfEq.x2);
    break;
  case INF_ROOTS:
    printf(MAKE_CYAN("Infinite number of roots\n")LINE);
    break;
  default:
    printf(MAKE_RED("IDK\n")LINE);
    assert("Visited default, but didn't have to" && 0);
    break;
  }
}




