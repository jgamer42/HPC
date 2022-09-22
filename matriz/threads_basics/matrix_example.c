#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 2

struct thread_data
{
    int start_col;
    int end_col;
    int start_row;
    int end_row;
    int thread_id;
};

void *show_matrix(void *threadid)
{
    struct thread_data *data;
    int start_row,start_col,end_col,end_row,id;
    int matrix[4][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}};
    data = (struct thread_data *)threadid;
    start_row = data->start_row;
    start_col = data->start_col;
    end_row = data->end_row;
    end_col = data->end_col;
    id = data->thread_id;
    printf("soy el hilo %d\n",id);
    for (int i = start_row; i < end_row; i++)
    {
        for (int j = start_col; j < end_col; j++)
        {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    pthread_exit(NULL);
}
void main()
{
    pthread_t threads[NUM_THREADS];
    
    int rc;
    struct thread_data t1,t2;
    t1.start_col = 0;
    t1.end_col = 4;
    t2.start_col = 0;
    t2.end_col = 4;

    t1.start_row = 0;
    t1.end_row = 2;
    t2.start_row = 2;
    t2.end_row = 4;

    t1.thread_id = 1;
    t2.thread_id = 2;
    struct thread_data data[2] = {t1,t2};
    for (int t = 0; t < NUM_THREADS; t++)
    {
        rc = pthread_create(&threads[t], NULL, show_matrix, (void *)&data[t]);
        if (rc)
        {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    /* Last thing that main() should do */
    pthread_exit(NULL);
}