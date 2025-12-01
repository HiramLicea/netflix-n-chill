#ifndef PELICULAS_H
#define PELICULAS_H

<<<<<<< HEAD
=======
#include <unordered_map>

#define MAX_PELICULAS 2000

>>>>>>> 7b97e2e6125ff9075f4b59d38dc1f624b48dbfad
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
<<<<<<< HEAD

=======
>>>>>>> 7b97e2e6125ff9075f4b59d38dc1f624b48dbfad
void modificarPelicula(Pelicula peliculas[], int totalPeliculas);
void eliminarPelicula(Pelicula peliculas[], int &totalPeliculas);
void eliminarPelicula(Pelicula peliculas[], int &totalPeliculas, int idEliminar, Usuario usuarios[], int totalUsuarios);

<<<<<<< HEAD
void eliminarPelicula(Pelicula peliculas[], int &totalPeliculas, int idEliminar,
                      Usuario usuarios[], int totalUsuarios);

int buscarPeliculaPorID(Pelicula peliculas[], int totalPeliculas, int id);

bool peliculaConCalificaciones(int idPelicula, Usuario usuarios[], int totalUsuarios);

void generarRecomendaciones(int usuarioId, Pelicula peliculas[], int totalPeliculas);
=======
int buscarPeliculaPorID(Pelicula peliculas[], int totalPeliculas, int idBuscado);
bool peliculaConCalificaciones(int idPelicula, struct Usuario usuarios[], int totalUsuarios);
>>>>>>> 7b97e2e6125ff9075f4b59d38dc1f624b48dbfad

#endif
