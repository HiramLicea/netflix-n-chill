#ifndef RECOMENDACIONES_H
#define RECOMENDACIONES_H

#include "peliculas.h"
#include "usuarios.h"

// Verifica si el usuario ya vio/calificó la película
bool usuarioYaVioPelicula(int userId, int movieId);

// Calcula similitud REAL entre usuarios (coseno)
double calcularSimilitudUsuarios(const Usuario &u1, const Usuario &u2, int totalPeliculas);

// Genera recomendaciones para un usuario
void generarRecomendaciones(int userId,
                            Pelicula peliculas[],
                            int totalPeliculas);

// Mostrar top (si quieres ordenar después)
void mostrarTopRecomendaciones();

#endif
