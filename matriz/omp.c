#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
long **result, **matrix_a, **matrix_b;
int global_size;
int num_of_threads;
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

void multi(int size, long **matrix_a, long **matrix_b, long **result){
    if (!size){
        size = global_size;
    }
    int a,j,i;
    int id = omp_get_thread_num();
    int rows_per_thr = size / num_of_threads;
    int start_index = id * rows_per_thr;
    int final_index = (id + 1) * rows_per_thr;
    if ((id == num_of_threads - 1) && (size % 2 != 0)){
        final_index++;
    }
    #pragma omp parallel for private(i, j, a) shared(matrix_a, matrix_b, result)
    for (int a = start_index; a < final_index; a++)
    {
        for (int i = 0; i < size; i++)
        {
            long suma = 0;
            for (int j = 0; j < size; j++)
            {
                suma += matrix_a[i][j] * matrix_b[j][a];
            }
            result[i][a] = suma;
        }
    }
}

int main(int argc, char *argv[]){

    sscanf(argv[1], "%d", &global_size);
    sscanf(argv[2], "%d", &num_of_threads);
    time_t t;
    srand((unsigned)time(&t));

    matrix_a = (long**)malloc(global_size*sizeof(long*));
    assign_memory_to_matrix(global_size,matrix_a);
    fill_matrix(global_size,matrix_a);

    matrix_b = (long**)malloc(global_size*sizeof(long*));
    assign_memory_to_matrix(global_size,matrix_b);
    fill_matrix(global_size,matrix_b);

    result = (long**)malloc(global_size*sizeof(long*));
    assign_memory_to_matrix(global_size, result);
    clock_t start, end;
    double cpu_time_used;
    start = clock();
    multi(global_size,matrix_a,matrix_b,result);
    end = clock();
    cpu_time_used = (end - start) / CLOCKS_PER_SEC;
    printf("%lf\n", cpu_time_used);
}