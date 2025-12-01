#include "ratings.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

// -------------------------------------------------------------
// Guarda un rating en ratings.csv (append)
// -------------------------------------------------------------
void guardarRating(int userId, int movieId, int rating) {
    ofstream file("ratings.csv", ios::app);

    if (!file.is_open()) {
        cout << "Error al abrir ratings.csv para escribir\n";
        return;
    }

    file << userId << "," << movieId << "," << rating << "\n";
    file.close();
}

// -------------------------------------------------------------
// Cargar ratings desde ratings.csv hacia las estructuras
// -------------------------------------------------------------
void cargarRatings(Usuario usuarios[], int totalUsuarios) {
    ifstream file("ratings.csv");

    if (!file.is_open()) {
        cout << "ratings.csv no existe o esta vacío. Creando uno nuevo...\n";
        ofstream crear("ratings.csv");
        crear.close();
        return;
    }

    string linea;

    while (getline(file, linea)) {
        if (linea == "") continue;

        stringstream ss(linea);
        string uStr, pStr, rStr;

        getline(ss, uStr, ',');
        getline(ss, pStr, ',');
        getline(ss, rStr, ',');

        int userId  = stoi(uStr);
        int movieId = stoi(pStr);
        int rating  = stoi(rStr);

        // Buscar al usuario correspondiente
        for (int i = 0; i < totalUsuarios; i++) {
            if (usuarios[i].id == userId) {

                int idx = usuarios[i].numCalificaciones;

                usuarios[i].calificaciones[idx].idPelicula = movieId;
                usuarios[i].calificaciones[idx].puntuacion  = rating;
                usuarios[i].numCalificaciones++;

                break;
            }
        }
    }

    file.close();
}
