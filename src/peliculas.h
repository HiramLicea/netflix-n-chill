#ifndef PELICULAS_H
#define PELICULAS_H

#include <unordered_map>

#define MAX_PELICULAS 2000

struct Pelicula
{
    int id;
    char titulo[200];
    char genero[100];
    int anio;
};

struct Usuario;
extern std::unordered_map<int, int> mapaPeliculas;
extern Pelicula peliculas[MAX_PELICULAS];
extern int totalPeliculas;

void cargarPeliculas(Pelicula peliculas[], int &totalPeliculas);
void mostrarPeliculas(Pelicula peliculas[], int totalPeliculas);
void modificarPelicula(Pelicula peliculas[], int totalPeliculas);
void eliminarPelicula(Pelicula peliculas[], int &totalPeliculas);
void eliminarPelicula(Pelicula peliculas[], int &totalPeliculas, int idEliminar, Usuario usuarios[], int totalUsuarios);

int buscarPeliculaPorID(Pelicula peliculas[], int totalPeliculas, int idBuscado);
bool peliculaConCalificaciones(int idPelicula, struct Usuario usuarios[], int totalUsuarios);

#endif
