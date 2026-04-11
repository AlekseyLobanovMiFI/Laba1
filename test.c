#include "test.h"

#include <stdio.h>
#include <stdlib.h>

////////////////////////////////////////////////////////////////////////////////////
// === 1. Тесты для DynamicArray ===

static void print_array_simple(const DynamicArray* array, const char* title) {
    if (!array) {
        printf("%s: NULL\n", title);
        return;
    }
    printf("%s (size = %zu, capacity = %zu):\n",
           title,
           dynamicArraySize(array),
           array->capacity);
    for (size_t i = 0; i < dynamicArraySize(array); i++) {
        void* elem = dynamicArrayGet(array, i);
        char* name = array->info->getName(elem);
        if (!name) {
            printf("  [%zu] ???\n", i);
        } else {
            printf("  [%zu] %s\n", i, name);
            free(name);
        }
    }
}

void test_dynamic_array_basic(void) {
    printf("\n=== 1.1 test_dynamic_array_basic ===\n");

    const FieldInfo* info = getStudentFieldInfo();
    if (!info) {
        printf("getStudentFieldInfo вернул NULL\n");
        return;
    }

    DynamicArray* array = dynamicArrayCreate(info, 2);
    if (!array) {
        printf("dynamicArrayCreate вернул NULL\n");
        return;
    }

    printf("dynamicArrayIsEmpty: %s\n",
           dynamicArrayIsEmpty(array) ? "true" : "false");
    printf("dynamicArraySize: %zu\n", dynamicArraySize(array));

    dynamicArrayDestroy(array);
}

void test_dynamic_array_person(void) {
    printf("\n=== 1.2 test_dynamic_array_person ===\n");

    const FieldInfo* info = getStudentFieldInfo();
    if (!info) {
        printf("getStudentFieldInfo вернул NULL\n");
        return;
    }

    DynamicArray* array = dynamicArrayCreate(info, 2);
    if (!array) {
        printf("dynamicArrayCreate вернул NULL\n");
        return;
    }

    Person* p1 = personCreate("Ivan", "A", "Ivanov", 1, 123, 1990);
    Person* p2 = personCreate("Anna", "B", "Petrova", 2, 222, 1992);
    Person* p3 = personCreate("Sergey", NULL, "Sidorov", 3, 333, 1995);

    if (!p1 || !p2 || !p3) {
        printf("personCreate вернул NULL\n");
        personDestroy(p1);
        personDestroy(p2);
        personDestroy(p3);
        dynamicArrayDestroy(array);
        return;
    }

    dynamicArrayAppend(array, p1);
    dynamicArrayAppend(array, p2);
    dynamicArrayAppend(array, p3);

    print_array_simple(array, "Студенты после append");

    dynamicArrayDestroy(array);
}

void test_dynamic_array_robot(void) {
    printf("\n=== 1.3 test_dynamic_array_robot ===\n");

    const FieldInfo* info = getRobotFieldInfo();
    if (!info) {
        printf("getRobotFieldInfo вернул NULL\n");
        return;
    }

    DynamicArray* array = dynamicArrayCreate(info, 2);
    if (!array) {
        printf("dynamicArrayCreate вернул NULL\n");
        return;
    }

    Robot* r1 = robotCreate("R2D2", 2000);
    Robot* r2 = robotCreate("C3PO", 1999);

    if (!r1 || !r2) {
        printf("robotCreate вернул NULL\n");
        robotDestroy(r1);
        robotDestroy(r2);
        dynamicArrayDestroy(array);
        return;
    }

    dynamicArrayAppend(array, r1);
    dynamicArrayAppend(array, r2);

    print_array_simple(array, "Роботы после append");

    dynamicArrayDestroy(array);
}

////////////////////////////////////////////////////////////////////////////////////
// === 2. Тесты для Person и Robot ===

