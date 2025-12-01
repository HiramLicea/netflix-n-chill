#ifndef USUARIOS_H
#define USUARIOS_H
#include "peliculas.h"
#define MAX_USUARIOS 200
#define MAX_PELICULAS_VISTAS 200


struct Calificacion
{
    int idPelicula;
    int puntuacion; // 1-5
};

struct Usuario
{
    int id;
    char nombre[100];
    Calificacion calificaciones[MAX_PELICULAS_VISTAS];
    int numCalificaciones;
};

extern Usuario usuarios[MAX_USUARIOS];
extern int totalUsuarios;

// Regisrtrar un nuevo usuario
void registrarUsuario(Usuario usuarios[], int &totalUsuarios);

// calificar una pelicula
void calificarPelicula(Usuario usuarios[], int totalUsuarios, Pelicula peliculas[], int totalPeliculas);

// Calcular promedio de pelicula en especifico
float promedioPelicula(int idPelicula, Usuario usuarios[], int totalUsuarios);

// Buscar usuario por ID
int buscarUsuarioPorID(int id, Usuario usuarios[], int totalUsuarios);

#endif