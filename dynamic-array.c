#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "./dynamic-array.h"

static inline bool isDynamicArrayFull(DynamicArray *);
static inline bool isDynamicArrayEmpty(DynamicArray *);
static void freeDynamicArrayList(DynamicArrayElement **, unsigned int, bool);
static void freeDynamicArrayListElement(DynamicArrayElement *element);
static void dynamicArrayResize(DynamicArray *);

static void printIntArr(int *, unsigned int, bool, int);
static void printDynamicArrayHelper(DynamicArray *, bool, int);
static inline void printSpaces(int);

DynamicArray *DefaultDynamicArrayInit(void)
{
    return DynamicArrayInit(DEFAULT_LIST_SIZE);
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

void DynamicArrayAddFirst(DynamicArray *dynamicArray, DynamicArrayElement *element)
{
    DynamicArrayAdd(dynamicArray, element, 0);
}

void DynamicArrayAddLast(DynamicArray *dynamicArray, DynamicArrayElement *element)
{
    DynamicArrayAdd(dynamicArray, element, dynamicArray->size - 1);
}

void DynamicArrayAdd(DynamicArray *dynamicArray, DynamicArrayElement *element, unsigned int index)
{
    if (dynamicArray == NULL || element == NULL)
    {
        return;
    }
    if (isDynamicArrayFull(dynamicArray))
    {
        dynamicArrayResize(dynamicArray);
    }
    for (unsigned int i = dynamicArray->size; i > index; i--)
    {
        dynamicArray->list[i] = dynamicArray->list[i - 1];
    }

    dynamicArray->list[index] = element;
    dynamicArray->size++;
}

static void dynamicArrayResize(DynamicArray *dynamicArray)
{
    if (dynamicArray == NULL)
    {
        return;
    }

    DynamicArrayElement **newList = malloc(sizeof(DynamicArrayElement *) * dynamicArray->capacity * RESIZE_MULTIPLE);
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
    dynamicArray->capacity *= RESIZE_MULTIPLE;
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
        if (element->type == DYN_ARR_t)
        {
            FreeDynamicArray(element->value);
        }
        else
        {
            free(element->value);
        }
        free(element);
    }
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

static inline void printSpaces(int depth)
{
    for (int i = 0; i < depth; i++)
    {
        printf(" ");
    }
}

static void printIntArr(int *arr, unsigned int len, bool pretty, int depth)
{
    printf("[");
    if (pretty)
    {
        printf("\n");
    }
    for (unsigned int i = 0; i < len; i++)
    {
        if (pretty)
        {
            printSpaces(depth);
        }
        printf("%d", arr[i]);
        if (i != len - 1)
        {

            printf(",");
        }
        if (pretty)
        {
            printf("\n");
        }
    }
    if (pretty)
    {
        printSpaces(depth);
    }
    printf("]");
}

static void printDynamicArrayHelper(DynamicArray *dynamicArray, bool pretty, int depth)
{
    for (unsigned int i = 0; i < dynamicArray->size; i++)
    {
        switch (dynamicArray->list[i]->type)
        {
        case CHAR_ARR_t:
            printf("\"%s\"", (char *)dynamicArray->list[i]->value);
            break;
        case INT_ARR_t:
            printIntArr((int *)dynamicArray->list[i]->value, dynamicArray->list[i]->len, false, depth * 2);
            break;
        case INT_t:
            printf("%d", *(int *)dynamicArray->list[i]->value);
            break;
        case DYN_ARR_t:
            PrintDynamicArray(dynamicArray->list[i]->value, pretty, depth * 2);
            break;
        default:
            break;
        }
        if (i != dynamicArray->size - 1)
        {
            if (pretty)
            {
                printf(",\n");
                printSpaces(depth);
            }
            else
            {
                printf(", ");
            }
        }
    }
    if (pretty)
    {
        printf("\n");
    }
    depth /= 2;
    if (depth == 1)
    {
        depth--;
    }
    printSpaces(depth);
    printf("]");
    if (depth == 0)
    {
        printf("\n");
    }
}

void PrintDynamicArray(DynamicArray *dynamicArray, bool pretty, int depth)
{
    if (dynamicArray == NULL)
    {
        return;
    }
    printf("[");
    if (pretty)
    {
        printf("\n");
        printSpaces(depth);
    }
    printDynamicArrayHelper(dynamicArray, pretty, depth);
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

void DynamicArrayRemoveFirst(DynamicArray *dynamicArray)
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

DynamicArray *DynamicArrayInitFromStr(char *input_str)
{
    if (input_str == NULL)
    {
        printf("invalid input to DynamicArrayInitFromStr\n");
        return NULL;
    }
    size_t input_str_len = strlen(input_str);
    if (input_str_len == 0 || input_str[0] != BRACKET_OPEN_CHAR || input_str[input_str_len - 1] != BRACKET_CLOSE_CHAR)
    {
        printf("invalid input to DynamicArrayInitFromStr\n");
        return NULL;
    }
    DynamicArray *dynamicArray = DefaultDynamicArrayInit();
    if (dynamicArray == NULL)
    {
        printf("out of memory for dynamicArray\n");
        return NULL;
    }

    // char *value_start = input_str;
    char *value_end = input_str;
    for (size_t i = 0; i < input_str_len && *input_str != NULL_CHAR; i++)
    {
        if (*input_str == COMMA_CHAR)
        {
            value_end = input_str;
            printf("%c\n", *value_end);
        }
        input_str++;
    }

    return dynamicArray;
}
