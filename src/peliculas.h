#ifndef PELICULAS_H
#define PELICULAS_H

struct Pelicula {
    int id;
    char titulo[200];
    char genero[100];
    int anio;
};

//definimos un maximo de 100 peliculas solo para ir probando pero el dataset "peliculas.csv" contiene 45,000 peliculas
const int MAX_PELICULAS = 100;

void cargarPeliculas(Pelicula peliculas[], int &totalPeliculas); //definimos funcion que carga las peliculas desde el dataset
void mostrarPeliculas(Pelicula peliculas[], int totalPeliculas); //definimos funcion para mostrar peliculas

#endif
