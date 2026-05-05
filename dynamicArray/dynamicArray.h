#ifndef DynamicArray_H
#define DynamicArray_H

#include <stdbool.h>
#include <stddef.h>
#include "..\fieldinfo\fieldinfo.h"

typedef struct DynamicArray DynamicArray;

struct DynamicArray {
    void* data;
    size_t size;
    size_t capacity;
    size_t elem_size;
    FieldInfo* info;
};

DynamicArray* dynamicArrayCreate(const FieldInfo* info, size_t initialCapacity);
void dynamicArrayDestroy(DynamicArray* array);   // DynamicArray → array

bool dynamicArrayIsEmpty(const DynamicArray* array);
size_t dynamicArraySize(const DynamicArray* array);
void* dynamicArrayGet(const DynamicArray* array, size_t index);
bool dynamicArraySet(DynamicArray* array, size_t index, void* element);
bool dynamicArrayAppend(DynamicArray* array, void* element);

bool dynamicArrayWhere(DynamicArray* array,
                 bool (*predicate)(const void*),
                 DynamicArray* result);
DynamicArray* dynamicArrayConcat(const DynamicArray* left, const DynamicArray* right);
DynamicArray* dynamicArrayMap(const DynamicArray* array,
                        void* (*mapper)(const void*, void*),
                        void* userData);

void dynamicArrayPrint(const DynamicArray* array, const char* title);

#endif
