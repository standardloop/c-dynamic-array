#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "./dynamic-array.h"
#include "./util.h"

static char *quickString(char *);
static int *quickInt(int);

static char *quickString(char *input)
{
    char *new_str = malloc(sizeof(char) * (strlen(input) + 1));
    strcpy(new_str, input);
    return new_str;
}

static int *quickInt(int size)
{
    int *int_arr = malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++)
    {
        int_arr[i] = i;
    }
    return int_arr;
}

int main(void)
{
    DynamicArray *dynamic_array = DefaultDynamicArrayInit();
    if (dynamic_array == NULL)
    {
        return EXIT_FAILURE;
    }
    DynamicArrayElement *string_ele = DynamicArrayElementInit(CHAR_ARR_t, quickString("hello"), 6);
    DynamicArrayAddFirst(dynamic_array, string_ele);

    // add an int array to the array
    DynamicArrayElement *int_arr_ele = DynamicArrayElementInit(INT_ARR_t, quickInt(6), 6);
    DynamicArrayAddFirst(dynamic_array, int_arr_ele);

    // add an int to the array
    int *single_int_ele_value = malloc(sizeof(int) * 1);
    *single_int_ele_value = 1000;
    DynamicArrayElement *single_int_ele = DynamicArrayElementInit(INT_t, single_int_ele_value, 1);
    DynamicArrayAddLast(dynamic_array, single_int_ele);

    // add a dynamic array to the dynamic array
    DynamicArray *dynamicArray_2 = DefaultDynamicArrayInit();
    DynamicArrayElement *dyn_arr_ele = DynamicArrayElementInit(DYN_ARR_t, dynamic_array, dynamic_array->size);
    DynamicArrayAddFirst(dynamicArray_2, dyn_arr_ele);

    // create a copy of the dynamic array and free the old one
    DynamicArray *copy = DynamicArrayReplicate(dynamicArray_2);
    FreeDynamicArray(dynamicArray_2);

    DynamicArray *copy_again = DynamicArrayReplicate(copy);
    DynamicArrayElement *dyn_arr_ele_2 = DynamicArrayElementInit(DYN_ARR_t, copy, copy->size);
    DynamicArrayAddFirst(copy_again, dyn_arr_ele_2);

    FreeDynamicArray(copy_again);

    DynamicArray *dyn_arr_from_str = DynamicArrayInitFromStr("[[1,2,3],[4,5,6, 8, 9, 4, 3], \"test\", [234, 542, 6774], [1,2,4], [1, \"nested\"]]");

    FreeDynamicArray(dyn_arr_from_str);

    DynamicArray *dyn_arr_from_str_again = DynamicArrayInitFromStr("[[1,2,3],[4,5,6, 8, 9, 4, 3], \"test\", [234, 542, 6774], [1,2,4], [1, \"nested\"]]");
    char *string_from_dyn_arr = DynamicArrayToString(dyn_arr_from_str_again);
    printf("%s\n", string_from_dyn_arr);

    return EXIT_SUCCESS;
}
