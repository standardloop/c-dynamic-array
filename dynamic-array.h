#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

// enum DynamicArrayElementType
// {
//     BOOL_t,
//     NUMBER_t,
//     STRING_t,
// };

// typedef struct
// {
//     enum DynamicArrayElementType type;
//     void *value;
// } DynamicArrayElement;

typedef struct
{
    unsigned int size;
    unsigned int capacity;
    void **list;
} DynamicArray;

DynamicArray *DynamicArrayInit(unsigned int);
DynamicArray *DefaultDynamicArrayInit(void);

void DynamicArrayAdd(DynamicArray *, void *);

void PrintDynamicArray(DynamicArray *);

void FreeDynamicArray(DynamicArray *);

#endif
