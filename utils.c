#include <stdlib.h>
#include "utils.h"

double rand01() {
    return (double) rand() / RAND_MAX;
}

double rand_double(double min, double max) {
    return min + rand01() * (max - min);
}

