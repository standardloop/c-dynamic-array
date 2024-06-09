#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#define RESIZE_MULTIPLE 2
#define DEFAULT_LIST_SIZE 5

enum DynamicArrayElementType
{
    INT_ARR_t,
    INT_t,
    CHAR_ARR_t,
    DYN_ARR_t,
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

extern DynamicArray *DynamicArrayInit(unsigned int);
extern DynamicArray *DefaultDynamicArrayInit(void);
extern DynamicArray *DynamicArrayInitFromStr(char *);
extern DynamicArray *DynamicArrayReplicate(DynamicArray *);

extern DynamicArrayElement *DynamicArrayElementInit(enum DynamicArrayElementType, void *, unsigned int);

extern void DynamicArrayAddFirst(DynamicArray *, DynamicArrayElement *);
extern void DynamicArrayAddLast(DynamicArray *, DynamicArrayElement *);
extern void DynamicArrayAdd(DynamicArray *, DynamicArrayElement *, unsigned int);

extern void DynamicArrayRemove(DynamicArray *, unsigned int);
extern void DynamicArrayRemoveFirst(DynamicArray *);
extern void DynamicArrayRemoveLast(DynamicArray *);

extern void PrintDynamicArray(DynamicArray *, bool, int);
extern void FreeDynamicArray(DynamicArray *);

extern void *ArrayFromStr(char *, enum DynamicArrayElementType);

#endif
