#ifndef ROBOT_H
#define ROBOT_H

#include <stdbool.h>


typedef struct {
    char* Name;
    int prodDate;
} Robot;


Robot* robotCreate(const char* name, int prodYear);
void robotDestroy(Robot* robot);
void robotPrint(const Robot* robot);
char* robotGetName(const Robot* robot);
bool robotEquals(const Robot* a, const Robot* b);
int robotGetDate(const Robot* r);

Robot* robotCopy(const Robot* src);

#endif
