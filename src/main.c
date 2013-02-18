#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "warp.h"

void show_help(const char const *progname);

int main(const int argc, char const **argv) {
  bool has_distance = false;
  bool use_tng = false;

  double distance_ly = 1.0;
  double factor = 1.0;

  if (argc < 2) {
    printf("Warp factor required.\n");
    return 0;
  }

  if (strncmp(argv[1], "-h", 2) == 0
      || strncmp(argv[1], "--help", 6) == 0)
    {
      show_help(argv[0]);
      return 0;
    }

  factor = strtod(argv[1], NULL);

  for (int i = 2; i < argc; i++) {
    if (strncmp(argv[i], "-d", 2) == 0
	|| strncmp(argv[i], "--distance", 10) == 0
	|| strncmp(argv[i], "--dist", 6) == 0)
      {
	has_distance = true;
	if (i + 1 < argc)
	  distance_ly = strtod(argv[++i], NULL);
	else {
	  printf("Distance required.\n");
	  return 1;
	}
      }

    if (strncmp(argv[i], "-t", 2) == 0
	|| strncmp(argv[i], "--tng", 5) == 0)
      {
	use_tng = true;
      }

    if (strncmp(argv[i], "-h", 2) == 0
	|| strncmp(argv[i], "--help", 6) == 0)
      {
	show_help(argv[0]);
	return 0;
      }
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

void show_help(const char const *progname) {
  printf("Usage: %s factor [options]\n", progname);
  printf("Options:\n");
  printf("  --distance, --dist, -d  Distance (in light-years)\n");
  printf("  --tng, -t               Use TNG warp speed formula\n");
  printf("  --help, -h              Show this message and exit\n");
}
