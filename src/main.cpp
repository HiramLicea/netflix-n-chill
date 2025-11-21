#include <iostream>
#include "peliculas.h"
#include "usuarios.h"
using namespace std;

int main()
{
    Pelicula peliculas[MAX_PELICULAS];
    int totalPeliculas = 0;

    Usuario usuarios[MAX_PELICULAS];
    int totalUsuarios = 0;

    cargarPeliculas(peliculas, totalPeliculas);

    int opcion;

    do
    {
        cout << "\n MENU PRINCIPAL \n";
        cout << "1. Gestionar peliculas\n";
        cout << "2. Registrar nuevo usuario\n";
        cout << "3. Ingresar calificaciones\n";
        cout << "4. Solicitar recomendaciones\n";
        cout << "5. Salir\n";
        cout << "===========================\n";
        cout << "Elige una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            mostrarPeliculas(peliculas, totalPeliculas); // actualmente solo sirve para cargar el .csv
            break;

        case 2:
            registrarUsuario(usuarios, totalUsuarios);
            break;

        case 3:
            calificarPelicula(usuarios, totalUsuarios, peliculas, totalPeliculas);
            break;

        case 4:
            cout << "\nFUNCION AUN NO IMPLEMENTADA\n";
            break;

        case 5:
            cout << "Saliendo...\n";
            break;

        default:
            cout << "Opcion invalida.\n";
        }

    } while (opcion != 5);

    return 0;
}
