#include "../fieldinfo/fieldinfo.h"
#include "../person/person.h"
#include "../robot/robot.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

/////////////////////////////////////////////////////////////////////////////////////////////

static FieldInfo* STUDENT_FIELD_INFO = NULL;
static FieldInfo* TEACHER_FIELD_INFO = NULL;
static FieldInfo* ROBOT_FIELD_INFO = NULL;

static void field_personDestroy(void* ptr);
static char* field_personGetName(const void* ptr);
static int field_personGetDate(const void* ptr);
static int field_personGetIdSeries(const void* ptr);
static int field_personGetIdNumbers(const void* ptr);
static void* field_personCopy(const void* ptr);
static bool field_personEquals(const void* a, const void* b);

const FieldInfo* getStudentFieldInfo(void) {
    if (STUDENT_FIELD_INFO == NULL) {
        STUDENT_FIELD_INFO = malloc(sizeof(FieldInfo));
        if (!STUDENT_FIELD_INFO) return NULL;

        STUDENT_FIELD_INFO->size = sizeof(Person);
        STUDENT_FIELD_INFO->typeName = "Student";
        STUDENT_FIELD_INFO->destroy = field_personDestroy;
        STUDENT_FIELD_INFO->getName = field_personGetName;
        STUDENT_FIELD_INFO->getDate = field_personGetDate;
        STUDENT_FIELD_INFO->getIdSeries = field_personGetIdSeries;
        STUDENT_FIELD_INFO->getIdNumbers = field_personGetIdNumbers;
        STUDENT_FIELD_INFO->copy = field_personCopy;
        STUDENT_FIELD_INFO->equals = field_personEquals;
    }
    return STUDENT_FIELD_INFO;
}

const FieldInfo* getTeacherFieldInfo(void) {
    if (TEACHER_FIELD_INFO == NULL) {
        TEACHER_FIELD_INFO = malloc(sizeof(FieldInfo));
        if (!TEACHER_FIELD_INFO) return NULL;

        TEACHER_FIELD_INFO->size = sizeof(Person);
        TEACHER_FIELD_INFO->typeName = "Teacher";
        TEACHER_FIELD_INFO->destroy = field_personDestroy;
        TEACHER_FIELD_INFO->getName = field_personGetName;
        TEACHER_FIELD_INFO->getDate = field_personGetDate;
        TEACHER_FIELD_INFO->getIdSeries = field_personGetIdSeries;
        TEACHER_FIELD_INFO->getIdNumbers = field_personGetIdNumbers;
        TEACHER_FIELD_INFO->copy = field_personCopy;
        TEACHER_FIELD_INFO->equals = field_personEquals;
    }
    return TEACHER_FIELD_INFO;
}

static void field_personDestroy(void* ptr) {
    Person* p = (Person*)ptr;
    free(p->firstName);
    free(p->middleName);
    free(p->lastName);
    // Note: do not free(p) as it's part of the array
}

static char* field_personGetName(const void* ptr) {
    return personGetFullName((const Person*)ptr);
}

static void* field_personCopy(const void* ptr) {
    return personCopy((const Person*)ptr);
}

static bool field_personEquals(const void* a, const void* b) {
    return personEquals((const Person*)a, (const Person*)b);
}

static int field_personGetIdSeries(const void* ptr) {
    const Person* p = (const Person*)ptr;
    return p->id.series;
}

static int field_personGetIdNumbers(const void* ptr) {
    const Person* p = (const Person*)ptr;
    return p->id.numbers;
}

static int field_personGetDate(const void* ptr) {
    return personGetDate((const Person*)ptr);
}

/////////////////////////////////////////////////////////////////////////////////////////////

static void field_robotDestroy(void* ptr);
static char* field_robotGetName(const void* ptr);
static int field_robotGetDate(const void* ptr);
static int field_robotGetIdSeries(const void* ptr);
static int field_robotGetIdNumbers(const void* ptr);
static void* field_robotCopy(const void* ptr);
static bool field_robotEquals(const void* a, const void* b);

const FieldInfo* getRobotFieldInfo(void) {
    if (ROBOT_FIELD_INFO == NULL) {
        ROBOT_FIELD_INFO = malloc(sizeof(FieldInfo));
        if (!ROBOT_FIELD_INFO) return NULL;

        ROBOT_FIELD_INFO->size = sizeof(Robot);
        ROBOT_FIELD_INFO->typeName = "Robot";
        ROBOT_FIELD_INFO->destroy = field_robotDestroy;
        ROBOT_FIELD_INFO->getName = field_robotGetName;
        ROBOT_FIELD_INFO->getDate = field_robotGetDate;
        ROBOT_FIELD_INFO->getIdSeries = field_robotGetIdSeries;
        ROBOT_FIELD_INFO->getIdNumbers = field_robotGetIdNumbers;
        ROBOT_FIELD_INFO->copy = field_robotCopy;
        ROBOT_FIELD_INFO->equals = field_robotEquals;
    }
    return ROBOT_FIELD_INFO;
}

static void field_robotDestroy(void* ptr) {
    Robot* r = (Robot*)ptr;
    free(r->Name);
    // Note: do not free(r) as it's part of the array
}

static char* field_robotGetName(const void* ptr) {
    const Robot* r = (const Robot*)ptr;
    return robotGetName(r);
}

static int field_robotGetDate(const void* ptr) {
    const Robot* r = (const Robot*)ptr;
    return robotGetDate(r);
}

static int field_robotGetIdSeries(const void* ptr) {
    return 0; // Robots don't have series
}

static int field_robotGetIdNumbers(const void* ptr) {
    return 0; // Robots don't have numbers
}

static void* field_robotCopy(const void* ptr) {
    const Robot* r = (const Robot*)ptr;
    return robotCopy(r);
}

static bool field_robotEquals(const void* a, const void* b) {
    const Robot* ra = (const Robot*)a;
    const Robot* rb = (const Robot*)b;
    return robotEquals(ra, rb);
}