#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
double *u, *f, *utmp;

struct thread_info
{
    int from, to;
    double h2;
};

void *thread_subroutine(void *threadarg)
{
    struct thread_info *thread_info;
    int from, to, i;
    double h2;

    thread_info = (struct thread_info *)threadarg;
    h2 = thread_info->h2;
    from = thread_info->from;
    to = thread_info->to;

    /* Old data in u; new data in utmp */
    for (i = from; i < to; ++i)
        utmp[i] = (u[i - 1] + u[i + 1] + h2 * f[i]) / 2;

    /* Old data in utmp; new data in u */
    for (i = from; i < to; ++i)
        u[i] = (utmp[i - 1] + utmp[i + 1] + h2 * f[i]) / 2;

    pthread_exit(NULL);
}

void jacobi(long long int nsweeps, long long int size, int threads_ammount)
{
    int i, sweep, thread_idx;
    double h = 1.0 / size;
    double h2 = h * h;

    struct thread_info threads_info[threads_ammount];
    pthread_t threads[threads_ammount];

    utmp[0] = u[0];
    utmp[size] = u[size];

    for (sweep = 0; sweep < nsweeps; sweep += 2)
    {
        for (thread_idx = 0; thread_idx < threads_ammount; thread_idx++)
        {

            threads_info[thread_idx].h2 = h2;
            threads_info[thread_idx].from = thread_idx * (size - 1) / threads_ammount;
            threads_info[thread_idx].to =
                (thread_idx + 1) * (size - 1) / threads_ammount;

            if (thread_idx == 0)
            {
                threads_info[thread_idx].from = 1;
            }
            if (pthread_create(&threads[thread_idx], NULL, thread_subroutine,
                               (void *)&threads_info[thread_idx]))
            {
                printf("There was an error creating a thread\n");
                exit(-1);
            }
        }

        for (thread_idx = 0; thread_idx < threads_ammount; thread_idx++)
        {
            if (pthread_join(threads[thread_idx], NULL))
            {
                printf("There was an error joining a thread\n");
                exit(-1);
            }
        }
    }
}

void write_solution(int n, double *u, const char *fname)
{
    int i;
    double h = 1.0 / n;
    FILE *fp = fopen(fname, "w+");
    for (i = 0; i <= n; ++i)
        fprintf(fp, "%g %g\n", i * h, u[i]);
    fclose(fp);
}

int main(int argc, char **argv)
{
    long long int n, nsteps;
    int i, threads_ammount;
    double h;
    char *fname;
    clock_t start_t, end_t;
    double total_t;
    h = 1.0 / n;
    sscanf(argv[1], "%lld", &n);
    sscanf(argv[2], "%lld", &nsteps);
    sscanf(argv[3], "%d", &threads_ammount);
    /* Allocate and initialize arrays */
    u = (double *)malloc((n + 1) * sizeof(double));
    f = (double *)malloc((n + 1) * sizeof(double));
    utmp = (double *)malloc((n + 1) * sizeof(double));

    memset(u, 0, (n + 1) * sizeof(double));

    for (i = 0; i <= n; ++i)
        f[i] = i * h;

    start_t = clock();
    jacobi(nsteps, n, threads_ammount);
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("%f\n", total_t);
    free(f);
    free(u);
    free(utmp);
    return 0;
}
