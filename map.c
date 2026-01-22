//obsluga wczytywania mapy, zwalnianie pamieci mapy
//pobieranie wartosci z danego punktu

#include <stdio.h>
#include <stdlib.h>
#include "map.h"

map* load_map(const char *plik) {
    FILE *in = fopen(plik, "r");

    if(in==NULL) {
        printf("nie mozna wczytac pliku");
        return NULL;
    }

    map *mapp = malloc(sizeof(map));

    if(mapp==NULL) {
        fclose(in);
        return NULL;
    } 

    if (fscanf(in, "%d %d", &mapp->szerokosc, &mapp->wysokosc) != 2) {
        fclose(in);
        free(mapp);
        return NULL;
    }



    mapp->value = malloc(mapp->wysokosc * sizeof(double*));

    if(mapp->value == NULL){
        free(mapp);
        fclose(in);
        return NULL;
    }

    for(int y=0; y < mapp->wysokosc; y++ ) {   
        mapp->value[y] = malloc(mapp->szerokosc * sizeof(double));

        if(mapp->value[y] == NULL) {
            for(int i=0; i<y; i++)
                free(mapp->value[i]);
            free(mapp->value);
            free(mapp);
            return NULL;
        }

        for(int x = 0; x < mapp->szerokosc; x++) {
            if(fscanf(in, "%lf", &mapp->value[y][x]) != 1) {
                for(int j =0; j < y; j++)
                    free(mapp->value[j]);
                free(mapp->value);
                free(mapp);
                fclose(in);
                return NULL;
            }

        }

    } 

    fclose(in);
    return mapp;

}

double get_value(map *mapp, int x, int y) {
    if(mapp==NULL) 
        return -100000.0;

    if(x < 0 || x >= mapp->szerokosc || y < 0 || y >= mapp->wysokosc)
        return -100000.0;

    return mapp->value[y][x];
}

void free_map(map *mapp) {
    if(mapp==NULL)
        return;
    
    if(mapp->value)   {

    for(int i = 0; i < mapp->wysokosc; i++){
        free(mapp->value[i]);
        } 
    free(mapp->value);
}  
free(mapp);
}

