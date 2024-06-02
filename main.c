#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "./dynamic-array.h"

int main(void)
{
    DynamicArray *dynamicArray = DefaultDynamicArrayInit();
    if (dynamicArray == NULL)
    {
        return EXIT_FAILURE;
    }

    // add a string to the array
    size_t string_ele_length = 6;
    char *string_ele_value = malloc(sizeof(char) * string_ele_length);
    strcpy(string_ele_value, "hello");
    DynamicArrayElement *string_ele = DynamicArrayElementInit(CHAR_ARR_t, string_ele_value, string_ele_length);
    DynamicArrayAddFirst(dynamicArray, string_ele);

    // add an int array to the array
    size_t int_arr_ele_length = 6;
    int *int_arr_ele_value = malloc(sizeof(int) * int_arr_ele_length);
    for (int i = 0; i < (int)int_arr_ele_length; i++)
    {
        int_arr_ele_value[i] = i;
    }
    DynamicArrayElement *int_arr_ele = DynamicArrayElementInit(INT_ARR_t, int_arr_ele_value, int_arr_ele_length);
    DynamicArrayAddFirst(dynamicArray, int_arr_ele);

    // add an int to the array
    int *single_int_ele_value = malloc(sizeof(int) * 1);
    *single_int_ele_value = 1000;
    DynamicArrayElement *single_int_ele = DynamicArrayElementInit(INT_t, single_int_ele_value, 1);
    DynamicArrayAddLast(dynamicArray, single_int_ele);

    // DynamicArrayRemoveFirst(dynamicArray);
    PrintDynamicArray(dynamicArray, true);

    FreeDynamicArray(dynamicArray);
    return EXIT_SUCCESS;
}
