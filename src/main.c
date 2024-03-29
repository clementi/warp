#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "warp.h"

#define _HELP_STR_ "--help"
#define _HELP_STR_SHORT_ "-h"

#define _DIST_STR_ "--distance"
#define _DIST_STR_MED_ "--dist"
#define _DIST_STR_SHORT_ "-d"

#define _TNG_STR_ "--tng"
#define _TNG_STR_SHORT_ "-t"

void show_help(const char *progname);

int main(const int argc, char const **argv) {
  bool has_distance = false;
  bool use_tng = false;

  double distance_ly = 1.0;
  double factor = 1.0;

  if (argc < 2) {
    printf("Warp factor required.\n");
    return 1;
  }

  if (strncmp(argv[1], _HELP_STR_SHORT_, strlen(_HELP_STR_SHORT_)) == 0 ||
      strncmp(argv[1], _HELP_STR_, strlen(_HELP_STR_)) == 0) {
    show_help(argv[0]);
    return 0;
  }

  factor = strtod(argv[1], NULL);

  for (int i = 2; i < argc; i++) {
    if (strncmp(argv[i], _DIST_STR_SHORT_, strlen(_DIST_STR_SHORT_)) == 0 ||
        strncmp(argv[i], _DIST_STR_, strlen(_DIST_STR_)) == 0 ||
        strncmp(argv[i], _DIST_STR_MED_, strlen(_DIST_STR_MED_)) == 0) {
      has_distance = true;
      if (i + 1 < argc)
        distance_ly = strtod(argv[++i], NULL);
      else {
        printf("Distance required.\n");
        return 1;
      }
    }

    if (strncmp(argv[i], _TNG_STR_SHORT_, strlen(_TNG_STR_SHORT_)) == 0 ||
        strncmp(argv[i], _TNG_STR_, strlen(_TNG_STR_)) == 0) {
      use_tng = true;
    }

    if (strncmp(argv[i], _HELP_STR_SHORT_, strlen(_HELP_STR_SHORT_)) == 0 ||
        strncmp(argv[i], _HELP_STR_, strlen(_HELP_STR_)) == 0) {
      show_help(argv[0]);
      return 0;
    }
  }

  if (factor < 0) {
    printf("Warp factor must be non-negative.\n");
    return 1;
  }

  if (use_tng && factor >= 10) {
    printf("Warp factor must be less than 10 if using the TNG formula.\n");
    return 1;
  }

  double velocity = use_tng ? tng_warp(factor) : tos_warp(factor);

  if (has_distance)
    printf("%lf\n", distance_ly / velocity);
  else
    printf("%lf\n", velocity);

  return 0;
}

void show_help(const char *progname) {
  printf("Usage: %s factor [options]\n", progname);
  printf("Options:\n");
  printf("  --distance, --dist, -d  Distance (in light-years)\n");
  printf("  --tng, -t               Use TNG warp speed formula\n");
  printf("  --help, -h              Show this message and exit\n");
}
