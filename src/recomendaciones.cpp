#include <iostream>
#include <cmath>
#include "recomendaciones.h"
#include "usuarios.h"
using namespace std;

/*
 * Verifica si el usuario ya vio una película.
 * Esto se basa en si la calificación es distinta de -1.
 * -----------------------------------------------------
 * userId: ID del usuario que consulta.
 * movieId: ID de la película a revisar.
 * usuarios[]: arreglo global con todos los usuarios del sistema.
 */
bool usuarioYaVioPelicula(int userId, int movieId) {
    // Buscar usuario por ID
    for (int i = 0; i < totalUsuarios; i++) {
        if (usuarios[i].id == userId) {

            // Buscar película por ID
            for (int j = 0; j < MAX_PELICULAS; j++) {
                if (j == movieId) {
                    return usuarios[i].calificaciones[j].puntuacion != -1;
                }
            }
        }
    }
    return false;
}

/*
 * Calcula la similitud entre un usuario y una película
 * usando un método provisional (dummy).
 * Más adelante se reemplaza con Coseno de Similaridad real
 * basado en calificaciones de usuarios similares.
 * ---------------------------------------------------------
 * movieId: ID de la película.
 * userId: ID del usuario.
 */
double similitudDummy(int movieId, int userId) {
    return 1.0;  // Placeholder
}

/*
 * Calcula la similitud entre dos usuarios usando
 * COSENO DE SIMILITUD REAL.
 * --------------------------------------------------------
 * u1 y u2: estructuras Usuario a comparar.
 * totalPeliculas: cuántas películas existen.
 */

void VectorUsuario(const Usuario &u, int totalPeliculas, int vectorCalif[]) {
    // Inicializar todo en -1
    for (int i = 0; i < totalPeliculas; i++)
        vectorCalif[i] = -1;

    // Llenar con las calificaciones que sí hizo
    for (int i = 0; i < u.numCalificaciones; i++) {
        int id = u.calificaciones[i].idPelicula;  // id real
        vectorCalif[id - 1] = u.calificaciones[i].puntuacion;
    }
}


double calcularSimilitudUsuarios(const Usuario &u1, const Usuario &u2, int totalPeliculas) {

    int v1[200], v2[200]; // tamaño suficiente
    VectorUsuario(u1, totalPeliculas, v1);
    VectorUsuario(u2, totalPeliculas, v2);

    double dot = 0, mag1 = 0, mag2 = 0;

    for (int i = 0; i < totalPeliculas; i++) {
        int r1 = u1.calificaciones[i].puntuacion;
        int r2 = u2.calificaciones[i].puntuacion;

        if (r1 != -1 && r2 != -1) {  
            dot += r1 * r2;
            mag1 += r1 * r1;
            mag2 += r2 * r2;
        }
    }

    if (mag1 == 0 || mag2 == 0)
        return 0;

    return dot / (sqrt(mag1) * sqrt(mag2));
}


/*
 * Genera recomendaciones basadas en:
 * - Usuario similar encontrado por Coseno de Similaridad.
 * - Películas que el usuario similar calificó bien.
 * - Películas que el usuario actual NO ha visto.
 * --------------------------------------------------------
 * userId: ID del usuario que solicita recomendaciones.
 * peliculas[]: catálogo de películas.
 * totalPeliculas: cuántas existen.
 */
void generarRecomendaciones(int userId,
                            Pelicula peliculas[],
                            int totalPeliculas)
{
    cout << "\n*** GENERANDO RECOMENDACIONES BASADAS EN COSENO ***\n";

    // Buscar al usuario actual
    int idxActual = -1;
    for (int i = 0; i < totalUsuarios; i++) {
        if (usuarios[i].id == userId) {
            idxActual = i;
            break;
        }
    }

    if (idxActual == -1) {
        cout << "Usuario no encontrado.\n";
        return;
    }

    // Buscar usuario más parecido
    double mejorSim = -1;
    int usuarioSimilar = -1;

    for (int i = 0; i < totalUsuarios; i++) {
        if (i == idxActual) continue;

        double sim = calcularSimilitudUsuarios(usuarios[idxActual], usuarios[i], totalPeliculas);

        if (sim > mejorSim) {
            mejorSim = sim;
            usuarioSimilar = i;
        }
    }

    if (usuarioSimilar == -1 || mejorSim <= 0) {
        cout << "No hay suficientes datos para recomendar.\n";
        return;
    }

    cout << "\nUsuario más similar encontrado: "
         << usuarios[usuarioSimilar].nombre
         << " (Similitud = " << mejorSim << ")\n\n";

    cout << "--- RECOMENDACIONES ---\n";

    bool encontro = false;

 // Mostrar recomendaciones del usuario más similar
for (int i = 0; i < usuarios[usuarioSimilar].numCalificaciones; i++) {

    int idPeliSimilar = usuarios[usuarioSimilar].calificaciones[i].idPelicula;
    int califSimilar = usuarios[usuarioSimilar].calificaciones[i].puntuacion;

    // Solo recomendar si al usuario similar realmente le gusto mucho (>=4)
    if (califSimilar >= 4) {

        // Verificar si el usuario actual ya la vio
        bool yaVio = false;
        for (int j = 0; j < usuarios[idxActual].numCalificaciones; j++) {
            if (usuarios[idxActual].calificaciones[j].idPelicula == idPeliSimilar) {
                yaVio = true;
                break;
            }
        }

        if (!yaVio) {

            // Buscar la película por ID real
            int indexPeli = -1;
            for (int p = 0; p < totalPeliculas; p++) {
                if (peliculas[p].id == idPeliSimilar) {
                    indexPeli = p;
                    break;
                }
            }

            if (indexPeli != -1) {
                cout << "- " << peliculas[indexPeli].titulo
                     << "  | Calificacion del usuario similar: "
                     << califSimilar << "\n";

                encontro = true;
            }
        }
    }
}

if (!encontro)
    cout << "No hay recomendaciones disponibles.\n";
}

