// поиск

#include <stdio.h>
#include <string.h>

#define MAX_NAME_LEN 50
#define MAX_GROUP_LEN 10

typedef struct {
    char name[MAX_NAME_LEN];    
    char group[MAX_GROUP_LEN];  
    int grades[3];            
} Student;

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

int main() {
    FILE *file;
    file = fopen("students.dat", "rb");
    if (file == NULL) {
        printf("ошибка при открытии файла для чтения.\n");
        return 1;
    }

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