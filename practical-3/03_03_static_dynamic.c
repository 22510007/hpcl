#include <stdio.h>
#include <omp.h>

#define SIZE 200
#define SCALAR 5

int main() {
    int vector[SIZE];

    for (int i = 0; i < SIZE; i++)
        vector[i] = i;

    int chunks[] = {1, 5, 10, 20};

    for (int c = 0; c < 4; c++) {
        int chunk = chunks[c];

        double start_static = omp_get_wtime();
        #pragma omp parallel for schedule(static, chunk)
        for (int i = 0; i < SIZE; i++) {
            vector[i] = i + SCALAR;
        }
        double end_static = omp_get_wtime();
        printf("STATIC chunk=%d: Time = %f sec\n", chunk, end_static - start_static);

        double start_dynamic = omp_get_wtime();
        #pragma omp parallel for schedule(dynamic, chunk)
        for (int i = 0; i < SIZE; i++) {
            vector[i] = i + SCALAR;
        }
        double end_dynamic = omp_get_wtime();
        printf("DYNAMIC chunk=%d: Time = %f sec\n", chunk, end_dynamic - start_dynamic);
    }

    int A[SIZE], B[SIZE];
    for (int i = 0; i < SIZE; i++) {
        A[i] = i;
        B[i] = i * 2;
    }

    double start_nowait = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp for nowait
        for (int i = 0; i < SIZE; i++) A[i] += SCALAR;

        #pragma omp for
        for (int i = 0; i < SIZE; i++) B[i] += SCALAR;
    }
    double end_nowait = omp_get_wtime();
    printf("nowait: Time = %f sec\n", end_nowait - start_nowait);

    return 0;
}
