#ifndef PELICULAS_H
#define PELICULAS_H

#include <unordered_map>

#define MAX_PELICULAS 200

struct Pelicula {
    int id;
    char titulo[200];
    char genero[100];
    int anio;
};

// Forward declaration para evitar includes circulares
struct Usuario;

// Hash global: id -> índice en arreglo peliculas[]
extern std::unordered_map<int, int> mapaPeliculas;

extern Pelicula peliculas[MAX_PELICULAS];
extern int totalPeliculas;

// Prototipos (firmas unificadas)
void cargarPeliculas(Pelicula peliculas[], int &totalPeliculas);
void mostrarPeliculas(Pelicula peliculas[], int totalPeliculas);

void modificarPelicula(Pelicula peliculas[], int totalPeliculas);
void eliminarPelicula(Pelicula peliculas[], int &totalPeliculas);

// Variante de eliminar que verifica usuarios (no obligatorio si no lo usas)
void eliminarPelicula(Pelicula peliculas[], int &totalPeliculas, int idEliminar, Usuario usuarios[], int totalUsuarios);

int buscarPeliculaPorID(Pelicula peliculas[], int totalPeliculas, int idBuscado);
bool peliculaConCalificaciones(int idPelicula, struct Usuario usuarios[], int totalUsuarios);

#endif
