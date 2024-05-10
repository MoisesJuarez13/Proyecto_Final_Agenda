//Moises de Jesus Juarez Alvarez
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include "header.h"

int valida_ndi(char *ndi_aux, Agenda *agenda, int contAgenda)
{
    int band = 0;
    int i;
    for (i = 0; ndi_aux[i] != '\0'; i++)
    {
        if (isalpha(ndi_aux[i]))
        {
            return 0;
        }
    }

    for (i = 0; i < contAgenda; i++)
    {
        if (strcmp(agenda[i].ndi, ndi_aux) == 0)
            band = 1;
    }

    if (band)
        return 0;
    else
        return 1;
}

int agregar_usuario(Agenda *agenda, int contAgenda)
{
    char ndi_tmp[T_NDI];

    printf("+ + Agregar Usuario + +\n");

    printf("NDI: ");
    fgets(ndi_tmp, sizeof(ndi_tmp), stdin);
    ndi_tmp[strcspn(ndi_tmp, "\n")] = '\0';

    if (!valida_ndi(ndi_tmp, agenda, contAgenda))
    {
        return -1;
    }

    strncpy(agenda[contAgenda].ndi, ndi_tmp, sizeof(agenda[contAgenda].ndi));

    printf("Nombre completo: ");
    fgets(agenda[contAgenda].nombre, sizeof(agenda[contAgenda].nombre), stdin);
    agenda[contAgenda].nombre[strcspn(agenda[contAgenda].nombre, "\n")] = '\0';

    printf("Correo: ");
    fgets(agenda[contAgenda].correo, sizeof(agenda[contAgenda].correo), stdin);
    agenda[contAgenda].correo[strcspn(agenda[contAgenda].correo, "\n")] = '\0';

    printf("Telefono: ");
    fgets(agenda[contAgenda].telefono, sizeof(agenda[contAgenda].telefono), stdin);
    agenda[contAgenda].telefono[strcspn(agenda[contAgenda].telefono, "\n")] = '\0';

    return contAgenda + 1;
}

int buscar_usuario(Agenda *agenda, int contAgenda)
{
    char ndi_aux[T_NDI];
    int i = 0;
    int band = 0;
    clock_t inicio,fin;
    double tiempo;
    printf("Ingresa el NDI a buscar: ");
    fgets(ndi_aux, sizeof(ndi_aux), stdin);
    ndi_aux[strcspn(ndi_aux, "\n")] = '\0';

    inicio=clock();
    for (i = 0; i < contAgenda && band == 0; i++)
    {
        if (strcmp(agenda[i].ndi, ndi_aux) == 0)
        {
            band = 1;
        }
    }
    fin=clock();
    printf("Elementos iterados: %i\n", i);
    tiempo=((double)(fin - inicio)) / CLOCKS_PER_SEC;
    if (!band)
    {
        return -1;
    }

    return i - 1;
}

int modificar_usuario(Agenda *agenda, int posicion)
{
    printf("NDI: %s\n", agenda[posicion].ndi);
    printf("Nombre completo: ");
    fgets(agenda[posicion].nombre, sizeof(agenda[posicion].nombre), stdin);
    agenda[posicion].nombre[strcspn(agenda[posicion].nombre, "\n")] = '\0';

    printf("Correo: ");
    fgets(agenda[posicion].correo, sizeof(agenda[posicion].correo), stdin);
    agenda[posicion].correo[strcspn(agenda[posicion].correo, "\n")] = '\0';

    printf("Telefono: ");
    fgets(agenda[posicion].telefono, sizeof(agenda[posicion].telefono), stdin);
    agenda[posicion].telefono[strcspn(agenda[posicion].telefono, "\n")] = '\0';

    return (0);
}

void mostrar_usuario(Agenda *agenda, int posicion)
{
    printf("NDI: %s\n", agenda[posicion].ndi);
    printf("Nombre completo: %s\n", agenda[posicion].nombre);
    printf("Correo: %s\n", agenda[posicion].correo);
    printf("Telefono: %s\n", agenda[posicion].telefono);
}

int mostrar_todos(Agenda *agenda, int contAgenda)
{
    // int i = 0;

    printf("+ + Mostrar Usuarios + + \n");

    for (int i = 1; i < contAgenda; i++)
    {
        mostrar_usuario(agenda, i);
        printf("\n");
    }

    // printf("Elementos mostrados: %i\n", i);

    return (0);
}

int eliminar_usuario(Agenda *agenda, int contAgenda, int pos)
{
    if (pos == contAgenda - 1)
    {
        return contAgenda - 1;
    }

    while (pos <= contAgenda - 1)
    {
        strcpy(agenda[pos].ndi, agenda[pos + 1].ndi);
        strcpy(agenda[pos].nombre, agenda[pos + 1].nombre);
        strcpy(agenda[pos].correo, agenda[pos + 1].correo);
        strcpy(agenda[pos].telefono, agenda[pos + 1].telefono);
        pos++;
    }

    return contAgenda - 1;
}

