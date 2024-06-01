#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "./dynamic-array.h"

static inline bool isDynamicArrayFull(DynamicArray *);
static inline bool isDynamicArrayEmpty(DynamicArray *);
static void freeDynamicArrayList(DynamicArrayElement **, unsigned int, bool);
static void freeDynamicArrayListElement(DynamicArrayElement *element);
static void dynamicArrayResize(DynamicArray *);

static void printIntArr(int *, unsigned int);

DynamicArray *DefaultDynamicArrayInit(void)
{
    return DynamicArrayInit(1);
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
    dynamicArray->list = malloc(sizeof(DynamicArrayElement *) * dynamicArray->capacity);
    return dynamicArray;
}

void DynamicArrayAdd(DynamicArray *dynamicArray, DynamicArrayElement *element)
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
    printf("[INFO]: resizing array\n");
    const unsigned int size_multiple = 2;
    // double the capacity
    DynamicArrayElement **newList = malloc(sizeof(DynamicArrayElement *) * dynamicArray->capacity * size_multiple);
    if (newList == NULL)
    {
        printf("not enough memory for newList\n");
        return; // FIXME
    }

    for (unsigned int i = 0; i < dynamicArray->size; i++)
    {
        newList[i] = dynamicArray->list[i];
    }
    freeDynamicArrayList(dynamicArray->list, dynamicArray->size, false);
    dynamicArray->list = newList;
    dynamicArray->capacity *= size_multiple;
}

static inline bool isDynamicArrayFull(DynamicArray *dynamicArray)
{
    return dynamicArray->capacity == dynamicArray->size;
}

static inline bool isDynamicArrayEmpty(DynamicArray *dynamicArray)
{
    return dynamicArray->size == 0;
}

static void freeDynamicArrayListElement(DynamicArrayElement *element)
{
    if (element == NULL)
    {
        return;
    }
    if (element->value != NULL)
    {
        free(element->value);
    }
    free(element);
}

static void freeDynamicArrayList(DynamicArrayElement **list, unsigned int size, bool deep)
{
    if (list == NULL)
    {
        return;
    }
    if (deep)
    {
        for (unsigned int i = 0; i < size; i++)
        {
            freeDynamicArrayListElement(list[i]);
        }
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
        freeDynamicArrayList(dynamicArray->list, dynamicArray->size, true);
    }
    free(dynamicArray);
}

static void printIntArr(int *arr, unsigned int len)
{
    printf("[");
    for (unsigned int i = 0; i < len; i++)
    {
        printf("%d", arr[i]);
        if (i != len - 1)
        {
            printf(",");
        }
    }
    printf("]");
}

void PrintDynamicArray(DynamicArray *dynamicArray)
{
    if (dynamicArray == NULL)
    {
        return;
    }
    printf("[");
    for (unsigned int i = 0; i < dynamicArray->size; i++)
    {
        switch (dynamicArray->list[i]->type)
        {
        case CHAR_ARR_t:
            printf("\"%s\"", (char *)dynamicArray->list[i]->value);
            break;
        case INT_ARR_t:
            printIntArr((int *)dynamicArray->list[i]->value, dynamicArray->list[i]->len);
            break;
        case INT_t:
            printf("%d", *(int *)dynamicArray->list[i]->value);
            break;
        default:
            break;
        }
        if (i != dynamicArray->size - 1)
        {
            printf(", ");
        }
    }
    printf("]\n");
}

void DynamicArrayRemove(DynamicArray *dynamicArray, unsigned int index)
{
    if (dynamicArray == NULL || index >= dynamicArray->size || isDynamicArrayEmpty(dynamicArray))
    {
        return;
    }
    freeDynamicArrayListElement(dynamicArray->list[index]);

    for (unsigned int i = index + 1; i < dynamicArray->size; i++)
    {
        dynamicArray->list[i - 1] = dynamicArray->list[i];
    }

    dynamicArray->size--;
}

void DynamicArrayRemoveFirstElement(DynamicArray *dynamicArray)
{
    if (dynamicArray == NULL)
    {
        return;
    }
    DynamicArrayRemove(dynamicArray, 0);
}

void DynamicArrayRemoveLastElement(DynamicArray *dynamicArray)
{
    if (dynamicArray == NULL)
    {
        return;
    }
    DynamicArrayRemove(dynamicArray, dynamicArray->size - 1);
}

DynamicArrayElement *DynamicArrayElementInit(enum DynamicArrayElementType type, void *value, unsigned int len)
{
    DynamicArrayElement *dynamicArrayElement = malloc(sizeof(DynamicArrayElement));
    if (dynamicArrayElement == NULL)
    {
        return NULL;
    }
    dynamicArrayElement->type = type;
    dynamicArrayElement->value = value;
    dynamicArrayElement->len = len;
    return dynamicArrayElement;
}
