
#include "students.h"
#include <stdio.h>
#include <string.h>

int imya(FILE *file, const char *name) {
    Student student;
    int found = 0;
    rewind(file);
    while (fread(&student, sizeof(Student), 1, file)) {
        float avg = (student.grades[0] + student.grades[1] + student.grades[2]) / 3.0;
        if (strcmp(student.name, name) == 0) {
            printf("найден студент: %s, Группа: %s, средний балл: %.2f\n",
                   student.name, student.group, avg);
            found = 1;
            break;
        }
    }
    return found;
}

int group(FILE *file, const char *group) {
    Student student;
    int found = 0;
    rewind(file);
    while (fread(&student, sizeof(Student), 1, file)) {
        float avg = (student.grades[0] + student.grades[1] + student.grades[2]) / 3.0;
        if (strcmp(student.group, group) == 0) {
            printf("найден студент: %s, Группа: %s, средний балл: %.2f\n",
                   student.name, student.group, avg);
            found = 1;
            break;
        }
    }
    return found;
}

int stataavg(FILE *file, float average) {
    Student student;
    int found = 0;
    rewind(file);
    while (fread(&student, sizeof(Student), 1, file)) {
        float avg = (student.grades[0] + student.grades[1] + student.grades[2]) / 3.0;
        if (avg == average) {
            printf("найден студент: %s, Группа: %s, средний балл: %.2f\n",
                   student.name, student.group, avg);
            found = 1;
            break;
        }
    }
    return found;
}

