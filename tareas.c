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
Nodo * buscarTarea(Nodo * StartRealizadas,Nodo * StartPendientes, int idBuscado, char * PalabraClave);
Nodo * buscarTareaPorId(Nodo * StartRealizadas,Nodo * StartPendientes, int idBuscado);
Nodo * buscarTareaPorPalabraClave(Nodo * StartRealizadas,Nodo * StartPendientes, char * PalabraClave);
void EliminarNodo(Nodo * nodo);
void ListarTareas(Nodo * TareasRealizadas, Nodo * TareasPendientes);
void InsertarNodo(Nodo **Start , Nodo * NodoAInsertar);
Nodo * QuitarNodo(Nodo ** Start, int id);
int main ()
{
    char *Buff;
    char *descripcion;
    int duracion;
    int idBuscar;
    int id=1000;
    int eleccion;
    Nodo * Eliminado;
    Nodo * NodoEncontrado;
    Nodo *TareasRealizadas=crearListaVacia();
    Nodo *TareasPendientes=crearListaVacia();
    Buff = (char *) malloc (sizeof(char)*150);
    char * palabraClave;
    do
    {
        printf("\n Cargar tareas a realizar: \n");
        printf("Descripcion de la tarea: \n");
        getchar();
        gets(Buff);
        descripcion = (char *) malloc ( sizeof(char)*(strlen(Buff)+1) );
        strcpy(descripcion,Buff);
        printf("Duracion de la tarea(entre 10 y 100): \n");
        scanf("%d",&duracion);
        Nodo *nuevoNodo = CrearNodo(id, descripcion, duracion);
        InsertarNodo(&TareasPendientes,nuevoNodo);

        printf(" \n Desea ingresar otra tarea?(1) o finalizar(0): ");
        scanf("%d",&eleccion);
        id++;
    }
    while(eleccion != 0);
    eleccion=1;
    do{


        ListarTareas(TareasRealizadas,TareasPendientes);
        printf("Elegir cual tarea pendiente se realizo, asi se pase a la lista de tareas Realizadas (0)por id o (1)para palabra clave:\n");
        scanf("%d",&eleccion);
        if(eleccion)
        {
            printf("Escribir Palabra clave: \n");
            gets(palabraClave);
            NodoEncontrado=buscarTareaPorPalabraClave(TareasRealizadas,TareasPendientes,0,palabraClave);
        }
        else
        {
            printf("Escribir id a buscar: \n");
            scanf("%d",&idBuscar);
            NodoEncontrado=buscarTareaPorId(TareasRealizadas,TareasPendientes,idBuscar,NULL);
        }
        if(NodoEncontrado)
        {
            InsertarNodo(&TareasRealizadas,NodoEncontrado);
            Eliminado=QuitarNodo(&TareasPendientes,idBuscar);
            EliminarNodo(Eliminado);
        }
        else
        {
            printf("No existe la tarea buscada");
        }
    
        printf(" \n Desea marcar otra tarea como realizada?(1) o finalizar(0): ");
        scanf("%d",&eleccion);
    }
    while (eleccion != 0);
    
        
    
    







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
Nodo * buscarTareaPorId(Nodo * StartRealizadas,Nodo * StartPendientes, int idBuscado)
{
Nodo *Aux = StartRealizadas;
while(Aux && Aux->T.TareaID != idBuscado)
{
Aux = Aux -> Siguiente;
}
if(Aux->T.TareaID == idBuscado)
{
    printf("La tarea encontrada en Realizadas: \n Id: %d \n Descripcion: %s\n Duracion:%d ",idBuscado,Aux->T.Descripcion,Aux->T.Duracion);
    return Aux;
}
Aux=StartPendientes;
while(Aux && Aux->T.TareaID !=idBuscado)
{
Aux=Aux->Siguiente;
}
if(Aux->T.TareaID == idBuscado)
{
    printf("La tarea encontrada en Pendientes : \n Id: %d \n Descripcion: %s\n Duracion:%d ",idBuscado,Aux->T.Descripcion,Aux->T.Duracion);
    return Aux; 

}
printf("no se encontro tarea");
return NULL;
}
Nodo * buscarTareaPorPalabraClave(Nodo * StartRealizadas,Nodo * StartPendientes, char * PalabraClave)
{
    Nodo *Aux = StartRealizadas;
    while(Aux && !strstr(Aux->T.Descripcion,PalabraClave))
    {
    Aux = Aux -> Siguiente;
    }
    if(strstr(Aux->T.Descripcion,PalabraClave))
    {
        printf("La tarea encontrada en Realizadas : \n Id: %d \n Descripcion: %s\n Duracion:%d ",Aux->T.TareaID,Aux->T.Descripcion,Aux->T.Duracion);
        return Aux;
    }
    Aux=StartPendientes;
    while(Aux && !strstr(Aux->T.Descripcion,PalabraClave))
    {
        Aux=Aux->Siguiente;
    }
    if(strstr(Aux->T.Descripcion,PalabraClave))
    {
        
        printf("La tarea encontrada en Pendientes : \n Id: %d \n Descripcion: %s\n Duracion:%d ",Aux->T.TareaID,Aux->T.Descripcion,Aux->T.Duracion);
        return Aux;
    }
    printf("La tarea no fue encontrada");
    return NULL;
    
}
void ListarTareas(Nodo * TareasRealizadas, Nodo * TareasPendientes)
{
    Nodo * Aux;
    Aux=TareasRealizadas;
    printf("\n Estas son las tareas Realizadas: \n");
    while (Aux)
    {
        printf("Tarea %d : %s \n Duracion: %d \n ",Aux->T.TareaID,Aux->T.Descripcion,Aux->T.Duracion);
        Aux=Aux->Siguiente;
    }
    Aux=TareasPendientes;
    printf("\n Estas son las tareas Pendientes: \n");
    while (Aux)
    {
        printf("Tarea %d : %s \n Duracion: %d \n ",Aux->T.TareaID,Aux->T.Descripcion,Aux->T.Duracion);
        Aux=Aux->Siguiente;
    }

    
}