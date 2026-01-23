//zapis danych posrednich

#include "logger.h"
#include <stdio.h>
#include <stdlib.h>

static FILE *p = NULL;

int open_logger(const char *plik) {
    p = fopen(plik, "w");

    if(p==NULL) {
        printf("nie mozna otworzyc pliku");
        return 1;
    }

    fprintf(p, "iteracja,czastka,x,y\n");
    fclose(p);
    return 0;
}


void logger_log(int iter, const Swarm *swarm) {
    if(p==NULL || swarm==NULL)
        return;
    
    for(int i = 0; i < swarm->size; i++) {

        const Particle *cz = &swarm->particles[i];

        fprintf(p, "%d,%d,%.6f,%.6f\n", iter, i, cz->x, cz->y );
    }
    
}


void close_logger(void) {
    if(p!=NULL) {
        fclose(p);
        p=NULL;
    }
}
