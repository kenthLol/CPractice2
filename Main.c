#include <stdio.h> //Standard Input/Output
#include <inttypes.h> // Aquí se encuentran los intxx_t, uintxx_t
#include <stdlib.h>

struct _List
{
    int32_t *Data; // Data es un array
    size_t Capacity; // Cantidad de elemento de Data
    size_t Size; // Cuántos bloques de memoria asignados o ocupados
};

typedef struct _List List, *ListPointer;

struct _ParesEImpares
{
    ListPointer Pares;
    ListPointer Impares;
};

typedef struct _ParesEImpares ParesImpares;

ListPointer ListNew();
void ListAdd(ListPointer, int32_t);
size_t ListSize(ListPointer);
void ListDestroy(ListPointer);
void Elements(ListPointer);
int32_t* ListGet(ListPointer, int32_t);

ParesImpares BuscarParesImpares(ListPointer);

int32_t main(const int32_t argc, char const * agrv[])
{
    int32_t value = 0;

    ListPointer list = ListNew();

    ListAdd(list, 5);
    ListAdd(list, 3);
    ListAdd(list, 2);
    ListAdd(list, 8);
    ListAdd(list, 7);
    ListAdd(list, 20);
    ListAdd(list, 21);

    ParesImpares ParImparList = BuscarParesImpares(list);

    printf(" Lista de elementos \n");
    Elements(list);

    printf(" Lista de elementos Pares\n");
    Elements(ParImparList.Pares);

    printf(" Lista de elementos Impares\n");
    Elements(ParImparList.Impares);

    ListDestroy(ParImparList.Pares);
    ListDestroy(ParImparList.Impares);
    ListDestroy(list);

    return 0;
}

ListPointer ListNew()
{
    ListPointer list = NULL;
    list = malloc(sizeof(List));

    //Incializando en Cero las variables
    list->Capacity = 4;
    list->Data = NULL;
    list->Size = 0;

    //Dando capacidad por defecto
    // (int32_t*)malloc(list->Capacity * sizeof(int32_t)) Me retorna el array de enteros
    //    Array                           Tamaño de un int

    //(int32_t*)malloc(list->Capacity * sizeof(int32_t*)) -> Está retornando un array de punteros de enteros

    list->Data = (int32_t*)malloc(list->Capacity * sizeof(int32_t));

    return list;
}

void ListAdd(ListPointer list_pointer, int32_t value)
{
    printf(" Capacidad: %lu", list_pointer->Capacity);
    printf(" Size: %lu", list_pointer->Size);
    // Validación
    if (list_pointer->Capacity == list_pointer->Size)
    {
        printf("\n Full capacity\n");
        int32_t new_capacity = (list_pointer->Capacity) * 2;
        int32_t *aux = NULL;

        aux = (int32_t*)malloc(list_pointer->Capacity * sizeof(int32_t));

        for (size_t i = 0; i < list_pointer->Size; ++i)
        {
            aux[i] = list_pointer->Data[i];
        }

        free(list_pointer->Data);

        list_pointer->Data = aux;

        list_pointer->Capacity = new_capacity;
    }

    list_pointer->Data[list_pointer->Size] = value;
    list_pointer->Size += 1;

    printf(" Size: %lu\n\n", list_pointer->Size);
}

size_t ListSize(ListPointer list_pointer)
{
    return list_pointer->Size;
}

void ListDestroy(ListPointer list_pointer)
{
    printf("\n Destroying object\n");
    free(list_pointer->Data);
    free(list_pointer);
}

void Elements(ListPointer list_pointer)
{
    printf("\t Elements \n");
    for (size_t index = 0; index < ListSize(list_pointer); ++index)
    {
        printf("[%lu]: %d\n", index, *ListGet(list_pointer, index));
    }
    printf("\n");
}

int32_t* ListGet(ListPointer list_pointer, int32_t index)
{       // >= 0 < Size
    if ((index >= 0) && (index < list_pointer->Size))
    {
        // También se puede &(list_pointer->Data[index])
        return (list_pointer->Data + index);
    }

    return NULL;
}

ParesImpares BuscarParesImpares(ListPointer list_pointer)
{
    ParesImpares list;
    list.Pares = ListNew();
    list.Impares = ListNew();

    for (size_t i = 0; i < list_pointer->Size; ++i)
    {
        if(list_pointer->Data[i] % 2 != 0)
        {
            printf(" Impares\n");
            ListAdd(list.Impares, *(list_pointer->Data + i));
        }
        else
        {
            printf(" Pares\n");
            ListAdd(list.Pares, *(list_pointer->Data + i));
        }
    }

    return list;
}