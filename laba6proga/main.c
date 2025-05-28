
#include <stdio.h>
#include "students.h"

int main() {
    FILE *file;
    int n;

    printf("введите количество студентов: ");
    scanf("%d", &n);

    Student students[n];

    for (int i = 0; i < n; i++) {
        printf("введите имя студента %d: ", i + 1);
        scanf("%s", students[i].name);
        printf("введите номер группы студента %d: ", i + 1);
        scanf("%s", students[i].group);
        printf("введите оценки за три предмета для студента %d: ", i + 1);
        for (int j = 0; j < 3; j++) {
            scanf("%d", &students[i].grades[j]);
        }
    }

    file = fopen("students.dat", "wb");
    if (file == NULL) {
        printf("ошибка при открытии файла для записи.\n");
        return 1;
    }

    writeToFile(file, students, n);
    fclose(file);

    printf("данные студентов успешно записаны в файл students.dat\n");

    file = fopen("students.dat", "rb");
    if (file == NULL) {
        printf("ошибка при открытии файла для чтения.\n");
        return 1;
    }

    printAllStudents(file);

    char searchimya[MAX_NAME_LEN];
    char searchgroup[MAX_GROUP_LEN];
    float searchavg;
    int choice;

    printf("что хотите искать? 1 - по имени, 2 - по номеру группы, 3 - по среднему баллу: ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("введите имя для поиска: ");
        scanf("%s", searchimya);
        if (!imya(file, searchimya)) {
            printf("студент с таким именем не найден.\n");
        }
    } else if (choice == 2) {
        printf("введите номер группы для поиска: ");
        scanf("%s", searchgroup);
        if (!group(file, searchgroup)) {
            printf("студент с таким номером группы не найден.\n");
        }
    } else if (choice == 3) {
        printf("введите средний балл для поиска: ");
        scanf("%f", &searchavg);
        if (!stataavg(file, searchavg)) {
            printf("студент с таким средним баллом не найден.\n");
        }
    } else {
        printf("неверный выбор.\n");
    }

    fclose(file);
    return 0;
}
