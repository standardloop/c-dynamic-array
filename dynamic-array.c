#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "./dynamic-array.h"
#include "./util.h"

static inline bool isDynamicArrayFull(DynamicArray *);
static inline bool isDynamicArrayEmpty(DynamicArray *);
static void freeDynamicArrayList(DynamicArrayElement **, unsigned int, bool);
static void freeDynamicArrayListElement(DynamicArrayElement *element);
static void dynamicArrayResize(DynamicArray *);

static DynamicArrayElement *dynamicArrayElementReplicate(DynamicArrayElement *);

static void printIntArr(int *, unsigned int, bool, int);
static void printDynamicArrayHelper(DynamicArray *, bool, int);
static inline void printSpaces(int);

static int *stringToIntArr(const char *, size_t);

extern DynamicArray *DefaultDynamicArrayInit(void)
{
    return DynamicArrayInit(DEFAULT_LIST_SIZE);
}

extern DynamicArray *DynamicArrayInit(unsigned int initial_capacity)
{
    DynamicArray *dynamic_array = malloc(sizeof(DynamicArray));
    if (dynamic_array == NULL)
    {
        printf("[ERROR]: could not allocate memory for DynamicArray\n");
        return NULL;
    }
    dynamic_array->size = 0;
    dynamic_array->capacity = initial_capacity;
    dynamic_array->list = malloc(sizeof(DynamicArrayElement *) * dynamic_array->capacity);
    return dynamic_array;
}

extern void DynamicArrayAddFirst(DynamicArray *dynamic_array, DynamicArrayElement *element)
{
    DynamicArrayAdd(dynamic_array, element, 0);
}

extern void DynamicArrayAddLast(DynamicArray *dynamic_array, DynamicArrayElement *element)
{
    if (dynamic_array == NULL || element == NULL)
    {
        return;
    }
    DynamicArrayAdd(dynamic_array, element, dynamic_array->size);
}

extern void DynamicArrayAdd(DynamicArray *dynamic_array, DynamicArrayElement *element, unsigned int index)
{
    if (dynamic_array == NULL || element == NULL)
    {
        return;
    }
    if (isDynamicArrayFull(dynamic_array))
    {
        dynamicArrayResize(dynamic_array);
    }
    for (unsigned int i = dynamic_array->size; i > index; i--)
    {
        dynamic_array->list[i] = dynamic_array->list[i - 1];
    }

    dynamic_array->list[index] = element;
    dynamic_array->size++;
}

static void dynamicArrayResize(DynamicArray *dynamic_array)
{
    if (dynamic_array == NULL)
    {
        return;
    }

    DynamicArrayElement **newList = malloc(sizeof(DynamicArrayElement *) * dynamic_array->capacity * RESIZE_MULTIPLE);
    if (newList == NULL)
    {
        printf("not enough memory for newList\n");
        return; // FIXME
    }

    for (unsigned int i = 0; i < dynamic_array->size; i++)
    {
        newList[i] = dynamic_array->list[i];
    }
    freeDynamicArrayList(dynamic_array->list, dynamic_array->size, false);
    dynamic_array->list = newList;
    dynamic_array->capacity *= RESIZE_MULTIPLE;
}

static inline bool isDynamicArrayFull(DynamicArray *dynamic_array)
{
    return dynamic_array->capacity == dynamic_array->size;
}

