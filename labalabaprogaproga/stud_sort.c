#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N1 10000

struct Student {
    char name[64];
    int math;
    int physics;
    int informatics;
    int total;
};

struct Student addStudent(const char *name, int math, int phy, int inf) {
    struct Student newStudent;
    strncpy(newStudent.name, name, 64);
    newStudent.math = math;
    newStudent.physics = phy;
    newStudent.informatics = inf;
    newStudent.total = math + phy + inf;
    return newStudent;
}

void printStudentInfo(struct Student s) {
    printf("Имя: %s, Матем: %d, Физ: %d, Инф: %d, Общий балл: %d\n",
           s.name, s.math, s.physics, s.informatics, s.total);
}

// Selection Sort
void selectionSort(struct Student bruh[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int maxIdx = i;
        for (int j = i + 1; j < size; j++) {
            if (bruh[j].total > bruh[maxIdx].total) {
                maxIdx = j;
            }
        }
        struct Student temp = bruh[i];
        bruh[i] = bruh[maxIdx];
        bruh[maxIdx] = temp;
    }
}

// Radix Sort
int getMaxTotal(struct Student bruh[], int size) {
    int max = bruh[0].total;
    for (int i = 1; i < size; i++) {
        if (bruh[i].total > max) {
            max = bruh[i].total;
        }
    }
    return max;
}

void countingSort(struct Student bruh[], int size, int exp) {
    struct Student output[size];
    int count[10] = {0};

    for (int i = 0; i < size; i++) {
        count[(bruh[i].total / exp) % 10]++;
    }


    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
    }

    for (int i = size - 1; i >= 0; i--) {
        output[count[(bruh[i].total / exp) % 10] - 1] = bruh[i];
        count[(bruh[i].total / exp) % 10]--;
    }

    for (int i = 0; i < size; i++) {
        bruh[i] = output[i];
    }
}

void radixSort(struct Student bruh[], int size) {
    int max = getMaxTotal(bruh, size);

    for (int exp = 1; max / exp > 0; exp *= 10) {
        countingSort(bruh, size, exp);
    }
}

void measureSortingTime(int size, int sortType) {
    struct Student *students = malloc(size * sizeof(struct Student));
    srand(time(NULL));

    for (int i = 0; i < size; i++) {
        char name[64];
        snprintf(name, 64, "Студент_%d", i + 1);
        students[i] = addStudent(name, rand() % 101, rand() % 101, rand() % 101);
    }

    printf("Студенты до сортировки:\n");
    for (int i = 0; i < size; i++) {
        printStudentInfo(students[i]);
    }

    clock_t start = clock();
    if (sortType == 1) {
        selectionSort(students, size);
        printf("\nИспользована сортировка выбором.\n");
    } else if (sortType == 2) {
        radixSort(students, size);
        printf("\nИспользована поразрядная сортировка (Radix Sort).\n");
    } else {
        printf("\nНеверный выбор сортировки.\n");
        free(students);
        return;
    }
    clock_t end = clock();

    printf("\nСтуденты после сортировки:\n");
    for (int i = 0; i < size; i++) {
        printStudentInfo(students[i]);
    }

    printf("\nРазмер данных: %d, Время сортировки: %lf секунд\n", size, (double)(end - start) / CLOCKS_PER_SEC);
    free(students);
}

int main() {
    int choice;
    printf("Выберите алгоритм сортировки:\n");
    printf("1. Сортировка выбором (Selection Sort)\n");
    printf("2. Поразрядная сортировка (Radix Sort)\n");
    scanf("%d", &choice);

    if (choice != 1 && choice != 2) {
        printf("Неверный выбор. Завершение программы.\n");
        return 1;
    }

    printf("Измерение времени сортировки:\n");
    measureSortingTime(N1, choice);
    return 0;
}