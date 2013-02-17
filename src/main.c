#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "warp.h"

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
