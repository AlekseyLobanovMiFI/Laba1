#ifndef TEST_H
#define TEST_H

#include "../dynamicArray/dynamicArray.h"
#include "../fieldinfo/fieldinfo.h"
#include "../person/person.h"
#include "../robot/robot.h"

// === 1. Тесты для DynamicArray (общий контейнер) ===
void test_dynamic_array_basic(void);
void test_dynamic_array_person(void);
void test_dynamic_array_robot(void);
void test_dynamic_array(void);

// === 2. Тесты для Person и Robot ===
void test_person_basic(void);
void test_robot_basic(void);
void test_person_robot(void);

// === 3. Тесты для FieldInfo ===
void test_fieldinfo_person(void);
void test_fieldinfo_robot(void);
void test_fieldinfo(void);

void test_dynamic_array_mini(void);

#endif
