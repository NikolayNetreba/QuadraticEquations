#include "main.h"
#include "calc.h"

roots solve_quadratic_equations(const double a, const double b, const double c,
                                double *x1, double *x2) {
  assert(x1 != NULL);
  assert(x2 != NULL);
  assert(x1 != x2);

  if (is_zero(a)) {
    return solve_linear(b, c, x1);
  } else {
    return solve_square(a, b, c, x1, x2);
  }
}

roots solve_linear(const double b, const double c, double *x1) {
  assert(x1 != NULL);

  if (is_zero(b) && is_zero(c)) {
    return INF_ROOTS;
  }

  if (is_zero(b)) {
    return ERROR_ROOTS;
  }

  *x1 = -c / b + 0.0;
  return ONE_ROOT;
}

roots solve_square(const double a, const double b, const double c, double *x1,
                   double *x2) {
  assert(x1 != NULL);
  assert(x2 != NULL);
  assert(x1 != x2);

  if (is_zero(c)) {
    *x1 = 0;
    *x2 = -b / a + 0.0;
    return TWO_ROOTS;
  }

  double disc = find_discriminant(a, b, c);
  if (disc > 0) {
    double sqDisc = sqrt(disc);
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

bool is_zero(const double val) { return fabs(val) < EPS; }

double find_discriminant(const double a, const double b, const double c) {
  return b * b - 4 * a * c;
}


