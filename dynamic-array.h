#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

enum DynamicArrayElementType
{
    INT_ARR_t,
    INT_t,
    CHAR_ARR_t,
};

typedef struct
{
    enum DynamicArrayElementType type;
    void *value;
    unsigned int len;
} DynamicArrayElement;

typedef struct
{
    unsigned int size;
    unsigned int capacity;
    DynamicArrayElement **list;
} DynamicArray;

DynamicArray *DynamicArrayInit(unsigned int);
DynamicArray *DefaultDynamicArrayInit(void);

void DynamicArrayAdd(DynamicArray *, DynamicArrayElement *);

void PrintDynamicArray(DynamicArray *);

void FreeDynamicArray(DynamicArray *);

#endif
