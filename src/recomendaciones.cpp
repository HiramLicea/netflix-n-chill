#include <iostream>
#include <cmath>
#include "recomendaciones.h"
#include "usuarios.h"
#include "peliculas.h"
#include "hashTable.h"

using namespace std;

// ---------------------------------------------------------
// Construir vector de usuario
// ---------------------------------------------------------
void construirVectorUsuario(const Usuario &u, int totalPeliculas, int vect[], unordered_map<int,int> &mapa) {
    for (int i = 0; i < totalPeliculas; i++)
        vect[i] = -1;

    for (int k = 0; k < u.numCalificaciones; k++) {
        int id = u.calificaciones[k].idPelicula;
        if (mapa.count(id)) {
            vect[ mapa[id] ] = u.calificaciones[k].puntuacion;
        }
    }
}

// ---------------------------------------------------------
double calcularSimilitudUsuarios(const Usuario &u1, const Usuario &u2) {
    extern int totalPeliculas;
    extern unordered_map<int,int> mapaPeliculas;

    int v1[300], v2[300];

    construirVectorUsuario(u1, totalPeliculas, v1, mapaPeliculas);
    construirVectorUsuario(u2, totalPeliculas, v2, mapaPeliculas);

    double dot = 0, mag1 = 0, mag2 = 0;

    for (int i = 0; i < totalPeliculas; i++) {
        if (v1[i] != -1 && v2[i] != -1) {
            dot += v1[i] * v2[i];
            mag1 += v1[i] * v1[i];
            mag2 += v2[i] * v2[i];
        }
    }

    if (mag1 == 0 || mag2 == 0) return 0;
    return dot / (sqrt(mag1) * sqrt(mag2));
}

// ---------------------------------------------------------
void mostrarTopRecomendaciones(Recomendacion r[], int total) {
    for (int i = 0; i < total; i++) {
        cout << i+1 << ". Pelicula ID " << r[i].idPelicula
             << "  | Puntaje = " << r[i].puntaje << "\n";
    }
}

// ---------------------------------------------------------
void generarRecomendaciones(int idUsuario,
                            Usuario usuarios[],
                            int totalUsuarios,
                            Pelicula peliculas[],
                            int totalPeliculas)
{
    cout << "\nGENERANDO RECOMENDACIONES...\n\n";

    int idxU = buscarUsuarioPorID(idUsuario, usuarios, totalUsuarios);
    if (idxU == -1) {
        cout << "Usuario no encontrado.\n";
        return;
    }

    extern unordered_map<int,int> mapaPeliculas;

    // --- encontrar usuario más similar ---
    double mejorSim = -1;
    int idxSim = -1;

    for (int i = 0; i < totalUsuarios; i++) {
        if (i == idxU) continue;

        double s = calcularSimilitudUsuarios(usuarios[idxU], usuarios[i]);
        if (s > mejorSim) {
            mejorSim = s;
            idxSim = i;
        }
    }

    if (idxSim == -1 || mejorSim <= 0) {
        cout << "No hay suficientes datos.\n";
        return;
    }

    cout << "Usuario similar: " << usuarios[idxSim].nombre
         << " (sim=" << mejorSim << ")\n\n";

    // --- usar HashTable para saber lo que el usuario ya vio ---
    HashTable tablaVistas;

    for (int i = 0; i < usuarios[idxU].numCalificaciones; i++) {
        int idP = usuarios[idxU].calificaciones[i].idPelicula;
        hashInsert(tablaVistas, idP, 1);
    }

    // --- recolectar recomendaciones ---
    Recomendacion recs[200];
    int n = 0;

    for (int i = 0; i < usuarios[idxSim].numCalificaciones; i++) {

        int idP = usuarios[idxSim].calificaciones[i].idPelicula;
        int calif = usuarios[idxSim].calificaciones[i].puntuacion;

        if (calif < 4) continue;              // solo buenas
        if (hashContains(tablaVistas, idP)) continue; // filtrar vistas

        if (mapaPeliculas.count(idP)) {

            double puntaje = calif * mejorSim;

            recs[n++] = { idP, puntaje };
        }
    }

    if (n == 0) {
        cout << "No hay recomendaciones.\n";
        return;
    }

    // --- ordenar con burbuja ---
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-1-i; j++) {
            if (recs[j].puntaje < recs[j+1].puntaje) {
                Recomendacion temp = recs[j];
                recs[j] = recs[j+1];
                recs[j+1] = temp;
            }
        }
    }

    // --- mostrar top ---
    cout << "\nTOP RECOMENDACIONES:\n";
    mostrarTopRecomendaciones(recs, n);
}