int eliminar_usuario_2(Agenda *agenda, int contAgenda, int pos)
{
    if (pos == contAgenda - 1)
    {
        return contAgenda - 1;
    }

    strcpy(agenda[pos].ndi, agenda[contAgenda - 1].ndi);
    strcpy(agenda[pos].nombre, agenda[contAgenda - 1].nombre);
    strcpy(agenda[pos].correo, agenda[contAgenda - 1].correo);
    strcpy(agenda[pos].telefono, agenda[contAgenda - 1].telefono);
    contAgenda--; // decrementa la posicion en el arreglo de usuarios

    return contAgenda - 1;
}
void guardar_cambios(char *nombre_archivo, Agenda *agenda, int contAgenda)
{
    FILE *archivo_salida;
    archivo_salida = fopen(nombre_archivo, "r+");
    if (archivo_salida == NULL)
    {
        printf("No se pudo abrir el archivo para escribir\n");
        return;
    }
    fprintf(archivo_salida, "ID,Nombre Completo,Correo,Telefono\n");
    for (int i = 0; i < contAgenda; i++)
    {
        fprintf(archivo_salida, "%s,%s,%s,%s\n", agenda[i].ndi, agenda[i].nombre, agenda[i].correo, agenda[i].telefono);
    }
    fclose(archivo_salida);
    printf("Cambios guardados en el archivo: %s\n", nombre_archivo);
}

void leer_archivo(const char *nombre_archivo, Agenda *agenda, int *contAgenda)
{
    char buffer[1000];
    FILE *archivo = fopen(nombre_archivo, "r");
    if (archivo == NULL)
    {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    if (fgets(buffer, 1000, archivo) == NULL)
    {
        printf("El archivo está vacío.\n");
        fclose(archivo);
        return;
    }
    rewind(archivo);

    if (strstr(buffer, "ID") && strstr(buffer, "Nombre") && strstr(buffer, "Correo") && strstr(buffer, "Telefono"))
    {
        fgets(buffer, 1000, archivo);
        while (fgets(buffer, 1000, archivo))
        {
            if (*contAgenda < T_AGENDA)
            {
                Agenda user;

                strtok(buffer, "\n");
                char *arr[4];

                arr[0] = strtok(buffer, ",");
                arr[1] = strtok(NULL, ",");
                arr[2] = strtok(NULL, ",");
                arr[3] = strtok(NULL, ",");

                // printf("NDI:%s\n", arr[0]);
                // printf("Nombre:%s\n", arr[1]);
                // printf("Correo:%s\n", arr[2]);
                // printf("Telefono:%s\n", arr[3]);

                if (valida_ndi(arr[0], agenda, *contAgenda))
                {
                    strncpy(agenda[*contAgenda].ndi, arr[0], sizeof(agenda[*contAgenda].ndi));
                    strncpy(agenda[*contAgenda].nombre, arr[1], sizeof(agenda[*contAgenda].nombre));
                    strncpy(agenda[*contAgenda].correo, arr[2], sizeof(agenda[*contAgenda].correo));
                    strncpy(agenda[*contAgenda].telefono, arr[3], sizeof(agenda[*contAgenda].telefono));

                    (*contAgenda)++;

                    printf("NDI:%s\n", arr[0]);
                    printf("Nombre:%s\n", arr[1]);
                    printf("Correo:%s\n", arr[2]);
                    printf("Telefono:%s\n", arr[3]);
                }
            }
        }
        fclose(archivo);
    }
    else
    {
        printf("El archivo no tiene la forma de una agenda.\n");
        fclose(archivo);
        return;
    }
}
void ordenar_id(Agenda *agenda, int contAgenda)
{
    clock_t inicio,fin;
    double tiempo;
    inicio=clock();
    for (int i = 0; i < contAgenda; i++)
    {
        for (int j = 0; j < contAgenda - 1; j++)
        {
            if (atoi(agenda[j].ndi) > atoi(agenda[j + 1].ndi))
            {
                // printf("agenda 1 %i",atoi(agenda[j].ndi));
                // printf("agenda 2 %i",atoi(agenda[j+1].ndi));
                // printf("\n");
                Agenda temp = agenda[j];
                agenda[j] = agenda[j + 1];
                agenda[j + 1] = temp;
            }
        }
    }
    fin=clock();
    mostrar_todos(agenda, contAgenda);
    tiempo=((double)(fin - inicio)) / CLOCKS_PER_SEC;
    printf("Tiempo de ordenamiento:%i\n");
    // printf("ID ordenados de menor a mayor:\n");
    // for (int i=0; i < contAgenda; i++) {
    //     printf("%s ", agenda[i].ndi);
    //     printf("%s\n", agenda[i].nombre);
    //     printf("%s\n", agenda[i].correo);
    //     printf("%s\n", agenda[i].telefono);
    // }
}