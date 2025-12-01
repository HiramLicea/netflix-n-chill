#include "peliculas.h"
#include "usuarios.h"
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

Pelicula peliculas[MAX_PELICULAS];
int totalPeliculas = 0;

std::unordered_map<int, int> mapaPeliculas;

void cargarPeliculas(Pelicula peliculas[], int &totalPeliculas)
{
    totalPeliculas = 0;

<<<<<<< HEAD
=======
    ifstream archivo("peliculas.csv");
>>>>>>> 7b97e2e6125ff9075f4b59d38dc1f624b48dbfad
    if (!archivo.is_open())
    {
        cout << "ERROR: No se pudo abrir el archivo CSV\n";
    }
    else
    {
        cout << "Archivo CSV cargado correctamente\n";

        mapaPeliculas.clear();

        for (int i = 0; i < totalPeliculas; i++)
        {
            mapaPeliculas[peliculas[i].id] = i;
        }
    }

    char linea[400];
    archivo.getline(linea, 400);

    // con este ciclo procesaremos todas las peliculas apartir de la segunda fila
    for (int i = 0; i < MAX_PELICULAS; i++)
    {
        if (!archivo.getline(linea, 400))
            break; // si ya no hay mas filas, el ciclo se detiene

        char *token = strtok(linea, ",");
        peliculas[i].id = atoi(token);

        token = strtok(NULL, ",");
        strcpy(peliculas[i].titulo, token);

        token = strtok(NULL, ",");
        strcpy(peliculas[i].genero, token);

        token = strtok(NULL, ",");
        peliculas[i].anio = atoi(token);

        totalPeliculas++;
    }
}

void mostrarPeliculas(Pelicula peliculas[], int totalPeliculas)
{
    cout << "\nLISTA DE PELICULAS\n";
    for (int i = 0; i < totalPeliculas; i++)
    {
        cout << peliculas[i].id << " | "
             << peliculas[i].titulo << " | "
             << peliculas[i].genero << " | "
             << peliculas[i].anio << "\n";
    }
}

void modificarPelicula(Pelicula peliculas[], int totalPeliculas)
{
    int id;
    cout << "Ingrese el ID de la pelicula a modificar: ";
    cin >> id;

    for (int i = 0; i < totalPeliculas; i++)
    {
        if (peliculas[i].id == id)
        {
            cout << "Titulo actual: " << peliculas[i].titulo << "\nNuevo titulo: ";
            cin.ignore();
            cin.getline(peliculas[i].titulo, 200);

            cout << "Genero actual: " << peliculas[i].genero << "\nNuevo genero: ";
            cin.getline(peliculas[i].genero, 100);

            cout << "Anio actual: " << peliculas[i].anio << "\nNuevo anio: ";
            cin >> peliculas[i].anio;

            cout << "Pelicula modificada correctamente.\n";
            return;
        }
    }

    cout << "No existe una pelicula con ese ID.\n";
}

void eliminarPelicula(Pelicula peliculas[], int &totalPeliculas)
{
    int id;
    cout << "Ingrese el ID de la pelicula a eliminar: ";
    cin >> id;

    for (int i = 0; i < totalPeliculas; i++)
    {
        if (peliculas[i].id == id)
        {
            for (int j = i; j < totalPeliculas - 1; j++)
            {
                peliculas[j] = peliculas[j + 1];
            }

            totalPeliculas--;
            cout << "Pelicula eliminada correctamente.\n";
            return;
        }
    }
    cout << "No existe una pelicula con ese ID.\n";
}

void eliminarPelicula(Pelicula peliculas[], int &totalPeliculas, int idEliminar,
                      Usuario usuarios[], int totalUsuarios)
{
    if (peliculaConCalificaciones(idEliminar, usuarios, totalUsuarios))
    {
        cout << "ERROR: No se puede eliminar la pelicula porque tiene calificaciones.\n";
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
    }

    totalPeliculas--;
    cout << "Pelicula eliminada correctamente.\n";
}

bool peliculaConCalificaciones(int idPelicula, Usuario usuarios[], int totalUsuarios)
{
    for (int i = 0; i < totalUsuarios; i++)
    {
        for (int j = 0; j < usuarios[i].numCalificaciones; j++)
        {
            if (usuarios[i].calificaciones[j].idPelicula == idPelicula)
            {
                return true; // La película tiene al menos UNA calificación
            }
        }
    }
    return false; // No tiene calificaciones
}

int buscarPeliculaPorID(Pelicula peliculas[], int totalPeliculas, int idBuscado)
{
    for (int i = 0; i < totalPeliculas; i++)
    {
        if (peliculas[i].id == idBuscado)
        {
            return i;
        }
    }
    return -1;
}
