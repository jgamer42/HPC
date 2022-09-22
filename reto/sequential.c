#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
void jacobi(long long int nsweeps, long long int n, double *u, double *f)
{
    int i, sweep;
    double h = 1.0 / n;
    double h2 = h * h;
    double *utmp = (double *)malloc((n + 1) * sizeof(double));

    /* Fill boundary conditions into utmp */
    utmp[0] = u[0];
    utmp[n] = u[n];

    for (sweep = 0; sweep < nsweeps; sweep++)
    {

        /* Old data in u; new data in utmp */
        for (i = 1; i < n; ++i)
            utmp[i] = (u[i - 1] + u[i + 1] + h2 * f[i]) / 2;

        /* Old data in utmp; new data in u */
        for (i = 1; i < n; ++i)
            u[i] = (utmp[i - 1] + utmp[i + 1] + h2 * f[i]) / 2;
    }

    free(utmp);
}

int main(int argc, char **argv)
{
    int i;
    long long int n, nsteps;
    double *u;
    double *f;
    double h;
    sscanf(argv[1], "%lld", &n);
    sscanf(argv[2], "%lld", &nsteps);
    clock_t start_t, end_t;
    double total_t;
    h = 1.0 / n;

    u = (double *)malloc((n + 1) * sizeof(double));
    f = (double *)malloc((n + 1) * sizeof(double));
    memset(u, 0, (n + 1) * sizeof(double));
    for (i = 0; i <= n; ++i)
        f[i] = i * h;

    /* Run the solver */
    start_t = clock();
    jacobi(nsteps, n, u, f);
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    printf("%f\n", total_t);
    free(f);
    free(u);
    return 0;
}