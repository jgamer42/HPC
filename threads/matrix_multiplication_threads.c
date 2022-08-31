#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

long **result, **matrix_a, **matrix_b;
struct thread_data
{
    int start_col;
    int end_col;
    int start_row;
    int end_row;
    int thread_id;
};

void *multiply_matrix(void *threadid)
{
    struct thread_data *data;
    int start_row,start_col,end_col,end_row,id;
    data = (struct thread_data *)threadid;
    start_row = data->start_row;
    start_col = data->start_col;
    end_row = data->end_row;
    end_col = data->end_col;
    id = data->thread_id;
    for (int a = 0; a < end_col; a++) {
        for (int i = start_row; i < end_row; i++) {
            long suma = 0;
            for (int j = 0; j < end_col; j++) {
                suma += matrix_a[i][j] * matrix_b[j][a];
            }
            result[i][a] = suma;
        }
    }
    pthread_exit(NULL);
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


void main(int argc, char *argv[])
{
    int rc,size,n_threads,actual_block = 0;
    n_threads = 2;
    sscanf(argv[1], "%d", &size);
    pthread_t threads[n_threads];
    void *status;
    int charge_by_thread = size/n_threads;
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
    for (int t = 0; t < n_threads; t++)
    {
        struct thread_data data;
        data.start_col = 0;
        data.end_col = size;
        data.start_row = actual_block;
        if((actual_block + charge_by_thread) >= size){
            data.end_row = size;
        }else{
            data.end_row = actual_block + charge_by_thread;
        }
        actual_block = actual_block + charge_by_thread;
        printf("creando el hilo %d con inicio en la fila %d hasta %d \n",t, data.start_row,data.end_row);
        rc = pthread_create(&threads[t], NULL, multiply_matrix, (void *)&data);
        if (rc)
        {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }
    for(int t=0; t<n_threads; t++) {
       rc = pthread_join(threads[t], &status);
       if (rc) {
          printf("ERROR; return code from pthread_join() is %d\n", rc);
          exit(-1);
          }
    }
    end = clock();
    cpu_time_used = end -start;
    printf("%lf\n",cpu_time_used);
    pthread_exit(NULL);
}