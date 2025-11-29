#include <iostream>
#include "peliculas.h"
#include "usuarios.h"
using namespace std;

int main()
{

    Pelicula peliculas[MAX_PELICULAS];
    int totalPeliculas = 0;

    Usuario usuarios[MAX_USUARIOS];
    int totalUsuarios = 0;

    cargarPeliculas(peliculas, totalPeliculas);

    int opcion;

    do
    {
        cout << "\n===== MENU PRINCIPAL =====\n";
        cout << "1. Gestionar peliculas\n";
        cout << "2. Registrar nuevo usuario\n";
        cout << "3. Ingresar calificacion\n";
        cout << "4. Solicitar recomendaciones\n";
        cout << "5. Salir\n";
        cout << "===========================\n";
        cout << "Elige una opcion: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
        {
            int opPeli;
            cout << "\n--- GESTION DE PELICULAS ---\n";
            cout << "1. Mostrar peliculas\n";
            cout << "2. Modificar pelicula\n";
            cout << "3. Eliminar pelicula\n";
            cout << "4. Agregar nueva pelicula\n";
            cout << "5. Regresar\n";
            cout << "Elige una opcion: ";
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
                // AGREGAR PELÍCULA NUEVA
                if (totalPeliculas >= MAX_PELICULAS)
                {
                    cout << "Limite de peliculas alcanzado.\n";
                }
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

                    peliculas[totalPeliculas] = nueva;
                    totalPeliculas++;

                    cout << "Pelicula agregada exitosamente.\n";
                }
                break;
            }
            case 5:
                break;

            default:
                cout << "Opcion invalida.\n";
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
            cout << "Ingrese el ID del usuario para recomendar: ";
            cin >> idU;

            generarRecomendaciones(idU, peliculas, totalPeliculas);
            break;
        }

        case 5:
            cout << "Saliendo...\n";
            break;

        default:
            cout << "Opcion invalida.\n";
        }

    } while (opcion != 5);

    return 0;
}
