#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "./dynamic-array.h"

static inline bool isDynamicArrayFull(DynamicArray *);
static void freeDynamicArrayList(void **, unsigned int);
static void freeDynamicArrayListElement(void *element);
static void dynamicArrayResize(DynamicArray *);

DynamicArray *DefaultDynamicArrayInit(void)
{
    return DynamicArrayInit(4);
}

DynamicArray *DynamicArrayInit(unsigned int initial_capacity)
{
    DynamicArray *dynamicArray = malloc(sizeof(DynamicArray));
    if (dynamicArray == NULL)
    {
        printf("[ERROR]: could not allocate memory for DynamicArray\n");
        return NULL;
    }
    dynamicArray->size = 0;
    dynamicArray->capacity = initial_capacity;
    dynamicArray->list = malloc(sizeof(void *) * dynamicArray->capacity);
    return dynamicArray;
}

void DynamicArrayAdd(DynamicArray *dynamicArray, void *element)
{
    if (dynamicArray == NULL || element == NULL)
    {
        return;
    }
    if (isDynamicArrayFull(dynamicArray))
    {
        dynamicArrayResize(dynamicArray);
    }

    dynamicArray->list[dynamicArray->size] = element;
    dynamicArray->size++;
}

static void dynamicArrayResize(DynamicArray *dynamicArray)
{
    if (dynamicArray == NULL)
    {
        return;
    }
    const unsigned int size_multiple = 2;
    // double the capacity
    void **newList = malloc(sizeof(void *) * dynamicArray->capacity * size_multiple);
    if (newList == NULL)
    {
        printf("not enough memory for newList\n");
        return; // FIXME
    }

    for (unsigned int i = 0; i < dynamicArray->size; i++)
    {
        newList[i] = dynamicArray->list[i];
    }
    freeDynamicArrayList(dynamicArray->list, dynamicArray->size);
    dynamicArray->list = newList;
    dynamicArray->capacity *= size_multiple;
}

static inline bool isDynamicArrayFull(DynamicArray *dynamicArray)
{
    return dynamicArray->capacity == dynamicArray->size;
}

static void freeDynamicArrayListElement(void *element)
{
    if (element != NULL)
    {
        free(element);
    }
}

static void freeDynamicArrayList(void **list, unsigned int size)
{
    for (unsigned int i = 0; i < size; i++)
    {
        freeDynamicArrayListElement(list[i]);
    }
    free(list);
}

void FreeDynamicArray(DynamicArray *dynamicArray)
{
    if (dynamicArray == NULL)
    {
        return;
    }
    if (dynamicArray->list != NULL)
    {
        freeDynamicArrayList(dynamicArray->list, dynamicArray->size);
    }
    free(dynamicArray);
}

void PrintDynamicArray(DynamicArray *dynamicArray)
{
    if (dynamicArray == NULL)
    {
        return;
    }
    for (unsigned int i = 0; i < dynamicArray->size; i++)
    {
        printf("%d\n", i);
    }
}