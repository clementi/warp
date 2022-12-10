#include <math.h>

#include "warp.h"

double tos_warp(const double factor) { return pow(factor, 3); }

double tng_warp(const double factor) {
  double a = 0.20467 * exp(-0.0058 * pow(log10(100000 - 10000 * factor), 5));
  double b = 1 + (2 * cos(10 * PI * log10(8 / (100 - 10 * factor))) - 1) / 3 *
                     exp(-49.369 * pow(log10(8 / (100 - 10 * factor)), 4));
  double c = 1 + 1.88269 *
                     (0.5 * PI -
                      atan(pow(10, factor) * log10(20000 - 2000 * factor))) /
                     PI;

  return pow(factor, (10.0 / 3) * (1 + a * b * c));
}
