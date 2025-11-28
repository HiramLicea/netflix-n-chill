#include <iostream>
#include <cmath>
#include "recomendaciones.h"
using namespace std;

// -------------------------------------------------------
// TEMPORAL: El usuario no tiene películas vistas todavía.
// Cuando Hiram implemente calificaciones, aquí se consulta.
// -------------------------------------------------------
bool usuarioYaVioPelicula(int userId, int movieId) {
    return false; // por ahora siempre false
}

// -------------------------------------------------------
// Ejemplo de similitud simple (stub temporal).
// Luego tú lo cambias por Euclidiana o Coseno.
// -------------------------------------------------------
double similitudDummy(int movieId, int userId) {
    return 1.0; // todas iguales por ahora
}

// -------------------------------------------------------
// Generar recomendaciones (versión inicial)
// -------------------------------------------------------
void generarRecomendaciones(int userId,
                            Pelicula peliculas[],
                            int totalPeliculas)
{
    cout << "\n*** GENERANDO RECOMENDACIONES ***\n";

    for (int i = 0; i < totalPeliculas; i++) {

        // Ignorar películas que ya vio
        if (usuarioYaVioPelicula(userId, peliculas[i].id)) {
            continue;
        }

        double score = similitudDummy(peliculas[i].id, userId);

        cout << "Pelicula: " << peliculas[i].titulo
             << "  | Score: " << score << "\n";
    }
}

// -------------------------------------------------------
// Muestra top (lo completará Hiram cuando ordene)
// -------------------------------------------------------
void mostrarTopRecomendaciones() {
    cout << "Funcion mostrarTopRecomendaciones aun no implementada.\n";
}
