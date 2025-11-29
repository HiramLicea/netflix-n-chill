#ifndef PELICULAS_H
#define PELICULAS_H
#include "usuarios.h"

struct Pelicula
{
    int id;
    char titulo[200];
    char genero[100];
    int anio;
};

const int MAX_PELICULAS = 100;

void cargarPeliculas(Pelicula peliculas[], int &totalPeliculas);
void mostrarPeliculas(Pelicula peliculas[], int totalPeliculas);

void modificarPelicula(Pelicula peliculas[], int totalPeliculas);
void eliminarPelicula(Pelicula peliculas[], int &totalPeliculas);

void eliminarPelicula(Pelicula peliculas[], int &totalPeliculas, int idEliminar,
                      Usuario usuarios[], int totalUsuarios);

int buscarPeliculaPorID(Pelicula peliculas[], int totalPeliculas, int id);

bool peliculaConCalificaciones(int idPelicula, Usuario usuarios[], int totalUsuarios);

void generarRecomendaciones(int usuarioId, Pelicula peliculas[], int totalPeliculas);

#endif
