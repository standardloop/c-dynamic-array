#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "./util.h"

extern void CopyString(const char *src, char *des, size_t len, size_t des_offset)
{
    if (src == NULL || des == NULL || len <= 0)
    {
        return;
    }

    char *dest_it = des + des_offset;
    size_t size = 0;
    while (size < len)
    {
        *dest_it = *src;
        dest_it++;
        src++;
        size++;
    }
}

extern bool IsCharInString(const char *input_str, char checker)
{
    while (*input_str != NULL_CHAR)
    {
        if (*input_str == checker)
        {
            return true;
        }
        input_str++;
    }
    return false;
}

extern size_t NumCharInString(const char *input_str, char checker)
{
    size_t count = 0;
    while (*input_str != NULL_CHAR)
    {
        if (*input_str == checker)
        {
            count++;
        }
        input_str++;
    }
    return count;
}

// fix me, should be able to combine this logic with DynamicArrayInitFromStr
extern int *StringToIntArr(const char *input_str, size_t num_elements)
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
