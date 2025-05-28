#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
    struct node *prev;
};

typedef struct node node_t;

node_t *newNode(int data) {
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

node_t* addBack(node_t* head, int data) {
    node_t* new_node = newNode(data);
    if (!head) {
        return new_node;
    }
    node_t* cur = head;
    while (cur->next) {
        cur = cur->next;
    }
    cur->next = new_node;
    new_node->prev = cur;
    return head;
}

node_t* addStart(node_t* head, int data) {
    node_t* new_node = newNode(data);
    new_node->next = head;
    if (head) head->prev = new_node;
    return new_node;
}

void printList(node_t* head) {
    node_t* cur = head;
    while (cur) {
        printf("%d", cur->data);
        if (cur->next) {
            printf(" -> ");
        }
        cur = cur->next;
    }
    printf(" -> NULL\n");
}

void moveRight(node_t** ptr) {
    if (*ptr && (*ptr)->next) {
        *ptr = (*ptr)->next;
        printf("Перемещено вправо: %d\n", (*ptr)->data);
    } else {
        printf("Вы на последнем элементе спика: %d\n", (*ptr)->data);
    }
}

void moveLeft(node_t** ptr) {
    if (*ptr && (*ptr)->prev) {
        *ptr = (*ptr)->prev;
        printf("Перемещено влево: %d\n", (*ptr)->data);
    } else {
        printf("Вы в начале списка.\n");
    }
}

int main() {
    char ch;
    int data, i = 1;
    node_t* oddList = NULL;
    node_t* evenList = NULL;
    node_t* oddPtr = NULL;
    node_t* evenPtr = NULL;
    node_t* S = NULL;

    printf("Вводите элементы списка, чтобы прекратить введите 0\n");

    while (1) {
        printf("%d элемент списка: ", i);
        if (scanf("%d", &data) != 1) {
            printf("Ошибка ввода\n");
            break;
        }
        if (data == 0) break;

        if (i % 2 == 1) {
            oddList = addStart(oddList, data);
        } else {
            evenList = addStart(evenList, data);
        }
        i++;
    }

    S = oddList;

    if (oddList && evenList) {
        oddList->prev = evenList;
    }

    printf("\nНечётный список:\n");
    printList(oddList);

    printf("\nЧётный список:\n");
    printList(evenList);

    oddPtr = oddList;
    evenPtr = evenList;

    while (1) {
        printf("\nВведите команду (W/A/S/D или 2/4/6/8): ");
        scanf(" %c", &ch);

        if (ch == 'W' || ch == '8') {
            printf("Вы переместились в начало списка.\n");
            oddPtr = oddList; // начало списка
            printf("Текущее значение: %d\n", oddPtr->data);
        } else if (ch == 'S' || ch == '2') {
            printf("Вы переместились в начало чётного списка.\n");
            evenPtr = evenList; // начало чёт
            printf("Текущее значение: %d\n", evenPtr->data);
        } else if (ch == 'D' || ch == '6') {
            moveRight(&oddPtr); // вправо по нечёт
        } else if (ch == 'A' || ch == '4') {
            moveLeft(&oddPtr); // влево по нечёт
        } else {
            printf("Неверная команда. Попробуйте снова.\n");
        }
    }

    return 0;
}