#ifndef RECOMENDACIONES_H
#define RECOMENDACIONES_H

#include "peliculas.h"
#include "usuarios.h"
#include "hashTable.h"

// Estructura de recomendación
struct Recomendacion
{
    int idPelicula;
    double puntaje;
};

// Función de similitud
double calcularSimilitudUsuarios(const Usuario &u1, const Usuario &u2);

// Función principal
void generarRecomendaciones(int idUsuario, Usuario usuarios[], int totalUsuarios, Pelicula peliculas[], int totalPeliculas);

// Función auxiliar para mostrar (Ahora recibe usuarios para el promedio)
void mostrarTopRecomendaciones(Recomendacion r[], int total, Pelicula peliculas[], int totalPeliculas, Usuario usuarios[], int totalUsuarios);

#endif