#include "peliculas.h"
#include "usuarios.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

using namespace std;

Pelicula peliculas[MAX_PELICULAS];
int totalPeliculas = 0;

std::unordered_map<int, int> mapaPeliculas;

void cargarPeliculas(Pelicula peliculas[], int &totalPeliculas)
{
    totalPeliculas = 0;

    ifstream archivo("peliculas.csv");

    if (!archivo.is_open())
    {
        cout << "ERROR: No se pudo abrir 'peliculas.csv'.\n";
        return;
    }

    mapaPeliculas.clear();

    char linea[400];
    archivo.getline(linea, 400);

    for (int i = 0; i < MAX_PELICULAS; i++)
    {
        if (!archivo.getline(linea, 400))
            break;

        char *token = strtok(linea, ",");
        if (token == NULL)
            continue;

        peliculas[i].id = atoi(token);

        token = strtok(NULL, ",");
        if (token != NULL)
            strcpy(peliculas[i].titulo, token);

        token = strtok(NULL, ",");
        if (token != NULL)
            strcpy(peliculas[i].genero, token);

        token = strtok(NULL, ",");
        if (token != NULL)
            peliculas[i].anio = atoi(token);

        mapaPeliculas[peliculas[i].id] = totalPeliculas;
        totalPeliculas++;
    }

    archivo.close();
}

void mostrarPeliculas(Pelicula peliculas[], int totalPeliculas)
{
    for (int i = 0; i < totalPeliculas; i++)
    {
        cout << peliculas[i].id << ". "
             << peliculas[i].titulo << " ("
             << peliculas[i].anio << ") ["
             << peliculas[i].genero << "]\n";
    }
}

void modificarPelicula(Pelicula peliculas[], int totalPeliculas)
{
    int id;
    cout << "ID a modificar: ";
    cin >> id;

    if (mapaPeliculas.count(id))
    {
        int i = mapaPeliculas[id];

        cout << "Titulo actual: " << peliculas[i].titulo << "\nNuevo titulo: ";
        cin.ignore();
        cin.getline(peliculas[i].titulo, 200);

        cout << "Genero actual: " << peliculas[i].genero << "\nNuevo genero: ";
        cin.getline(peliculas[i].genero, 100);

        cout << "Anio actual: " << peliculas[i].anio << "\nNuevo anio: ";
        cin >> peliculas[i].anio;

        cout << "Pelicula modificada.\n";
    }
    else
    {
        cout << "ID no encontrado.\n";
    }
}

void eliminarPelicula(Pelicula peliculas[], int &totalPeliculas)
{
    int id;
    cout << "Ingrese el ID: ";
    cin >> id;
}

void eliminarPelicula(Pelicula peliculas[], int &totalPeliculas, int idEliminar, Usuario usuarios[], int totalUsuarios)
{
    if (peliculaConCalificaciones(idEliminar, usuarios, totalUsuarios))
    {
        cout << "ERROR: Tiene calificaciones asociadas.\n";
        return;
    }

    int index = buscarPeliculaPorID(peliculas, totalPeliculas, idEliminar);

    if (index == -1)
    {
        cout << "Pelicula NO encontrada.\n";
        return;
    }

    for (int i = index; i < totalPeliculas - 1; i++)
    {
        peliculas[i] = peliculas[i + 1];
        mapaPeliculas[peliculas[i].id] = i;
    }

    mapaPeliculas.erase(idEliminar);

    totalPeliculas--;
    cout << "Pelicula eliminada.\n";
}

bool peliculaConCalificaciones(int idPelicula, Usuario usuarios[], int totalUsuarios)
{
    for (int i = 0; i < totalUsuarios; i++)
    {
        for (int j = 0; j < usuarios[i].numCalificaciones; j++)
        {
            if (usuarios[i].calificaciones[j].idPelicula == idPelicula)
            {
                return true;
            }
        }
    }
    return false;
}

int buscarPeliculaPorID(Pelicula peliculas[], int totalPeliculas, int idBuscado)
{
    if (mapaPeliculas.count(idBuscado))
        return mapaPeliculas[idBuscado];
    return -1;
}