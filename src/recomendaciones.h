#ifndef RECOMENDACIONES_H
#define RECOMENDACIONES_H

#include "peliculas.h"
#include "usuarios.h"
#include "hashTable.h"

// Estructura de recomendación
struct Recomendacion
{
    int idPelicula;
    double puntaje; // basado en similitud
};

double calcularSimilitudUsuarios(const Usuario &u1, const Usuario &u2, int totalPeliculas);

void generarRecomendaciones(int idUsuario, Usuario usuarios[], int totalUsuarios, Pelicula peliculas[], int totalPeliculas);

void mostrarTopRecomendaciones(Recomendacion r[], int total, Pelicula peliculas[], int totalPeliculas, Usuario usuarios[], int totalUsuarios);

#endif