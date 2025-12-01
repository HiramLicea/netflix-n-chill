// Funciones usadas en este codigo:
// strtok es una funcion que sirve para extraer pedazos de una cadena llamados tokens y usa delimitadores (en este caso ","). Cada que la funcion encuentra un delimitador, esta lo corta. Esta es su sintaxis: char* token = strtok(cadena, delimitador);
// getline sirve para leer cadenas de caracteres e irlos guardando en un arreglo y se detiene en saltos de linea o en un valor maximo. Tambien agrega un \0 al final.
// atoi es una funcion que convierte una cadena de char[] a numeros enteros como una cadena "1995" la convierte a un entero 1995 y es necesaria porque strtok siempre devuelve texto.
// strcpy sirve para copiar un arreglo de caracteres a otro arreglo diferente, sintaxis: strcpy(destino, origen) copia TODA la cadena de origen dentro de destino, incluyendo el \0 final. Es necesario porque en C++ las cadenas no se asignan conun =.
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
    totalPeliculas = 0; // no hay peliculas cargadas por lo tanto igual a 0

    ifstream archivo("C:/Users/Toshiba/netflix-n-chill/data/peliculas.csv"); // funcion de la libreria fstream para cargar el .csv con los datos limpios,"archivo" es un objeto de tipo ifstream.
    if (!archivo.is_open())
    {
        cout << "ERROR: No se pudo abrir el archivo CSV\n";
    }
    else
    {
        cout << "Archivo CSV cargado correctamente\n";

        mapaPeliculas.clear();  // Limpia para evitar basura previa

    for (int i = 0; i < totalPeliculas; i++) {
        mapaPeliculas[peliculas[i].id] = i;
    }

    }




    char linea[400];             // arreglo linea que ira guardando linea por linea que se lee del archivo .csv
    archivo.getline(linea, 400); // sirve para obtener solo la primera fila del .csv la cual queremos evitar procesar (ID, Tiulo, etc...)

    // con este ciclo procesaremos todas las peliculas apartir de la segunda fila
    for (int i = 0; i < MAX_PELICULAS; i++)
    {
        if (!archivo.getline(linea, 400))
            break; // si ya no hay mas filas, el ciclo se detiene

        char *token = strtok(linea, ","); // extraemos el primer dato de la pelicula: ID
        peliculas[i].id = atoi(token);    // atoi convierte la cadena de numeros en ID a un entero.

        token = strtok(NULL, ",");
        strcpy(peliculas[i].titulo, token); // strcpy copia el texto del token (que strtok encontró) dentro del campo titulo de la estructura

        token = strtok(NULL, ",");
        strcpy(peliculas[i].genero, token);

        token = strtok(NULL, ",");
        peliculas[i].anio = atoi(token);

        totalPeliculas++; // actualiza el contador
    }
}

// Esta función recibe la lista de películas ya cargadas y el número total de películas para imprimirlas.
// La funcion recibe un arreglo peliculas[] de tipo Pelicula, este fue definido en pelicus.h, cada elemento del arreglo es un struct Pelicula completo
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
    if (peliculaConCalificaciones(idEliminar, usuarios, totalUsuarios)) {
        cout << "ERROR: No se puede eliminar la pelicula porque tiene calificaciones.\n";
        return;
    }

    int index = buscarPeliculaPorID(peliculas, totalPeliculas, idEliminar);

    if (index == -1) {
        cout << "Pelicula NO encontrada.\n";
        return;
    }

    for (int i = index; i < totalPeliculas - 1; i++) {
        peliculas[i] = peliculas[i + 1];
    }

    totalPeliculas--;
    cout << "Pelicula eliminada correctamente.\n";
}


bool peliculaConCalificaciones(int idPelicula, Usuario usuarios[], int totalUsuarios) {
    for (int i = 0; i < totalUsuarios; i++) {
        for (int j = 0; j < usuarios[i].numCalificaciones; j++) {
            if (usuarios[i].calificaciones[j].idPelicula == idPelicula) {
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

