//Moises de Jesus Juarez Alvarez
#define T_NDI 5
#define T_NAME 50
#define T_MAIL 50
#define T_PHONE 11
#define T_AGENDA 122

typedef struct
{
    char ndi[T_NDI];
    char nombre[T_NAME];
    char correo[T_MAIL];
    char telefono[T_PHONE];
} Agenda;

int valida_ndi(char *ndi_aux, Agenda *agenda, int contAgenda);
int agregar_usuario(Agenda *agenda, int contAgenda);
int buscar_usuario(Agenda *agenda, int contAgenda);
int modificar_usuario(Agenda *agenda, int posicion);
void mostrar_usuario(Agenda *agenda, int posicion);
int mostrar_todos(Agenda *agenda, int contAgenda);
int eliminar_usuario(Agenda *agenda, int contAgenda, int pos);
int eliminar_usuario_2(Agenda *agenda, int contAgenda, int pos);
void guardar_cambios(char*nombre_archivo,Agenda *agenda, int contAgenda);
void leer_archivo(const char *nombre_archivo, Agenda *agenda, int *contAgenda);
void ordenar_id(Agenda *agenda, int contAgenda);
