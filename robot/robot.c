#include "../robot/robot.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


Robot* robotCreate(const char* name, int prodYear) {
    Robot* robot = malloc(sizeof(Robot));
    if (!robot) return NULL;

    robot->Name = name ? strdup(name) : NULL;
    robot->prodDate = prodYear;

    if (name && !robot->Name) {
        robotDestroy(robot);
        return NULL;
    }

    return robot;
}


void robotDestroy(Robot* robot) {
    if (!robot) return;

    free(robot->Name);
    free(robot);
}


char* robotGetName(const Robot* robot) {
    if (!robot || !robot->Name) return NULL;

    size_t len = strlen(robot->Name) + 1;
    char* nameCopy = malloc(len);
    if (!nameCopy) return NULL;

    strcpy(nameCopy, robot->Name);
    return nameCopy;
}


Robot* robotCopy(const Robot* src) {
    if (!src) return NULL;

    Robot* dst = malloc(sizeof(Robot));
    if (!dst) return NULL;

    dst->prodDate = src->prodDate;
    dst->Name = src->Name ? strdup(src->Name) : NULL;

    if (src->Name && !dst->Name) {
        robotDestroy(dst);
        return NULL;
    }

    return dst;
}


bool robotEquals(const Robot* a, const Robot* b) {
    if (!a || !b) return false;
    if (!a->Name && !b->Name) return true;
    if (!a->Name || !b->Name) return false;
    return strcmp(a->Name, b->Name) == 0;
}


int robotGetDate(const Robot* r) {
    if (!r) return 0;
    return r->prodDate;
}

void robotPrint(const Robot* r) {
    if (!r) {
        printf("[NULL ROBOT]\n");
        return;
    }
    char* name = robotGetName(r);
    if (name) {
        printf("Robot: %s (г. %d)\n", name, robotGetDate(r));
        free(name);
    } else {
        printf("Robot: [unknown] (г. %d)\n", robotGetDate(r));
    }
}
