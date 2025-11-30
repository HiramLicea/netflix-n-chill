#ifndef RATINGS_H
#define RATINGS_H
#include "usuarios.h"

// Guarda una calificación en ratings.csv
void guardarRating(int userId, int movieId, int rating);

// Carga todas las calificaciones desde ratings.csv a tus usuarios
void cargarRatings(Usuario usuarios[], int totalUsuarios);

#endif
