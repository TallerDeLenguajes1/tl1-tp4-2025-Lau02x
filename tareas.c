#include <stdio.h>
#include <stdlib.h>

/*1) Desarrolle una interfaz de carga de tareas para solicitar tareas pendientes, en la cual se
solicite descripción y duración de la misma (el id debe ser generado automáticamente por
el sistema, de manera autoincremental comenzando desde el número 1000). Al cabo de
cada tarea consulte al usuario si desea ingresar una nueva tarea o finalizar la carga.
2) Implemente una interfaz para elegir qué tareas de la lista de pendientes deben ser
transferidas a la lista de tareas realizadas.
3) Implemente una funcionalidad que permita listar todas las tareas pendientes y realizadas.
4) Implemente una funcionalidad que permita consultar tareas por id o palabra clave y
mostrarlas por pantalla, indicando si corresponde a una tarea pendiente o realizada.*/
typedef struct
    {
    int TareaID;//Numérico autoincrementa l comenzando en 1000
    char *Descripcion; //
    int Duracion; // entre 10 – 100
    } Tarea;
typedef struct
{
    Tarea T;
    struct Nodo *Siguiente;
} Nodo;

Nodo * crearListaVacia();
Nodo * CrearNodo(int id, char *descripcion, int duracion);
int main ()
{
    Nodo *Start=crearListaVacia();
    








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
Nuevo->T.Descripcion=*descripcion;
Nuevo->Siguiente = NULL;
return Nuevo;
}
