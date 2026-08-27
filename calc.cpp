#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdbool.h>
#include "calc.h"
#include "colors.h"

roots solve_quadratic_equations(coeff eqCoeff, EqRoots *rootsOfEq) {
  assert(rootsOfEq != NULL);
  assert(&(rootsOfEq->x1) != &(rootsOfEq->x2));

  if (is_zero(eqCoeff.a)) {
    return solve_linear(eqCoeff, rootsOfEq);
  } else {
    return solve_square(eqCoeff, rootsOfEq);
  }
}

roots solve_linear(coeff eqCoeff, EqRoots *rootsOfEq) {
  assert(rootsOfEq != NULL);

  if (is_zero(eqCoeff.b) && is_zero(eqCoeff.c)) {
    return INF_ROOTS;
  }

  if (is_zero(eqCoeff.b)) {
    return NO_ROOTS;
  }

  rootsOfEq->x1 = -eqCoeff.c / eqCoeff.b + 0.0; // -0.0 + 0.0 = 0.0

  return ONE_ROOT;
}

bool is_zero(const double val) {
  return fabs(val) < EPS;
}

bool is_equal(double a, double b) {
    return is_zero(fabs(a - b));
}

roots solve_square(coeff eqCoeff, EqRoots *rootsOfEq) {
  assert(rootsOfEq != NULL);

  double *x1 = &(rootsOfEq->x1), *x2 = &(rootsOfEq->x2);
  double a = eqCoeff.a, b = eqCoeff.b, c = eqCoeff.c;

  assert(x1 != x2);

  if (is_zero(c)) {
    *x1 = 0;
    *x2 = -b / a + 0.0; // -0.0 + 0.0 = 0.0
    if (is_equal(*x1, *x2))
        return ONE_ROOT;
    return TWO_ROOTS;
  }

  double disc = find_discriminant(eqCoeff);
  if (is_zero(disc)) {
    *x1 = -b / (2 * a) + 0.0; // -0.0 + 0.0 = 0.0
    return ONE_ROOT;
  }
  if (disc > 0) {
    double sqDisc = sqrt(disc);
    *x1 = (-b + sqDisc) / (2 * a);
    *x2 = (-b - sqDisc) / (2 * a);
    return TWO_ROOTS;
  }

  return NO_ROOTS;
}

double find_discriminant(coeff eqCoeff) {
  return eqCoeff.b * eqCoeff.b - 4 * eqCoeff.a * eqCoeff.c + 0.0; // -0.0 + 0.0 = 0.0
}


