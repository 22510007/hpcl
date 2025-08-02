#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main() {
    int sizes[] = {250, 500, 750, 1000, 2000};
    int threads[] = {1, 2, 4, 8};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    int num_threads = sizeof(threads) / sizeof(threads[0]);

    for (int s = 0; s < num_sizes; s++) {
        int n = sizes[s];

        int **A = malloc(n * sizeof(int *));
        int **B = malloc(n * sizeof(int *));
        int **C = malloc(n * sizeof(int *));
        for (int i = 0; i < n; i++) {
            A[i] = malloc(n * sizeof(int));
            B[i] = malloc(n * sizeof(int));
            C[i] = malloc(n * sizeof(int));
        }

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                A[i][j] = i + j;
                B[i][j] = i - j;
            }

        double base_time = 0.0;

        for (int t = 0; t < num_threads; t++) {
            omp_set_num_threads(threads[t]);

            double start = omp_get_wtime();

            #pragma omp parallel for collapse(2)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < n; j++)
                    C[i][j] = A[i][j] + B[i][j];

            double end = omp_get_wtime();
            double time_taken = end - start;

            if (threads[t] == 1) base_time = time_taken;

            double speedup = base_time / time_taken;

            printf("Size: %d x %d, Threads: %d, Time: %f s, Speedup: %.2f\n",
                   n, n, threads[t], time_taken, speedup);
        }
        printf("--------------------------------------------------------------\n");
        for (int i = 0; i < n; i++) {
            free(A[i]);
            free(B[i]);
            free(C[i]);
        }
        free(A);
        free(B);
        free(C);
    }

    return 0;
}
