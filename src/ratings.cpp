#include "ratings.h"
#include "usuarios.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>

using namespace std;

void guardarRating(int userId, int movieId, int rating)
{
    ofstream file("ratings.csv", ios::app);

    if (!file.is_open())
    {
        file.open("ratings.csv", ios::app);
    }

    if (file.is_open())
    {
        file << userId << "," << movieId << "," << rating << "\n";
        file.close();
    }
}

void cargarRatings(Usuario usuarios[], int totalUsuarios)
{
    ifstream file("ratings.csv");

    if (!file.is_open())
    {
        file.open("ratings.csv");
    }

    if (!file.is_open())
    {
        return;
    }

    string linea;
    int cargados = 0;

    while (getline(file, linea))
    {
        if (linea.length() < 3)
            continue;

        stringstream ss(linea);
        string uStr, pStr, rStr;

        if (!getline(ss, uStr, ','))
            continue;
        if (!getline(ss, pStr, ','))
            continue;
        if (!getline(ss, rStr, ','))
            continue;

        int userId = atoi(uStr.c_str());
        int movieId = atoi(pStr.c_str());
        int rating = atoi(rStr.c_str());

        if (userId == 0 && movieId == 0)
            continue;

        for (int i = 0; i < totalUsuarios; i++)
        {
            if (usuarios[i].id == userId)
            {
                if (usuarios[i].numCalificaciones < MAX_PELICULAS_VISTAS)
                {
                    int idx = usuarios[i].numCalificaciones;
                    usuarios[i].calificaciones[idx].idPelicula = movieId;
                    usuarios[i].calificaciones[idx].puntuacion = rating;
                    usuarios[i].numCalificaciones++;
                    cargados++;
                }
                break;
            }
        }
    }
    file.close();
}