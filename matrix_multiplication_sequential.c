#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void show_matrix(int size, long **matrix, char name[]){
    printf("Showing %s \n", name);
    for (int i = 0; i < size; i++){
        for (int j = 0; j < size; j++){
            printf("%ld\t", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void fill_matrix(int size, long **matrix){
    for (int row = 0; row < size; row++){
        for (int col = 0; col < size; col++){
            matrix[col][row] = rand() % 100;
        }
    }
}

void assign_memory_to_matrix(int size, long **matrix){
    for (int index = 0; index < size; ++index){
        matrix[index] = (long *)malloc(size * sizeof(long));
    }
}

int main(int argc, char *argv[]){
    int size;
    sscanf(argv[1], "%d", &size);
    long **result, **matrix_a, **matrix_b;
    time_t t;
    srand((unsigned)time(&t));

    matrix_a = (long**)malloc(size*sizeof(long*));
    assign_memory_to_matrix(size,matrix_a);
    fill_matrix(size,matrix_a);

    matrix_b = (long**)malloc(size*sizeof(long*));
    assign_memory_to_matrix(size,matrix_b);
    fill_matrix(size,matrix_b);

    result = (long**)malloc(size*sizeof(long*));
    assign_memory_to_matrix(size,result);
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    for (int a = 0; a < size; a++) {
        for (int i = 0; i < size; i++) {
            long suma = 0;
            for (int j = 0; j < size; j++) {
                suma += matrix_a[i][j] * matrix_b[j][a];
            }
            result[i][a] = suma;
        }
    }
    end = clock();
    cpu_time_used = end -start;
    printf("%lf\n",cpu_time_used);
}