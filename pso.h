#ifndef PSO_H
#define PSO_H

#include "map.h"

typedef struct {
    double x, y;
    double vx, vy;
    double best_x, best_y;
    double best_value;
} Particle;

typedef struct {
    Particle *particles;
    int size;

    double gbest_x, gbest_y;
    double gbest_value;

    double w, c1, c2;
} Swarm;

Swarm* init_swarm(int size, map *mapp);
void update_swarm(Swarm *swarm, map *mapp);
void free_swarm(Swarm *swarm);

#endif

