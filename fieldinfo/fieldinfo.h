#ifndef FIELDINFO_H
#define FIELDINFO_H

#include <stdbool.h>
#include <stddef.h>

typedef struct FieldInfo FieldInfo;

struct FieldInfo {
    size_t size;
    char* typeName;                
    
    void (*destroy)(void* element);
    char* (*getName)(const void* element);
    int (*getDate)(const void* element);
    int (*getIdSeries)(const void* element);
    int (*getIdNumbers)(const void* element);
    void* (*copy)(const void* element);
    bool (*equals)(const void* a, const void* b);
};

const FieldInfo* getStudentFieldInfo(void);
const FieldInfo* getTeacherFieldInfo(void);
const FieldInfo* getRobotFieldInfo(void);

#endif
