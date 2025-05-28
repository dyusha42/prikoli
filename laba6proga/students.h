
#ifndef STUDENTS_H
#define STUDENTS_H

#include <stdio.h>

#define MAX_NAME_LEN 50
#define MAX_GROUP_LEN 10

typedef struct {
    char name[MAX_NAME_LEN];
    char group[MAX_GROUP_LEN];
    int grades[3];
} Student;

void writeToFile(FILE *file, Student *students, int n);
void printAllStudents(FILE *file);
int imya(FILE *file, const char *name);
int group(FILE *file, const char *group);
int stataavg(FILE *file, float average);

#endif