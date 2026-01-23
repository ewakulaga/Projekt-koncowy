#include "pso.h"
#include "map.h"
#include "utils.h"
#include "logger.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_PARTICLE 30
#define DEFAULT_ITERATION 100

int main(int argc, char *argv[]) {

    if(argc<2) {
        printf("Uzycie: ./pso <plik_mapy> -p <liczba_czastek> -i <liczba_iteracji> -c <plik_konfiguracyjny z parametrami_PSO> -n <co_ktora_iteracje_zapis_postepow>\n");
        return 1;

} 

const char *map_file = argv[1];
int particles = DEFAULT_PARTICLE;
int iteracja = DEFAULT_ITERATION;
int logg = 0;
const char *config_filename = NULL;


for(int i = 2; i<argc; i++) {
    if(strcmp(argv[i], "-p")==0 && i+1<argc) {
        particles = atoi(argv[++i]);
    }
    else if(strcmp(argv[i], "-i")==0 && i+1<argc) {
        iteracja = atoi(argv[++i]);
    }
    else if(strcmp(argv[i], "-c")==0 && i+1<argc) {
        config_filename = argv[++i];
    }
    else if(strcmp(argv[i], "-n")==0 && i+1<argc) {
        iteracja = atoi(argv[++i]);
    }

else {
    printf("nieznany argument: %s\n", argv[i] );
    return 1;
    }
}

printf("Mapa: %s\n", map_file);
printf("Konfiguracja roju: liczba czastek = %d, liczba iteracji = %d, logowanie = %d\n", particles, iteracja, logg);


map *mapp = load_map(map_file);

if(mapp==NULL) {
    printf("Blad wczytywania mapy\n");
    return 1;
}

Swarm *swarm = init_swarm(particles, mapp);

if(!swarm) {
    printf("bład inicjalizacji roju\n");
    free(mapp);
    return 1;
}


double pso_w = 0.5;
double pso_c1 = 1.0;
double pso_c2 = 1.0;

if(config_filename != NULL){
    FILE *config_file = fopen(config_filename, "r");
    if(config_file){
        if(fscanf(config_file, "%lf %lf %lf", &pso_w, &pso_c1, &pso_c2) == 3){
            printf("Parametry PSO wczytane z pliku: w=%.2f, c1=%.2f, c2=%.2f\n", pso_w, pso_c1, pso_c2);
        } else {
            fprintf(stderr, "Blad: Niepoprawny format pliku konfiguracyjnego: %s\n", config_filename);
            printf("Uzycie domyslnych parametrow PSO: w=0.5, c1=1.0, c2=1.0\n");
        }
        fclose(config_file);
    }
    else{
        fprintf(stderr, "Blad: Nie mozna otworzyc pliku konfiguracyjnego: %s\n", config_filename);
        printf("Uzycie domyslnych parametrow PSO: w=0.5, c1=1.0, c2=1.0\n");
    }
}

 if(logg > 0){
        open_logger("pso_log.csv");
        printf("Plik logow zainicjalizowany: pso_log.csv\n");
    }

for(int i = 0; i < iteracja; i++) {
    update_swarm(swarm, mapp);

    if(logg > 0 && i % logg == 0){
        logger_log(i, swarm);
}
}

printf("Wyniki - najlepsze rozwiazanie:\n");
printf("x = %.3f\n", swarm->gbest_x);
printf("y = %.3f\n", swarm->gbest_y);
printf("wartość = %.3f\n", swarm->gbest_value);


free_swarm(swarm);
free_map(mapp);
return 0;

}

