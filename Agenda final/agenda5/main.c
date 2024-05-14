//Moises de Jesus Juarez Alvarez
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "header.h"

int main(int argc, char *argv[]){
    Agenda agenda[T_AGENDA];
    int contAgenda;
    char clear;
    int opc;
    char opc_elimina;
    int pos;
    int retorno;
    char buffer[1000];
    if (argc != 2){
        printf("Archivo no indicado\n");
        return 1;
    }
    leer_archivo(argv[1], agenda, &contAgenda);
        do
    {
        printf("\n>> AGENDA ELECTRONICA <<\n\n");
        printf("[1] Alta de usuario \n");
        printf("[2] Modifica usuario \n");
        printf("[3] Busca usuario \n");
        printf("[4] Muestra todos \n");
        printf("[5] Elimina usuario \n");
        printf("[6] Guardar archivo\n");
        // printf("[7] Mostrar ordenados\n");
        printf("[7] Salir del programa \n");
        printf("Ingresa opcion: ");

        scanf("%i", &opc);
        do
        {
            clear = getchar();
        } while (clear != '\n');
        printf("\n");

        switch (opc)
        {
        case 1:

            if (contAgenda < T_AGENDA)
            {
                retorno = agregar_usuario(agenda, contAgenda);
                if (retorno == -1)
                {
                    printf("El NDI ya existe\n");
                }
                else
                {
                    contAgenda = retorno;
                    printf("Usuario %i, agregado\n", contAgenda);
                    if(contAgenda>1){
                        ordenar_alta(agenda,contAgenda);
                    }
                }
            }
            else
            {
                printf("La agenda tiene su maximo registro de usuarios");
            }

            break;

        case 2:
            printf("+ + Modifica usuario + +\n");

            pos = buscar_usuario(agenda, contAgenda);
            if (pos >= 0)
            {
                modificar_usuario(agenda, pos);
            }
            else
            {
                printf("No se encontro registro en la busqueda\n");
            }

            break;

        case 3:
            printf("+ + Busca usuario + +\n");

            pos = buscar_usuario(agenda, contAgenda);
            if (pos >= 0)
            {
                mostrar_usuario(agenda, pos);
            }
            else
            {
                printf("No se encontro registro en la busqueda\n");
            }

            break;

        case 4:
            if (contAgenda > 0)
            {
                mostrar_todos(agenda, contAgenda);
            }
            else
            {
                printf("No hay usuarios registrados\n");
            }
            break;

        case 5:
            printf("+ + Elimina usuario + +\n");
            pos = buscar_usuario(agenda, contAgenda);

            if (pos >= 0)
            {
                printf("Posicion a eliminar: %i - Total de usuarios: %i\n", pos, contAgenda);
                mostrar_usuario(agenda, pos);

                printf("Presiona [y] para confirmar,\npresiona cualquier otra tecla para cancelar: ");
                scanf("%c", &opc_elimina);
                do
                {
                    clear = getchar();
                } while (clear != '\n');

                opc_elimina = toupper(opc_elimina);
                if (opc_elimina == 'Y')
                {
                    contAgenda = eliminar_usuario(agenda, contAgenda, pos);
                    printf("Usuario eliminado...\n");
                }
                else
                {
                    printf("Usuario no eliminado\n");
                }
            }
            else
            {
                printf("No se encontro registro para eliminar\n");
            }
           
            break;

        case 6:
            printf("++Guardar Cambios++\n");
            guardar_cambios(argv[1],agenda, contAgenda);
            break;
        case 7:
            ordenar_id(agenda, contAgenda);
        break;
        case 8:
            printf("Se ejecuta salir del programa...");
            break;

        default:
            printf("Eleccion fuera de rango");
        } 
    } while (opc != 8);

    return 0;
}