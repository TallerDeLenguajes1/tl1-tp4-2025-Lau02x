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
Nodo * buscarTareas(Nodo * TareasRealizadas,Nodo * TareasPendientes);
Nodo * buscarTareaPorId(Nodo * StartRealizadas,Nodo * StartPendientes, int idBuscado);
Nodo * buscarTareaPorPalabraClave(Nodo * StartRealizadas,Nodo * StartPendientes, char * PalabraClave);
void EliminarNodo(Nodo * nodo);
void ListarTareas(Nodo * TareasRealizadas, Nodo * TareasPendientes);
void InsertarNodo(Nodo **Start , Nodo * NodoAInsertar);
Nodo * QuitarNodo(Nodo ** Start, int id);
void cargarTareasARealizar(Nodo ** TareasPendientes,int *id);
void moverTareaPendienteARealizada(Nodo ** TareasPendientes,Nodo ** TareasRealizadas,int idMover);
void LiberarLista(Nodo *Start);
int main ()
{
    int id;
    id=1000;
    int idMover;
    int eleccion;
    Nodo *TareasRealizadas=crearListaVacia();
    Nodo *TareasPendientes=crearListaVacia();
    do
    {
        do
        {
            printf("Menu: Cargar Tareas a realizar (1)\nMover una tarea pendiente a tareas realizadas(2) \nListar todas las tareas pendientes y realizadas(3)\nBuscar tareas(4)\nFinalizar(5)\nEleccion:");
            scanf("%d",&eleccion);
        }
        while(eleccion!=1 && eleccion!=2 && eleccion!=3 && eleccion!=4 && eleccion !=5 && eleccion);
        switch (eleccion)
        {
        case 1:
                cargarTareasARealizar(&TareasPendientes,&id);
        break;
        case 2:
                ListarTareas(TareasRealizadas,TareasPendientes);
                printf("Elegir id de Tareas Pendientes para mover a Tareas Realizadas:");
                scanf("%d",&idMover);
                moverTareaPendienteARealizada(&TareasPendientes,&TareasRealizadas,idMover);
        break;
        case 3:
                ListarTareas(TareasRealizadas,TareasPendientes);
        break;
        case 4:
                buscarTareas(TareasRealizadas,TareasPendientes);
        break;
        case 5:
        break;
        default: 
                return 0;
        break;
        }

    }
    while(eleccion!=5);
    LiberarLista(TareasPendientes);
    LiberarLista(TareasRealizadas);
    return 0;
}
void LiberarLista(Nodo *Start)
{
    Nodo *Aux;
    while (Start != NULL)
    {
        Aux = Start;
        Start = Start->Siguiente;
        EliminarNodo(Aux); // Liberar cada nodo
    }
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
Nodo * buscarTareas(Nodo * TareasRealizadas,Nodo * TareasPendientes)
    {
    int eleccion;
    int id;
    char * palabraClave;
    palabraClave= (char *)malloc(sizeof(char)*150);
    Nodo * TareaEncontrada;
    do
    {
        printf("Buscar tarea por id(0) o por palabra clave(1)?\n ");
        scanf("%d",&eleccion);
       switch (eleccion)
       {
       case 0:
                printf("\nEscribir id:");
                scanf("%d",&id);
                TareaEncontrada=buscarTareaPorId(TareasRealizadas,TareasPendientes,id);
                return TareaEncontrada;
        break;
       case 1:
                printf("\nEscribir palabra clave: ");
                getchar();
                gets(palabraClave);
                TareaEncontrada=buscarTareaPorPalabraClave(TareasRealizadas,TareasPendientes,palabraClave);
                return TareaEncontrada;
        break;
       default:
                printf("Incorrecto, vuelva a elegir 1 o 0 \n");
        break;
       }
           
        

    } while (eleccion!=1 || eleccion!=0);
    return NULL;
    }
Nodo * buscarTareaPorId(Nodo * StartRealizadas,Nodo * StartPendientes, int idBuscado)
{
    Nodo *Aux = StartRealizadas;
    while(Aux && Aux->T.TareaID != idBuscado)
    {
        Aux = Aux -> Siguiente;
    }
    if(Aux != NULL)
    {
        printf("La tarea encontrada en Realizadas: \n Id: %d \n Descripcion: %s\n Duracion: %d \n", Aux->T.TareaID, Aux->T.Descripcion, Aux->T.Duracion);
        return Aux;
    }
    Aux = StartPendientes;
    while(Aux && Aux->T.TareaID != idBuscado)
    {
        Aux = Aux->Siguiente;
    }
    if(Aux != NULL)
    {
        printf("La tarea encontrada en Pendientes: \n Id: %d \n Descripcion: %s\n Duracion: %d \n", Aux->T.TareaID, Aux->T.Descripcion, Aux->T.Duracion);
        return Aux;
    }
    printf("No se encontro tarea\n");
    return NULL;
}

Nodo * buscarTareaPorPalabraClave(Nodo * StartRealizadas,Nodo * StartPendientes, char * PalabraClave)
{
    Nodo *Aux = StartRealizadas;
    while(Aux && !strstr(Aux->T.Descripcion,PalabraClave))
    {
    Aux = Aux -> Siguiente;
    }
    if(Aux && strstr(Aux->T.Descripcion,PalabraClave))
    {
        printf("La tarea encontrada en Realizadas : \n Id: %d \n Descripcion: %s\n Duracion:%d \n",Aux->T.TareaID,Aux->T.Descripcion,Aux->T.Duracion);
        return Aux;
    }
    Aux=StartPendientes;
    while(Aux && !strstr(Aux->T.Descripcion,PalabraClave))
    {
        Aux=Aux->Siguiente;
    }
    if(strstr(Aux->T.Descripcion,PalabraClave))
    {
        
        printf("La tarea encontrada en Pendientes : \n Id: %d \n Descripcion: %s\n Duracion:%d \n",Aux->T.TareaID,Aux->T.Descripcion,Aux->T.Duracion);
        return Aux;
    }
    printf("La tarea no fue encontrada");
    return NULL;
}

void ListarTareas(Nodo * TareasRealizadas, Nodo * TareasPendientes)
{
    Nodo * Aux;
    Aux=TareasRealizadas;
if(TareasRealizadas)
{
 printf("////////\n Estas son las tareas Realizadas: \n");
    while (Aux)
    {
        printf("Tarea %d : %s \n Duracion: %d \n ",Aux->T.TareaID,Aux->T.Descripcion,Aux->T.Duracion);
        Aux=Aux->Siguiente;
    }
printf("////////// \n");
}
else 
{
    printf("\n No hay tareas Realizadas \n");
    printf("////////// \n");
}
if(TareasPendientes)
{
    Aux=TareasPendientes;
    printf("//////////\n Estas son las tareas Pendientes: \n");
    while (Aux)
    {
        printf("Tarea %d : %s \n Duracion: %d \n ",Aux->T.TareaID,Aux->T.Descripcion,Aux->T.Duracion);
        Aux=Aux->Siguiente;
    }
    printf("////////// \n");
}
else 
{
    printf("\n No hay tareas Pendientes \n ///////// \n");
}

}

void cargarTareasARealizar(Nodo ** TareasPendientes,int *id)
{
    char *Buff;
    Buff = (char *) malloc (sizeof(char)*150);
    char *descripcion;
    int duracion;
    printf("\n Cargar tareas a realizar: \n");
    printf("Descripcion de la tarea: \n");
    getchar();
    gets(Buff);
    descripcion = (char *) malloc ( sizeof(char)*(strlen(Buff)+1) );
    strcpy(descripcion,Buff);
    do{
        printf("Duracion de la tarea(entre 10 y 100): \n");
        scanf("%d",&duracion);
    }
    while(duracion<10 || duracion>=100);
    Nodo *nuevoNodo = CrearNodo(*id, descripcion, duracion);
    InsertarNodo(TareasPendientes,nuevoNodo);
    (*id)++;
    if(Buff)
    {
        free(Buff);
    }
}

void moverTareaPendienteARealizada(Nodo ** TareasPendientes,Nodo ** TareasRealizadas,int idMover)
{
    Nodo * Eliminado=QuitarNodo(TareasPendientes,idMover);
    if(Eliminado){
        InsertarNodo(TareasRealizadas,Eliminado);
        printf("\n Tarea movida a Tareas Realizadas exitosamente \n");
    }
    else{
        printf("\n No existe la id de esa tarea, intentar de nuevo \n");
    }
}
Nodo * QuitarNodo(Nodo **Start, int id)
    {  
    Nodo *nodoAux = (*Start);
    Nodo *nodoAnt = NULL;

    while (nodoAux != NULL && nodoAux->T.TareaID != id)
    { 
        nodoAnt = nodoAux;
        nodoAux = nodoAux->Siguiente;
    }
    if (nodoAux != NULL)
    {
        if (nodoAux == (*Start))
        { 
            (*Start) = nodoAux->Siguiente;
        }
        else
        { 
            nodoAnt->Siguiente = nodoAux->Siguiente;
        }
        nodoAux->Siguiente = NULL;
    }
    return (nodoAux);
    }
void EliminarNodo(Nodo * nodo)
{
if (nodo)
{
    if(nodo->T.Descripcion)
    {
        free(nodo->T.Descripcion);
    }
    free(nodo);
}
}