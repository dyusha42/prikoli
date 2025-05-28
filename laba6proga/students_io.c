#include "students.h"
#include <stdio.h>

void writeToFile(FILE *file, Student *students, int n) {
    for (int i = 0; i < n; i++) {
        fwrite(&students[i], sizeof(Student), 1, file);
    }
}

void printAllStudents(FILE *file) {
    Student student;
    rewind(file);
    printf("\nинформация о всех студентах:\n");
    printf("имя студента | номер группы | средний балл\n");
    printf("--------------------------------------------\n");

    while (fread(&student, sizeof(Student), 1, file)) {
        float average = (student.grades[0] + student.grades[1] + student.grades[2]) / 3.0;
        printf("%-15s | %-13s | %.2f\n", student.name, student.group, average);
    }
}

