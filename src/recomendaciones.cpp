#include <iostream>
#include <cmath>

#include "recomendaciones.h"
#include "usuarios.h"
#include "peliculas.h"
#include "hashTable.h"

using namespace std;

// ---------------------------------------------------------
// Construye tabla hash de películas que vio el usuario
// ---------------------------------------------------------
void construirTablaHashUsuario(const Usuario &u, HashTable &tabla) {

    for (int i = 0; i < u.numCalificaciones; i++) {
        int idP = u.calificaciones[i].idPelicula;
        int score = u.calificaciones[i].puntuacion;

        hashInsert(tabla, idP, score);
    }
}

// ---------------------------------------------------------
bool usuarioYaVioPeliculaHash(const HashTable &tabla, int idPelicula) {
    return hashContains(tabla, idPelicula);
}

// ---------------------------------------------------------
void VectorUsuario(const Usuario &u, int totalPeliculas, int vect[]) {

    for (int i = 0; i < totalPeliculas; i++)
        vect[i] = -1;

    for (int i = 0; i < u.numCalificaciones; i++) {
        int id = u.calificaciones[i].idPelicula;

        if (mapaPeliculas.count(id)) {
            int idx = mapaPeliculas[id];
            vect[idx] = u.calificaciones[i].puntuacion;
        }
    }
}

// ---------------------------------------------------------
double calcularSimilitudUsuarios(const Usuario &u1, const Usuario &u2) {

    int v1[200], v2[200];
    VectorUsuario(u1, totalPeliculas, v1);
    VectorUsuario(u2, totalPeliculas, v2);

    double dot = 0, mag1 = 0, mag2 = 0;

    for (int i = 0; i < totalPeliculas; i++) {

        int r1 = v1[i];
        int r2 = v2[i];

        if (r1 != -1 && r2 != -1) {
            dot += r1 * r2;
            mag1 += r1 * r1;
            mag2 += r2 * r2;
        }
    }

    if (mag1 == 0 || mag2 == 0) return 0;

    return dot / (sqrt(mag1) * sqrt(mag2));
}
// ---------------------------------------------------------
bool usuarioYaVioPelicula(int userId, int movieId, Usuario usuarios[], int totalUsuarios) {
    int idxU = buscarUsuarioPorID(userId, usuarios, totalUsuarios);
    if (idxU == -1) return false;

    for (int k = 0; k < usuarios[idxU].numCalificaciones; k++) {
        if (usuarios[idxU].calificaciones[k].idPelicula == movieId)
            return true;
    }
    return false;
}
// ---------------------------------------------------------
void generarRecomendaciones(int idUsuario, Usuario usuarios[], int totalUsuarios,Pelicula peliculas[], int totalPeliculas)
{
    cout << "\n*** GENERANDO RECOMENDACIONES BASADAS EN COSENO ***\n";

    int idxActual = buscarUsuarioPorID(idUsuario, usuarios, totalUsuarios);
    if (idxActual == -1) {
        cout << "Usuario no encontrado.\n";
        return;
    }

    // Buscar usuario más parecido
    double mejorSim = -1;
    int usuarioSimilar = -1;

    for (int i = 0; i < totalUsuarios; i++) {
        if (i == idxActual) continue;

        double sim = calcularSimilitudUsuarios(usuarios[idxActual], usuarios[i]);


        if (sim > mejorSim) {
            mejorSim = sim;
            usuarioSimilar = i;
        }
    }

    if (usuarioSimilar == -1 || mejorSim <= 0) {
        cout << "No hay suficientes datos para recomendar.\n";
        return;
    }

    cout << "\nUsuario más similar: "
         << usuarios[usuarioSimilar].nombre
         << " (Similitud = " << mejorSim << ")\n\n";

    cout << "--- RECOMENDACIONES ---\n";

    bool encontro = false;

    // Recorrer calificaciones del usuario similar
    for (int c = 0; c < usuarios[usuarioSimilar].numCalificaciones; c++) {

        int idPeliSimilar = usuarios[usuarioSimilar].calificaciones[c].idPelicula;
        int califSimilar  = usuarios[usuarioSimilar].calificaciones[c].puntuacion;

        if (califSimilar < 4) continue;  // Solo recomendar películas buenas
        if (usuarioYaVioPelicula(idUsuario, idPeliSimilar, usuarios, totalUsuarios)) continue;

        // Usar tabla hash para encontrar la película
        if (mapaPeliculas.count(idPeliSimilar)) {

            int indexPeli = mapaPeliculas[idPeliSimilar];

            cout << "- " << peliculas[indexPeli].titulo
                 << "  | Calificacion del usuario similar: "
                 << califSimilar << "\n";

            encontro = true;
        }
    }

    if (!encontro)
        cout << "No hay recomendaciones disponibles.\n";
}

// ---------------------------------------------------------
void mostrarTopRecomendaciones() {
    cout << "Funcion mostrarTopRecomendaciones aun no implementada.\n";
}
