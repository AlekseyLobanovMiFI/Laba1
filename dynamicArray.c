#include "../dynamicArray/dynamicArray.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

DynamicArray* dynamicArrayCreate(const FieldInfo* info, size_t initialCapacity) {
    if (!info) return NULL;
    if (initialCapacity == 0) initialCapacity = 4;

    DynamicArray* array = malloc(sizeof(DynamicArray));
    if (!array) return NULL;

    size_t alloc_size = initialCapacity * info->size;
    array->data = malloc(alloc_size);
    if (!array->data) {
        free(array);
        return NULL;
    }

    array->size = 0;
    array->capacity = initialCapacity;
    array->elem_size = info->size;
    array->info = (FieldInfo*)info;

    return array;
}

void dynamicArrayDestroy(DynamicArray* array) {
    if (!array) return;

    for (size_t i = 0; i < array->size; i++) {
        void* elem = (char*)array->data + i * array->elem_size;
        array->info->destroy(elem);
    }

    free(array->data);
    free(array);
}

bool dynamicArrayIsEmpty(const DynamicArray* array) {
    return array ? array->size == 0 : true;
}

size_t dynamicArraySize(const DynamicArray* array) {
    return array ? array->size : 0;
}

bool dynamicArrayAppend(DynamicArray* array, void* element) {
    if (!array || !element) return false;

    void* copied = array->info->copy(element);
    if (!copied) return false;

    if (array->size >= array->capacity) {
        size_t newCapacity = array->capacity * 2 ? array->capacity * 2 : 4;
        void* newData = realloc(array->data, newCapacity * array->elem_size);
        if (!newData) {
            array->info->destroy(copied);
            return false;
        }
        array->data = newData;
        array->capacity = newCapacity;
    }

    void* slot = (char*)array->data + array->size * array->elem_size;
    memcpy(slot, copied, array->elem_size);
    free(copied);
    array->size++;
    return true;
}

void* dynamicArrayGet(const DynamicArray* array, size_t index) {
    if (!array || index >= array->size) return NULL;
    return (char*)array->data + index * array->elem_size;
}

bool dynamicArraySet(DynamicArray* array, size_t index, void* element) {
    if (!array || index >= array->size || !element) return false;

    void* elem = (char*)array->data + index * array->elem_size;
    array->info->destroy(elem);
    memcpy(elem, element, array->elem_size);
    return true;
}

DynamicArray* dynamicArrayConcat(const DynamicArray* left, const DynamicArray* right) {
    if (!left || !right || left->info != right->info) {
        return NULL;
    }

    DynamicArray* result = dynamicArrayCreate(left->info, left->size + right->size);
    if (!result) return NULL;

    for (size_t i = 0; i < left->size; i++) {
        void* src = (char*)left->data + i * left->elem_size;
        void* copy = left->info->copy(src);
        void* dst = (char*)result->data + i * result->elem_size;
        memcpy(dst, copy, result->elem_size);
        free(copy);
    }

    for (size_t i = 0; i < right->size; i++) {
        void* src = (char*)right->data + i * right->elem_size;
        void* copy = right->info->copy(src);
        void* dst = (char*)result->data + (left->size + i) * result->elem_size;
        memcpy(dst, copy, result->elem_size);
        free(copy);
    }

    result->size = left->size + right->size;
    return result;
}

bool dynamicArrayWhere(DynamicArray* array,
                       bool (*predicate)(const void*),
                       DynamicArray* result) {
    if (!array || !predicate || !result || array->info != result->info) {
        return false;
    }

    for (size_t i = 0; i < result->size; i++) {
        void* elem = (char*)result->data + i * result->elem_size;
        result->info->destroy(elem);
    }
    result->size = 0;

    for (size_t i = 0; i < array->size; i++) {
        void* elem = (char*)array->data + i * array->elem_size;
        if (predicate(elem)) {
            dynamicArrayAppend(result, elem);
        }
    }

    return true;
}

void dynamicArrayPrint(const DynamicArray* array, const char* title) {
    if (!array) {
        printf("%s: [NULL DynamicArray]\n", title);
        return;
    }

    printf("%s (%zu элементов, тип: %s):\n",
           title, dynamicArraySize(array), array->info->typeName);

    for (size_t i = 0; i < dynamicArraySize(array); i++) {
        void* elem = dynamicArrayGet(array, i);
        char* name = array->info->getName(elem);
        if (name) {
            printf("  [%d-%d] %s (г. %d)\n",
                   array->info->getIdSeries(elem),
                   array->info->getIdNumbers(elem),
                   name ? name : "",
                   array->info->getDate(elem));
            free(name);
        } else {
            printf("  [???]\n");
        }
    }
}