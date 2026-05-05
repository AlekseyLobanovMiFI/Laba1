#include "../person/person.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Person* personCreate(const char* first,
                     const char* middle,
                     const char* last,
                     int series,
                     int number,
                     int birthYear) {
    Person* person = malloc(sizeof(Person));
    if (!person) return NULL;

    person->id.series = series;
    person->id.numbers = number;
    person->firstName = first ? strdup(first) : NULL;
    person->middleName = middle ? strdup(middle) : NULL;
    person->lastName = last ? strdup(last) : NULL;
    person->birthYear = birthYear;

    if (!person->firstName || !person->lastName ||
        (middle && !person->middleName)) {
        personDestroy(person);
        return NULL;
    }

    return person;
}

void personDestroy(Person* person) {
    if (!person) return;

    free(person->firstName);
    free(person->middleName);
    free(person->lastName);
    free(person);
}

Person* personCopy(const Person* src) {
    if (!src) return NULL;

    Person* dst = malloc(sizeof(Person));
    if (!dst) return NULL;

    dst->id.series = src->id.series;
    dst->id.numbers = src->id.numbers;
    dst->birthYear = src->birthYear;

    dst->firstName = src->firstName ? strdup(src->firstName) : NULL;
    dst->middleName = src->middleName ? strdup(src->middleName) : NULL;
    dst->lastName = src->lastName ? strdup(src->lastName) : NULL;

    if (!dst->firstName || !dst->lastName ||
        (src->middleName && !dst->middleName)) {
        personDestroy(dst);
        return NULL;
    }

    return dst;
}

void personPrint(const Person* person) {
    if (!person) {
        printf("[NULL PERSON]\n");
        return;
    }

    char* fullName = personGetFullName(person);
    printf("  [%d-%d] %s (g. %d)\n",
           person->id.series,
           person->id.numbers,
           fullName ? fullName : "NULL",
           person->birthYear);
    free(fullName);
}

char* personGetFullName(const Person* person) {
    if (!person) return NULL;

    const char* first = person->firstName ? person->firstName : "";
    const char* middle = person->middleName ? person->middleName : "";
    const char* last = person->lastName ? person->lastName : "";

    size_t len = strlen(first) + strlen(middle) + strlen(last) + 3;
    char* fullName = malloc(len);
    if (!fullName) return NULL;

    snprintf(fullName, len, "%s %s %s", first, middle, last);
    return fullName;
}

int personGetDate(const Person* person) {
    if (!person) return 0;
    return person->birthYear;
}

bool personEquals(const Person* a, const Person* b) {
    if (!a || !b) return false;
    return a->id.series == b->id.series &&
           a->id.numbers == b->id.numbers;
}

bool personHasSeries(const Person* p, int series) {
    return p && p->id.series == series;
}

bool personIsYoungerThan(const Person* p, int age, int currentYear) {
    if (!p) return false;
    return (currentYear - p->birthYear) < age;
}

bool personNameStartsWith(const Person* p, char letter) {
    return p && p->firstName && p->firstName[0] == letter;
}
