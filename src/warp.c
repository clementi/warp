#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

double tos_warp(const double factor);

double tos_warp(const double factor) {
    return pow(factor, 3);
}

int main(const int argc, char const **argv) {
    bool has_distance = false;
    bool has_factor = false;

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
    }

    if (!has_factor) {
        printf("Warp factor required.\n");
        return 1;
    }

    if (has_distance) {
        printf("%g\n", distance_ly / tos_warp(factor));
    }
    else {
        printf("%g\n", tos_warp(factor));
    }

    return 0;
}
