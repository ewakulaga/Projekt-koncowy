#include <stdlib.h>
#include <float.h>
#include "pso.h"
#include "utils.h"

Swarm* init_swarm(int size, map *mapp) {
    Swarm *s = malloc(sizeof(Swarm));
    s->size = size;
    s->particles = malloc(size * sizeof(Particle));

    s->gbest_value = -DBL_MAX;
    s->w = 0.5;
    s->c1 = 1.0;
    s->c2 = 1.0;

    for (int i = 0; i < size; i++) {
        Particle *p = &s->particles[i];

        p->x = rand_double(0, mapp->szerokosc);
        p->y = rand_double(0, mapp->wysokosc);
        p->vx = rand_double(-1, 1);
        p->vy = rand_double(-1, 1);

        int ix = (int)p->x;
        int iy = (int)p->y;

        p->best_value = get_value(mapp, ix, iy);
        p->best_x = p->x;
        p->best_y = p->y;

        if (p->best_value > s->gbest_value) {
            s->gbest_value = p->best_value;
            s->gbest_x = p->x;
            s->gbest_y = p->y;
        }
    }

    return s;
}

void update_swarm(Swarm *s, map *mapp) {
    for (int i = 0; i < s->size; i++) {
        Particle *p = &s->particles[i];

        double r1 = rand01();
        double r2 = rand01();

        p->vx = s->w * p->vx +
                s->c1 * r1 * (p->best_x - p->x) +
                s->c2 * r2 * (s->gbest_x - p->x);

        p->vy = s->w * p->vy +
                s->c1 * r1 * (p->best_y - p->y) +
                s->c2 * r2 * (s->gbest_y - p->y);

        p->x += p->vx;
        p->y += p->vy;

        int ix = (int)p->x;
        int iy = (int)p->y;

        double val = get_value(mapp, ix, iy);

        if (val > p->best_value) {
            p->best_value = val;
            p->best_x = p->x;
            p->best_y = p->y;
        }

        if (val > s->gbest_value) {
            s->gbest_value = val;
            s->gbest_x = p->x;
            s->gbest_y = p->y;
        }
    }
}

void free_swarm(Swarm *s) {
    if (!s) return;

    if(s->particles)
	    free(s->particles);

    free(s);
}

