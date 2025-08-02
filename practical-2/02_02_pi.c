#include <stdio.h>
#include <omp.h>

int main() {
    long n = 1000000;
    double step = 1.0 / (double)n;
    double sum = 0.0, pi = 0.0;

    double start = omp_get_wtime();

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < n; i++) {
        double x = (i + 0.5) * step;
        sum += 4.0 / (1.0 + x * x);
    }

    pi = sum * step;

    double end = omp_get_wtime();

    printf("Calculated Pi = %.15f\n", pi);
    printf("Time taken = %f seconds\n", end - start);

    return 0;
}
