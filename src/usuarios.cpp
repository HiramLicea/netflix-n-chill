#include "usuarios.h"
#include <iostream>
#include <cstring>
#include "peliculas.h"
#include "usuarios.h"

Usuario usuarios[MAX_USUARIOS];
int totalUsuarios = 0;


using namespace std;

void registrarUsuario(Usuario usuarios[], int &totalUsuarios)
{
    if (totalUsuarios >= MAX_USUARIOS)
    {
        cout << "No se pueden registrar mas usuarios." << endl;
        return;
    }

    Usuario nuevoUsuario;
    nuevoUsuario.id = totalUsuarios + 1; // Asignar un ID unico
    cout << "Ingrese el nombre del usuario: ";
    cin.ignore();
    cin.getline(nuevoUsuario.nombre, 100);
    nuevoUsuario.numCalificaciones = 0;

    usuarios[totalUsuarios] = nuevoUsuario;
    totalUsuarios++;

    cout << "Usuario registrado con ID: " << nuevoUsuario.id << endl;
}

void calificarPelicula(Usuario usuarios[], int totalUsuarios, Pelicula peliculas[], int totalPeliculas)
{
    int idUsuario;
    cout << "Ingrese el ID del usuario: ";
    cin >> idUsuario;

    int indiceUsuario = buscarUsuarioPorID(idUsuario, usuarios, totalUsuarios);
    if (indiceUsuario == -1)
    {
        cout << "Usuario no encontrado." << endl;
        return;
    }

    int idPelicula;
    cout << "Ingrese el ID de la pelicula a calificar: ";
    cin >> idPelicula;

    int indicePelicula = -1; // Ubicacion de la pelicula
    bool peliculaEncontrada = false;

    for (int i = 0; i < totalPeliculas; i++)
    {
        if (peliculas[i].id == idPelicula)
        {
            peliculaEncontrada = true;
            indicePelicula = i; // Indice para mostrar datos despues
            break;
        }
    }

    if (!peliculaEncontrada)
    {
        cout << "No existe la pelicula." << endl;
        return;
    }

    // Datos de pelicula encontrada
    float promedioActual = promedioPelicula(idPelicula, usuarios, totalUsuarios);
    cout << "\n--- DATOS DE LA PELICULA ---" << endl;
    cout << "Titulo: " << peliculas[indicePelicula].titulo << endl;
    cout << "Genero: " << peliculas[indicePelicula].genero << endl;
    cout << "Fecha: " << peliculas[indicePelicula].anio << endl;
    cout << "Promedio actual: " << promedioActual << endl;
    cout << "----------------------------" << endl;

    if (usuarios[indiceUsuario].numCalificaciones >= MAX_PELICULAS_VISTAS)
    {
        cout << "El usuario ha alcanzado el maximo de calificaciones." << endl;
        return;
    }

    int puntuacion;
    cout << "Ingrese su puntuacion (1-5): ";
    cin >> puntuacion;

    if (puntuacion < 1 || puntuacion > 5)
    {
        cout << "Puntuacion invalida." << endl;
        return;
    }

    Calificacion nuevaCalificacion;
    nuevaCalificacion.idPelicula = idPelicula;
    nuevaCalificacion.puntuacion = puntuacion;

    usuarios[indiceUsuario].calificaciones[usuarios[indiceUsuario].numCalificaciones] = nuevaCalificacion;
    usuarios[indiceUsuario].numCalificaciones++;

    cout << "Pelicula calificada exitosamente." << endl;
}

float promedioPelicula(int idPelicula, Usuario usuarios[], int totalUsuarios)
{
    int sumaPuntuaciones = 0;
    int contadorPuntuaciones = 0;

    for (int i = 0; i < totalUsuarios; i++)
    {
        for (int j = 0; j < usuarios[i].numCalificaciones; j++)
        {
            if (usuarios[i].calificaciones[j].idPelicula == idPelicula)
            {
                sumaPuntuaciones += usuarios[i].calificaciones[j].puntuacion;
                contadorPuntuaciones++;
            }
        }
    }

    if (contadorPuntuaciones == 0)
    {
        return 0.0f; // No hay calificaciones
    }

    return static_cast<float>(sumaPuntuaciones) / contadorPuntuaciones;
}

int buscarUsuarioPorID(int id, Usuario usuarios[], int totalUsuarios)
{
    for (int i = 0; i < totalUsuarios; i++)
    {
        if (usuarios[i].id == id)
        {
            return i;
        }
    }
    return -1;
}
