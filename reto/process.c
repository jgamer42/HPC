#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>

int lenth_n;
int nsteps;
int procesos_n;
double *u;
double *f;
double h;
int termino;

int jacobi(int id_proceso)
{
    int i, sweep;
    double h = 1.0 / lenth_n;
    double h2 = h * h;
    double *utmp = (double *)mmap(NULL, (lenth_n + 1) * sizeof(double),
                                  PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS,
                                  0, 0);
    ;
    int id = (long)id_proceso;
    int cargaxproceso = lenth_n / procesos_n;
    int inicio = cargaxproceso * id;
    int final = inicio + cargaxproceso;

    if (id + 1 == procesos_n)
    {
        final = lenth_n;
    }

    utmp[0] = u[0];
    utmp[lenth_n] = u[lenth_n];
    for (sweep = 0; sweep < nsteps; sweep += 2)
    {
        for (i = inicio + 1; i < final; ++i)
        {
            utmp[i] = (u[i + 1] + u[i - 1] + h2 * f[i]) / 2;
        }
        for (i = inicio + 1; i < final; ++i)
        {
            u[i] = (utmp[i + 1] + utmp[i - 1] + h2 * f[i]) / 2;
        }
    }
    munmap(utmp, (lenth_n + 1) * sizeof(double *));
    return 0;
}

int main(int argc, char **argv)
{
    clock_t start_t, end_t;
    sscanf(argv[1], "%d", &lenth_n);
    sscanf(argv[2], "%d", &nsteps);
    sscanf(argv[3], "%d", &procesos_n);
    double total_t;
    u = (double *)mmap(NULL, (lenth_n + 1) * sizeof(double),
                       PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS,
                       0, 0);
    f = (double *)mmap(NULL, (lenth_n + 1) * sizeof(double),
                       PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS,
                       0, 0);
    h = 1.0 / lenth_n;
    memset(u, 0, (lenth_n + 1) * sizeof(double));
    for (int i = 0; i <= lenth_n; ++i)
    {
        f[i] = i * h;
    }
    start_t = clock();
    for (int i = 0; i < procesos_n; i++)
    {
        int ProcessId = fork();
        if (ProcessId == 0)
        {
            exit(jacobi(i));
        }
        else if (ProcessId < 0)
        {
            printf("ERROR IN PROCESS TREE %d\n", i);
            exit(0);
        }
    }

    for (int i = 0; i < procesos_n; i++)
    {
        wait(&termino);
    }
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("%f\n", total_t);
    munmap(u, (lenth_n + 1) * sizeof(double *));
    munmap(f, (lenth_n + 1) * sizeof(double *));
    return 0;
}
