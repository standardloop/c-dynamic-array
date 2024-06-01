#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "./dynamic-array.h"

int main(void)
{
    DynamicArray *dynamicArray = DefaultDynamicArrayInit();
    if (dynamicArray == NULL)
    {
        return EXIT_FAILURE;
    }
    // add a string to the array
    DynamicArrayElement *string_ele = malloc(sizeof(DynamicArrayElement));
    char *string_ele_value = malloc(sizeof(char) * 6);
    strcpy(string_ele_value, "hello");
    string_ele->len = 6;
    string_ele->type = CHAR_ARR_t;
    string_ele->value = string_ele_value;
    DynamicArrayAdd(dynamicArray, string_ele);

    // add an int array to the array
    DynamicArrayElement *int_arr_ele = malloc(sizeof(DynamicArrayElement));
    int *int_arr_ele_value = malloc(sizeof(int) * 6);
    for (int i = 0; i < 6; i++)
    {
        int_arr_ele_value[i] = i;
    }
    int_arr_ele->len = 6;
    int_arr_ele->type = INT_ARR_t;
    int_arr_ele->value = int_arr_ele_value;
    DynamicArrayAdd(dynamicArray, int_arr_ele);

    // add an int to the array
    DynamicArrayElement *single_int_ele = malloc(sizeof(DynamicArrayElement));
    int *single_int_ele_value = malloc(sizeof(int) * 1);
    *single_int_ele_value = 1000;
    single_int_ele->len = 1;
    single_int_ele->type = INT_t;
    single_int_ele->value = single_int_ele_value;
    DynamicArrayAdd(dynamicArray, single_int_ele);

    PrintDynamicArray(dynamicArray);

    FreeDynamicArray(dynamicArray);
    return EXIT_SUCCESS;
}