void test_person_basic(void) {
    printf("\n=== 2.1 test_person_basic ===\n");

    Person* p1 = personCreate("Ivan", "A", "Ivanov", 1, 123, 1990);
    if (!p1) {
        printf("personCreate(p1) вернул NULL\n");
        return;
    }

    char* name1 = personGetFullName(p1);
    if (!name1) {
        printf("personGetFullName(p1) вернул NULL\n");
    } else {
        printf("personGetFullName: %s\n", name1);
        free(name1);
    }

    int date1 = personGetDate(p1);
    printf("personGetDate: %d\n", date1);

    Person* p1_copy = personCopy(p1);
    if (!p1_copy) {
        printf("personCopy вернул NULL\n");
    } else {
        bool eq = personEquals(p1, p1_copy);
        printf("personEquals(p1, p1_copy): %s\n", eq ? "true" : "false");
        personDestroy(p1_copy);
    }

    personDestroy(p1);
}

void test_robot_basic(void) {
    printf("\n=== 2.2 test_robot_basic ===\n");

    Robot* r1 = robotCreate("R2D2", 2000);
    if (!r1) {
        printf("robotCreate(r1) вернул NULL\n");
        return;
    }

    char* name1 = robotGetName(r1);
    if (!name1) {
        printf("robotGetName(r1) вернул NULL\n");
    } else {
        printf("robotGetName: %s\n", name1);
        free(name1);
    }

    int date1 = robotGetDate(r1);
    printf("robotGetDate: %d\n", date1);

    Robot* r1_copy = robotCopy(r1);
    if (!r1_copy) {
        printf("robotCopy вернул NULL\n");
    } else {
        bool eq = robotEquals(r1, r1_copy);
        printf("robotEquals(r1, r1_copy): %s\n", eq ? "true" : "false");
        robotDestroy(r1_copy);
    }

    robotDestroy(r1);
}

void test_person_robot(void) {
    printf("\n=== 2.3 test_person_robot ===\n");
    test_person_basic();
    test_robot_basic();
}

////////////////////////////////////////////////////////////////////////////////////
// === 3. Тесты для FieldInfo ===

void test_fieldinfo_person(void) {
    printf("\n=== 3.1 test_fieldinfo_person ===\n");

    const FieldInfo* info = getStudentFieldInfo();
    if (!info) {
        printf("getStudentFieldInfo вернул NULL\n");
        return;
    }

    Person* p = personCreate("Max", "V", "Kozlov", 1, 111, 1999);
    if (!p) {
        printf("personCreate вернул NULL\n");
        return;
    }

    char* name = info->getName(p);
    if (!name) {
        printf("FieldInfo::getName вернул NULL\n");
    } else {
        printf("FieldInfo::getName: %s\n", name);
        free(name);
    }

    int date = info->getDate(p);
    printf("FieldInfo::getDate: %d\n", date);

    void* copy = info->copy(p);
    if (!copy) {
        printf("FieldInfo::copy вернул NULL\n");
    } else {
        bool eq = info->equals(p, copy);
        printf("FieldInfo::equals(p, copy): %s\n", eq ? "true" : "false");
        info->destroy(copy);
    }

    info->destroy(p);
}

void test_fieldinfo_robot(void) {
    printf("\n=== 3.2 test_fieldinfo_robot ===\n");

    const FieldInfo* info = getRobotFieldInfo();
    if (!info) {
        printf("getRobotFieldInfo вернул NULL\n");
        return;
    }

    Robot* r = robotCreate("GuardBot", 2100);
    if (!r) {
        printf("robotCreate вернул NULL\n");
        return;
    }

    char* name = info->getName(r);
    if (!name) {
        printf("FieldInfo::getName вернул NULL\n");
    } else {
        printf("FieldInfo::getName: %s\n", name);
        free(name);
    }

    int date = info->getDate(r);
    printf("FieldInfo::getDate: %d\n", date);

    void* copy = info->copy(r);
    if (!copy) {
        printf("FieldInfo::copy вернул NULL\n");
    } else {
        bool eq = info->equals(r, copy);
        printf("FieldInfo::equals(r, copy): %s\n", eq ? "true" : "false");
        info->destroy(copy);
    }

    info->destroy(r);
}

void test_fieldinfo(void) {
    printf("\n=== 3.3 test_fieldinfo (общий запуск) ===\n");
    test_fieldinfo_person();
    test_fieldinfo_robot();
}