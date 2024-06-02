#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#define RESIZE_MULTIPLE 2

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

DynamicArrayElement *DynamicArrayElementInit(enum DynamicArrayElementType, void *, unsigned int);

void DynamicArrayAddFirst(DynamicArray *, DynamicArrayElement *);
void DynamicArrayAddLast(DynamicArray *, DynamicArrayElement *);
void DynamicArrayAdd(DynamicArray *, DynamicArrayElement *, unsigned int);

void DynamicArrayRemove(DynamicArray *, unsigned int);
void DynamicArrayRemoveFirst(DynamicArray *);
void DynamicArrayRemoveLast(DynamicArray *);

void PrintDynamicArray(DynamicArray *, bool);
void FreeDynamicArray(DynamicArray *);

#endif
