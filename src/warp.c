#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "warp.h"

double tos_warp(const double factor) {
  return pow(factor, 3);
}

double tng_warp(const double factor) {
  double a = 0.20467 * exp(-0.0058 * pow(log10(100000 - 10000 * factor), 5));
  double b = 1 + (2 * cos(10 * PI * log10(8 / (100 - 10 * factor))) - 1) / 3 
    * exp(-49.369 * pow(log10(8 / (100 - 10 * factor)), 4));
  double c = 1 + 1.88269 
    * (0.5 * PI - atan(pow(10, factor) * log10(20000 - 2000 * factor))) / PI;

  return pow(factor, (10.0 / 3) * (1 + a * b * c));
}

int main(const int argc, char const **argv) {
  bool has_distance = false;
  bool has_factor = false;
  bool use_tng = false;

  double distance_ly = 1.0;
  double factor = 1.0;

  for (int i = 1; i < argc; i++) {
    if (strncmp(argv[i], "-d", 2) == 0) {
      has_distance = true;
      if (i + 1 < argc)
	distance_ly = strtod(argv[++i], NULL);
    }

    if (strncmp(argv[i], "-f", 2) == 0) {
      has_factor = true;
      if (i + 1 < argc)
	factor = strtod(argv[++i], NULL);
    }

    if (strncmp(argv[i], "-t", 2) == 0)
      use_tng = true;
  }

  if (!has_factor) {
    printf("Warp factor required.\n");
    return 1;
  }

  double velocity = use_tng ? tng_warp(factor) : tos_warp(factor);

  if (has_distance) {
    printf("%g\n", distance_ly / velocity);
  }
  else {
    printf("%g\n", velocity);
  }

  return 0;
}
