#ifndef RECOMENDACIONES_H
#define RECOMENDACIONES_H

#include "peliculas.h"
#include "hashTable.h"

//---------------------------------------------------
// Estructura de recomendación (película + puntaje)
//---------------------------------------------------
struct Recomendacion {
    int idPelicula;
    double puntaje;   // basado en similitud
};



/// Calcula similitud entre dos usuarios usando Coseno
double calcularSimilitudUsuarios(const Usuario &u1, const Usuario &u2);

/// Genera y muestra recomendaciones basadas en similitud + HashTable
void generarRecomendaciones(int idUsuario,Usuario usuarios[], int totalUsuarios,Pelicula peliculas[], int totalPeliculas);

/// Construye la tabla hash de calificaciones de un usuario
void construirTablaHashUsuario(const Usuario &u, HashTable &tabla);

/// Verifica rápido si un usuario ya calificó una película (via Hash)
bool usuarioYaVioPeliculaHash(const HashTable &tabla, int idPelicula);
void mostrarTopRecomendaciones();

#endif

