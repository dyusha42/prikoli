#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int** A;
int** B;
int** C;
int N;
int thread_count;

void allocate_matrices() {
    A = malloc(N * sizeof(int*));
    B = malloc(N * sizeof(int*));
    C = malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++) {
        A[i] = malloc(N * sizeof(int));
        B[i] = malloc(N * sizeof(int));
        C[i] = malloc(N * sizeof(int));
    }
}

void fill_matrices() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            A[i][j] = 1;
            B[i][j] = 1;
            C[i][j] = 0;
        }
}

void print_matrix(int** M) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%d ", M[i][j]);
        printf("\n");
    }
}

void* multiply(void* arg) {
    int thread_id = *(int*)arg;
    int rows_per_thread = N / thread_count;
    int start = thread_id * rows_per_thread;
    int end = (thread_id == thread_count - 1) ? N : start + rows_per_thread;

    for (int i = start; i < end; i++)
        for (int j = 0; j < N; j++)
            for (int k = 0; k < N; k++)
                C[i][j] += A[i][k] * B[k][j];

    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc < 3) return 1;

    N = atoi(argv[1]);
    thread_count = atoi(argv[2]);

    allocate_matrices();
    fill_matrices();

    pthread_t threads[thread_count];
    int thread_ids[thread_count];

    clock_t start = clock();

    for (int i = 0; i < thread_count; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, multiply, &thread_ids[i]);
    }

    for (int i = 0; i < thread_count; i++)
        pthread_join(threads[i], NULL);

    clock_t end = clock();
    double elapsed = (double)(end - start) / CLOCKS_PER_SEC * 1000;

    if (N <= 5) {
        printf("Matrix A:\n");
        print_matrix(A);
        printf("Matrix B:\n");
        print_matrix(B);
        printf("Matrix C:\n");
        print_matrix(C);
    }

    printf("Время выполнения: %.2f мс\n", elapsed);

    FILE* f = fopen("results.csv", "a");
    fprintf(f, "%d,%d,%.2f\n", N, thread_count, elapsed);
    fclose(f);

    for (int i = 0; i < N; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);

    return 0;
}