static inline bool isDynamicArrayEmpty(DynamicArray *dynamic_array)
{
    return dynamic_array->size == 0;
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

extern void FreeDynamicArray(DynamicArray *dynamic_array)
{
    if (dynamic_array == NULL)
    {
        return;
    }
    if (dynamic_array->list != NULL)
    {
        freeDynamicArrayList(dynamic_array->list, dynamic_array->size, true);
    }
    free(dynamic_array);
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

            printf(", ");
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

static void printDynamicArrayHelper(DynamicArray *dynamic_array, bool pretty, int depth)
{
    for (unsigned int i = 0; i < dynamic_array->size; i++)
    {
        switch (dynamic_array->list[i]->type)
        {
        case CHAR_ARR_t:
            printf("\"%s\"", (char *)dynamic_array->list[i]->value);
            break;
        case INT_ARR_t:
            printIntArr((int *)dynamic_array->list[i]->value, dynamic_array->list[i]->len, false, depth * 2);
            break;
        case INT_t:
            printf("%d", *(int *)dynamic_array->list[i]->value);
            break;
        case DYN_ARR_t:
            PrintDynamicArray(dynamic_array->list[i]->value, pretty, depth + 2);
            break;
        default:
            break;
        }
        if (i != dynamic_array->size - 1)
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
    depth -= 2;
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

extern void PrintDynamicArray(DynamicArray *dynamic_array, bool pretty, int depth)
{
    if (dynamic_array == NULL)
    {
        return;
    }
    printf("[");
    if (pretty)
    {
        printf("\n");
        printSpaces(depth);
    }
    printDynamicArrayHelper(dynamic_array, pretty, depth);
}

extern void DynamicArrayRemove(DynamicArray *dynamic_array, unsigned int index)
{
    if (dynamic_array == NULL || index >= dynamic_array->size || isDynamicArrayEmpty(dynamic_array))
    {
        return;
    }
    freeDynamicArrayListElement(dynamic_array->list[index]);

    for (unsigned int i = index + 1; i < dynamic_array->size; i++)
    {
        dynamic_array->list[i - 1] = dynamic_array->list[i];
    }

    dynamic_array->size--;
}

extern void DynamicArrayRemoveFirst(DynamicArray *dynamic_array)
{
    if (dynamic_array == NULL)
    {
        return;
    }
    DynamicArrayRemove(dynamic_array, 0);
}

extern void DynamicArrayRemoveLastElement(DynamicArray *dynamic_array)
{
    if (dynamic_array == NULL)
    {
        return;
    }
    DynamicArrayRemove(dynamic_array, dynamic_array->size - 1);
}

extern DynamicArrayElement *DynamicArrayElementInit(enum DynamicArrayElementType type, void *value, unsigned int len)
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

static DynamicArrayElement *dynamicArrayElementReplicate(DynamicArrayElement *dynamicArrayElement)
{
    if (dynamicArrayElement == NULL)
    {
        return NULL;
    }
    void *value = NULL;
    switch (dynamicArrayElement->type)
    {
    case INT_t:
    case INT_ARR_t:
        value = (int *)malloc(sizeof(int) * dynamicArrayElement->len);
        memcpy(value, dynamicArrayElement->value, sizeof(int) * dynamicArrayElement->len);
        break;
    case CHAR_ARR_t:
        value = (char *)malloc(sizeof(char) * dynamicArrayElement->len);
        memcpy(value, dynamicArrayElement->value, sizeof(char) * dynamicArrayElement->len);
        break;
    case DYN_ARR_t:
        value = (DynamicArray *)DynamicArrayReplicate(dynamicArrayElement->value);
    default:
        break;
    }
    return DynamicArrayElementInit(dynamicArrayElement->type, value, dynamicArrayElement->len);
}

extern DynamicArray *DynamicArrayReplicate(DynamicArray *dynamic_array)
{
    if (dynamic_array == NULL)
    {
        return NULL;
    }
    DynamicArray *deep_clone = DynamicArrayInit(dynamic_array->capacity);

    for (unsigned int i = 0; i < dynamic_array->size; i++)
    {
        deep_clone->list[i] = dynamicArrayElementReplicate(dynamic_array->list[i]);
        deep_clone->size++;
    }
    return deep_clone;
}

extern DynamicArray *DynamicArrayInitFromStr(char *input_str)
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
    DynamicArray *dynamic_array = DefaultDynamicArrayInit();
    if (dynamic_array == NULL)
    {
        printf("out of memory for dynamic_array\n");
        return NULL;
    }

    input_str++;
    char *value_start = input_str;
    char *value_end = NULL;
    size_t char_count = 1;
    bool nested = false;
    if (*value_start == BRACKET_OPEN_CHAR)
    {
        nested = true;
    }

    while (*input_str != NULL_CHAR)
    {
        if (((*input_str == COMMA_CHAR) && !nested) || ((*input_str == BRACKET_CLOSE_CHAR) && nested) || char_count == input_str_len - 1)
        {
            enum DynamicArrayElementType element_type;
            bool is_element_arr = false;
            DynamicArrayElement *element = NULL;
            if (*input_str == COMMA_CHAR || char_count == input_str_len - 1)
            {
                value_end = input_str - 1;
            }
            else
            {
                value_end = input_str;
            }

            if (*value_start == DOUBLE_QUOTES_CHAR && *value_end == DOUBLE_QUOTES_CHAR)
            {
                value_start++;
                value_end--;
            }
            else if (*value_start == BRACKET_OPEN_CHAR && *value_end == BRACKET_CLOSE_CHAR)
            {
                is_element_arr = true;
            }
            // printf("%c %c\n", *value_start, *value_end);
            size_t value_size = (value_end - value_start) + 1;

            if (value_size > 0)
            {
                char *substring = malloc(sizeof(char) * (value_size + 1));
                CopyString(value_start, substring, value_size, 0);

                substring[value_size] = NULL_CHAR;

                if (is_element_arr)
                {
                    if (IsCharInString(substring, DOUBLE_QUOTES_CHAR))
                    {
                        element_type = DYN_ARR_t;
                    }
                    else
                    {
                        element_type = INT_ARR_t;
                    }
                }
                else
                {
                    // FIXME, zero value
                    if (!atoi(substring))
                    {
                        element_type = CHAR_ARR_t;
                    }
                    else
                    {
                        element_type = INT_t;
                    }
                }

                if (element_type == CHAR_ARR_t)
                {
                    element = DynamicArrayElementInit(element_type, substring, (value_size + 1));
                }
                else if (element_type == INT_t)
                {
                    int value_temp = atoi(substring);
                    free(substring);
                    int *value = malloc(sizeof(int) * 1);
                    *value = value_temp;
                    element = DynamicArrayElementInit(element_type, value, 1);
                }
                else if (element_type == INT_ARR_t)
                {
                    size_t arr_size = NumCharInString(substring, COMMA_CHAR) + 1;
                    element = DynamicArrayElementInit(element_type, stringToIntArr(substring, arr_size), arr_size);
                    free(substring);
                }
                else if (element_type == DYN_ARR_t)
                {
                    DynamicArray *sub_dyn_array = DynamicArrayInitFromStr(substring);
                    element = DynamicArrayElementInit(element_type, sub_dyn_array, sub_dyn_array->size);
                    free(substring);
                }
                else
                {
                    exit(1);
                }

                DynamicArrayAddLast(dynamic_array, element);

                input_str++;
                char_count++;
                if (*input_str == COMMA_CHAR)
                {
                    input_str++;
                    char_count++;
                }
                while (*input_str == SPACE_CHAR)
                {
                    input_str++;
                    char_count++;
                }
                value_start = input_str;
                nested = (*value_start == BRACKET_OPEN_CHAR) && (char_count != input_str_len - 1);
            }
        }
        input_str++;
        char_count++;
    }

    return dynamic_array;
}

static int *stringToIntArr(const char *input_str, size_t num_elements)
{
    int *int_arr = malloc(sizeof(int) * num_elements);
    size_t num_elements_in_arr = 0;
    size_t input_str_len = strlen(input_str);
    size_t char_count = 1;
    input_str++;
    const char *value_start = input_str;
    const char *value_end = NULL;
    while (*input_str != NULL_CHAR && num_elements_in_arr < num_elements)
    {
        if (*input_str == COMMA_CHAR || char_count == input_str_len - 1)
        {
            value_end = input_str - 1;
            size_t value_size = (value_end - value_start) + 1;
            char *substring = malloc(sizeof(char) * (value_size + 1));
            CopyString(value_start, substring, value_size, 0);
            substring[value_size] = NULL_CHAR;
            // printf("%s\n", substring);

            int value_temp = atoi(substring);
            free(substring);
            int_arr[num_elements_in_arr] = value_temp;
            num_elements_in_arr++;

            value_start = input_str + 1;
            while (*value_start == SPACE_CHAR)
            {
                value_start++;
            }
        }
        input_str++;
        char_count++;
    }
    return int_arr;
}

char *DynamicArrayToString(DynamicArray *dynamic_array)
{
    if (dynamic_array == NULL)
    {
        return NULL;
    }
    FreeDynamicArray(dynamic_array);
    return NULL;
}
