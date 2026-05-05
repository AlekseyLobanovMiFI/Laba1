#ifndef PERSON_H
#define PERSON_H

#include <stdbool.h>
#include <time.h>

typedef struct {
    int series;
    int numbers;
} PersonID;

typedef struct {
    PersonID id;
    char* firstName;
    char* middleName;
    char* lastName;
    int birthYear;
} Person;

Person* personCreate(const char* first, 
                     const char* middle, 
                     const char* last, 
                     int series, 
                     int number, 
                     int birthYear);

void personDestroy(Person* person);

void personPrint(const Person* person);
char* personGetFullName(const Person* person);
bool personEquals(const Person* a, const Person* b);

Person* personCopy(const Person* src);
int personGetDate(const Person* person);

bool personHasSeries(const Person* p, int series);
bool personIsYoungerThan(const Person* p, int age, int currentYear);
bool personNameStartsWith(const Person* p, char letter);

#endif
