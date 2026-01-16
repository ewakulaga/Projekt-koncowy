#ifndef MAP_H
#define MAP_H

typedef struct {
    int szerokosc;
    int wysokosc;
    double **value;
}map;

map* load_map(const char *plik);   //wczytanie mapy

double get_value(map *mapp, int x, int y);    //pobranie danych z pliku

void free_map(map *mapp);            //zwolnienie pamieci




#endif