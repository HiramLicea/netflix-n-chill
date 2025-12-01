#include <iostream>
#include "peliculas.h"
#include "usuarios.h"
#include "recomendaciones.h"
#include "ratings.h"

using namespace std;

int main()
{
    Pelicula peliculas[MAX_PELICULAS];
    int totalPeliculas = 0;

    Usuario usuarios[MAX_USUARIOS];
    int totalUsuarios = 0;

    cargarPeliculas(peliculas, totalPeliculas);
    cargarRatings(usuarios, totalUsuarios);

    int opcion;

    do
    {
        cout << "\n===== NETFLIX-N-CHILL =====\n";
        cout << "1. Gestionar peliculas\n";
        cout << "2. Registrar nuevo usuario\n";
        cout << "3. Ingresar calificacion\n";
        cout << "4. Solicitar recomendaciones\n";
        cout << "5. Salir\n";
        cout << "=============================\n";
        cout << "Elige una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
        {
            int opPeli;
            cout << "\n--- GESTION DE PELICULAS ---\n";
            cout << "1. Mostrar catalogo\n";
            cout << "2. Modificar pelicula\n";
            cout << "3. Eliminar pelicula\n";
            cout << "4. Agregar nueva pelicula\n";
            cout << "5. Regresar\n";
            cout << ">> ";
            cin >> opPeli;

            switch (opPeli)
            {
            case 1:
                mostrarPeliculas(peliculas, totalPeliculas);
                break;
            case 2:
                modificarPelicula(peliculas, totalPeliculas);
                break;
            case 3:
            {
                int idEliminar;
                cout << "ID a eliminar: ";
                cin >> idEliminar;
                eliminarPelicula(peliculas, totalPeliculas, idEliminar, usuarios, totalUsuarios);
                break;
            }
            case 4:
            {
                if (totalPeliculas >= MAX_PELICULAS)
                    cout << "Memoria llena.\n";
                else
                {
                    Pelicula nueva;
                    cout << "ID: ";
                    cin >> nueva.id;
                    cin.ignore();
                    cout << "Titulo: ";
                    cin.getline(nueva.titulo, 200);
                    cout << "Genero: ";
                    cin.getline(nueva.genero, 100);
                    cout << "Año: ";
                    cin >> nueva.anio;
                    peliculas[totalPeliculas++] = nueva;
                    cout << "Guardado.\n";
                }
                break;
            }
            }
            break;
        }

        case 2:
            registrarUsuario(usuarios, totalUsuarios);
            break;

        case 3:
            calificarPelicula(usuarios, totalUsuarios, peliculas, totalPeliculas);
            break;

        case 4:
        {
            int idU;
            cout << "Ingrese su ID de usuario: ";
            cin >> idU;
            generarRecomendaciones(idU, usuarios, totalUsuarios, peliculas, totalPeliculas);
            break;
        }

        case 5:
            cout << "Guardando datos y saliendo...\n";
            break;

        default:
            cout << "Opcion invalida.\n";
        }

    } while (opcion != 5);

    return 0;
}