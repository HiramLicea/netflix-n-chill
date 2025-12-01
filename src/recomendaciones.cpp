#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstring> // Para strstr
#include "recomendaciones.h"
#include "usuarios.h"
#include "peliculas.h"
#include "hashTable.h"

using namespace std;

int partition(Recomendacion arr[], int low, int high)
{
    double pivot = arr[high].puntaje;
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (arr[j].puntaje > pivot)
        {
            i++;
            Recomendacion temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    Recomendacion temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return (i + 1);
}

void quickSort(Recomendacion arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void construirVectorUsuario(const Usuario &u, int totalPeliculas, int vect[], unordered_map<int, int> &mapa)
{
    for (int i = 0; i < totalPeliculas; i++)
        vect[i] = -1;

    for (int k = 0; k < u.numCalificaciones; k++)
    {
        int id = u.calificaciones[k].idPelicula;
        if (mapa.count(id))
        {
            vect[mapa[id]] = u.calificaciones[k].puntuacion;
        }
    }
}

double calcularSimilitudUsuarios(const Usuario &u1, const Usuario &u2)
{
    extern int totalPeliculas;
    extern unordered_map<int, int> mapaPeliculas;

    static int v1[5000];
    static int v2[5000];

    construirVectorUsuario(u1, totalPeliculas, v1, mapaPeliculas);
    construirVectorUsuario(u2, totalPeliculas, v2, mapaPeliculas);

    double dot = 0, mag1 = 0, mag2 = 0;

    for (int i = 0; i < totalPeliculas; i++)
    {
        if (v1[i] != -1 && v2[i] != -1)
        {
            dot += v1[i] * v2[i];
            mag1 += v1[i] * v1[i];
            mag2 += v2[i] * v2[i];
        }
    }

    if (mag1 == 0 || mag2 == 0)
        return 0;
    return dot / (sqrt(mag1) * sqrt(mag2));
}

void mostrarTopRecomendaciones(Recomendacion r[], int total, Pelicula peliculas[], int totalPeliculas, Usuario usuarios[], int totalUsuarios)
{
    int limite = (total < 5) ? total : 5;

    cout << "\n----------------------------------------------------------------------------------\n";
    cout << "                         TOP RECOMENDACIONES PERSONALIZADAS                        \n";
    cout << "----------------------------------------------------------------------------------\n";
    cout << " # | Titulo (Fecha) [Genero]                     | Calif. Promedio | Relevancia \n";
    cout << "---|--------------------------------------------|-----------------|--------------\n";

    for (int i = 0; i < limite; i++)
    {
        int indexPeli = -1;
        for (int p = 0; p < totalPeliculas; p++)
        {
            if (peliculas[p].id == r[i].idPelicula)
            {
                indexPeli = p;
                break;
            }
        }

        if (indexPeli != -1)
        {
            float prom = promedioPelicula(peliculas[indexPeli].id, usuarios, totalUsuarios);

            cout << " " << (i + 1) << " | "
                 << peliculas[indexPeli].titulo << " (" << peliculas[indexPeli].anio << ") "
                 << "[" << peliculas[indexPeli].genero << "] | "
                 << prom << " / 5.0      | "
                 << (int)(r[i].puntaje * 100) << "%" << endl;
        }
    }
    cout << "----------------------------------------------------------------------------------\n";
}

void generarRecomendaciones(int idUsuario, Usuario usuarios[], int totalUsuarios, Pelicula peliculas[], int totalPeliculas)
{
    cout << "\n=== SOLICITUD DE RECOMENDACIONES ===\n";
    int idxU = buscarUsuarioPorID(idUsuario, usuarios, totalUsuarios);
    if (idxU == -1)
    {
        cout << "Usuario no encontrado.\n";
        return;
    }

    char generoBuscado[50];
    int anioMin, anioMax;

    cout << "Ingresa el Genero preferido (ej. Comedy, Action): ";
    cin.ignore();
    cin.getline(generoBuscado, 50);

    cout << "Ingresa el rango de fechas.\n";
    cout << " Desde la fecha: ";
    cin >> anioMin;
    cout << " Hasta la fecha: ";
    cin >> anioMax;

    cout << "\nAnalizando base de datos...\n";

    extern unordered_map<int, int> mapaPeliculas;

    double mejorSim = -1;
    int idxSim = -1;

    for (int i = 0; i < totalUsuarios; i++)
    {
        if (i == idxU)
            continue;
        double s = calcularSimilitudUsuarios(usuarios[idxU], usuarios[i]);
        if (s > mejorSim)
        {
            mejorSim = s;
            idxSim = i;
        }
    }

    if (idxSim == -1 || mejorSim <= 0)
    {
        cout << "No se encontraron usuarios con gustos similares suficientes.\n";
        return;
    }

    cout << ">> Perfil compatible encontrado: " << usuarios[idxSim].nombre
         << " (Similitud: " << (int)(mejorSim * 100) << "%)\n";

    HashTable tablaVistas;
    for (int i = 0; i < usuarios[idxU].numCalificaciones; i++)
    {
        int idP = usuarios[idxU].calificaciones[i].idPelicula;
        hashInsert(tablaVistas, idP, 1);
    }

    Recomendacion recs[200];
    int n = 0;

    for (int i = 0; i < usuarios[idxSim].numCalificaciones; i++)
    {
        int idP = usuarios[idxSim].calificaciones[i].idPelicula;
        int calif = usuarios[idxSim].calificaciones[i].puntuacion;

        if (calif < 4)
            continue;
        if (hashContains(tablaVistas, idP))
            continue;

        if (mapaPeliculas.count(idP))
        {
            int idxPeliArreglo = mapaPeliculas[idP];
            Pelicula &p = peliculas[idxPeliArreglo];

            if (p.anio < anioMin || p.anio > anioMax)
                continue;
            if (generoBuscado[0] != '\0' && strstr(p.genero, generoBuscado) == NULL)
                continue;

            double puntaje = calif * mejorSim;
            recs[n++] = {idP, puntaje};
        }
    }

    if (n == 0)
    {
        cout << "\nNo hay recomendaciones que coincidan con tus filtros.\n";
        return;
    }
    quickSort(recs, 0, n - 1);
    mostrarTopRecomendaciones(recs, n, peliculas, totalPeliculas, usuarios, totalUsuarios);
}