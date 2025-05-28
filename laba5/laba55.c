#include <stdio.h>
#include <string.h>

#define MAX_NAME_LEN 50
#define MAX_GROUP_LEN 10

typedef struct {
    char name[MAX_NAME_LEN];   
    char group[MAX_GROUP_LEN];  
    int grades[3];              
} Student;

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

    fclose(file);
    return 0;
}