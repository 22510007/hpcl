#include <stdio.h>
#include <omp.h>

int main() {
    int n = 10;
    float scalar = 2.5;
    float vec[10], result[10];

    for (int i = 0; i < n; i++) {
        vec[i] = i * 1.0;
    }

    printf("Original Vector: ");
    for (int i = 0; i < n; i++) {
        printf("%.1f ", vec[i]);
    }
    printf("\nScalar to add: %.1f\n", scalar);

    
    double start = omp_get_wtime();

    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        result[i] = vec[i] + scalar;
    }

    double end = omp_get_wtime();

    printf("Result Vector: ");
    for (int i = 0; i < n; i++) {
        printf("%.1f ", result[i]);
    }
    printf("\nTime taken: %.6f seconds\n", end - start);

    return 0;
}
