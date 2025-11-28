#ifndef RECOMENDACIONES_H
#define RECOMENDACIONES_H

#include "peliculas.h"
#include "usuarios.h"

// Calcula la similitud entre el usuario y todas las películas
// usando distancia euclidiana o coseno (tú eliges luego).
void generarRecomendaciones(int userId,
                            Pelicula peliculas[],
                            int totalPeliculas);

// Función que verifica si el usuario ya calificó esa película.
// Será útil si quieren usar tabla hash o filtro Bloom luego.
bool usuarioYaVioPelicula(int userId, int movieId);

// Muestra el top de recomendaciones (luego Hiram hace el ordenamiento)
void mostrarTopRecomendaciones();

#endif
