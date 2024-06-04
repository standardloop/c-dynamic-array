#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#define RESIZE_MULTIPLE 2
#define DEFAULT_LIST_SIZE 5

#define BRACKET_OPEN_CHAR '['
#define BRACKET_CLOSE_CHAR ']'
#define SPACE_CHAR ' '
#define COMMA_CHAR ','

#define NULL_CHAR '\0'

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

DynamicArray *DynamicArrayInit(unsigned int);
DynamicArray *DefaultDynamicArrayInit(void);
DynamicArray *DynamicArrayInitFromStr(char *);
DynamicArray *DynamicArrayReplicate(DynamicArray *);

DynamicArrayElement *DynamicArrayElementInit(enum DynamicArrayElementType, void *, unsigned int);

void DynamicArrayAddFirst(DynamicArray *, DynamicArrayElement *);
void DynamicArrayAddLast(DynamicArray *, DynamicArrayElement *);
void DynamicArrayAdd(DynamicArray *, DynamicArrayElement *, unsigned int);

void DynamicArrayRemove(DynamicArray *, unsigned int);
void DynamicArrayRemoveFirst(DynamicArray *);
void DynamicArrayRemoveLast(DynamicArray *);

void PrintDynamicArray(DynamicArray *, bool, int);
void FreeDynamicArray(DynamicArray *);

#endif
