#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*1) Desarrolle una interfaz de carga de tareas para solicitar tareas pendientes, en la cual se
solicite descripción y duración de la misma (el id debe ser generado automáticamente por
el sistema, de manera autoincremental comenzando desde el número 1000). Al cabo de
cada tarea consulte al usuario si desea ingresar una nueva tarea o finalizar la carga.
2) Implemente una interfaz para elegir qué tareas de la lista de pendientes deben ser
transferidas a la lista de tareas realizadas.
3) Implemente una funcionalidad que permita listar todas las tareas pendientes y realizadas.
4) Implemente una funcionalidad que permita consultar tareas por id o palabra clave y
mostrarlas por pantalla, indicando si corresponde a una tarea pendiente o realizada.*/
typedef struct Tarea
    {
    int TareaID;//Numérico autoincrementa l comenzando en 1000
    char *Descripcion; //
    int Duracion; // entre 10 – 100
    } Tarea;
typedef struct Nodo
{
    Tarea T;
    struct Nodo *Siguiente;
} Nodo;

Nodo * crearListaVacia();
Nodo * CrearNodo(int id, char *descripcion, int duracion);
Nodo * buscarNodo(Nodo * Start, int idBuscado);
void EliminarNodo(Nodo * nodo);
void ListarTareas(Nodo * TareasRealizadas, Nodo * TareasPendientes);
int main ()
{
    char *Buff;
    char *descripcion;
    int duracion;
    int id=1000;
    int eleccion;
    Nodo * TareasRealizadas;
    TareasRealizadas->Siguiente=NULL;
    Nodo * TareasPendientes;
    TareasPendientes->Siguiente=NULL;
    Buff = (char *) malloc (sizeof(char)*150);
    Nodo *TareasRealizadas=crearListaVacia();
    Nodo *TareasPendientes=crearListaVacia();
    do
    {
        printf("\n Cargar tareas a realizar: \n");
        printf("Descripcion de la tarea: \n");
        gets(Buff);
        descripcion = (char *) malloc ( sizeof(char)*(strlen(Buff)+1) );
        strcpy(descripcion,Buff);
        printf("Duracion de la tarea: \n");
        scanf("%d",&duracion);
        Nodo *nuevoNodo = CrearNodo(id, descripcion, duracion);
        

        printf(" \n Desea ingresar otra tarea?(1) o finalizar(0): ");
        scanf("%d",&eleccion);
        id++;
    }
    while(eleccion != 0);
    eleccion=1;
    do
    {
        printf("\n Tareas que se realizaron: \n");
        printf("Descripcion de la tarea: \n");
        gets(Buff);
        descripcion = (char *) malloc ( sizeof(char)*(strlen(Buff)+1) );
        strcpy(descripcion,Buff);
        printf("Duracion de la tarea: \n");
        scanf("%d",&duracion);
        Nodo *nuevoNodo = CrearNodo(id, descripcion, duracion);
        

        printf(" \n Desea ingresar otra tarea?(1) o finalizar(0): ");
        scanf("%d",&eleccion);
        id++;
    }
    while(eleccion != 0);
    
    







free(Buff);
return 0;
}

Nodo * crearListaVacia(){
        return NULL;
    }

Nodo * CrearNodo(int id, char *descripcion, int duracion)
{
Nodo *Nuevo = (Nodo *) malloc (sizeof(Nodo));
Nuevo->T.TareaID = id;
Nuevo->T.Duracion=duracion;
Nuevo->T.Descripcion = descripcion;
Nuevo->Siguiente = NULL;
return Nuevo;
}
void InsertarNodo(Nodo **Start , Nodo * NodoAInsertar)
{
NodoAInsertar->Siguiente = *Start;
*Start = NodoAInsertar;
}
Nodo * buscarNodo(Nodo * Start, int idBuscado)
{
Nodo *Aux = Start;
while(Aux && Aux->T.TareaID != idBuscado)
{
Aux = Aux -> Siguiente;
}
return Aux;
}

void EliminarNodo(Nodo * nodo)
{
if (!nodo) free(nodo);
}
/*void QuitarNodo(Nodo * Start, int dato)
{ Nodo ** aux = Start;
while (*aux != NULL && (*aux)->dato != dato) {
aux = &(*aux)->siguiente;
}
if (*aux) {
Tnodo *temp = *aux;
*aux = (*aux)->siguiente;
temp->siguiente =NULL;
return temp;
}
return NULL;
}*/
void ListarTareas(Nodo * TareasRealizadas, Nodo * TareasPendientes)
{
    
    printf("\n Estas son las tareas Realizadas: \n");
    printf("Tarea %d : %s, Duracion: %d  ",TareasRealizadas->T.TareaID,TareasRealizadas->T.Descripcion,TareasRealizadas->T.Duracion);
}