#include <stdio.h>
#include <omp.h>

int main() {
    int n = 5;
    int vec1[] = {1, 3, -5, 2, -1};
    int vec2[] = {-2, 4, 1, -3, 0};

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (vec1[i] > vec1[j]) {
                int temp = vec1[i];
                vec1[i] = vec1[j];
                vec1[j] = temp;
            }
        }
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (vec2[i] < vec2[j]) {
                int temp = vec2[i];
                vec2[i] = vec2[j];
                vec2[j] = temp;
            }
        }
    }

    int result = 0;
    double start = omp_get_wtime();

    #pragma omp parallel for reduction(+:result)
    for (int i = 0; i < n; i++) {
        result += vec1[i] * vec2[i];
    }

    double end = omp_get_wtime();

    printf("Minimum Scalar Product = %d\n", result);
    printf("Time taken: %f seconds\n", end - start);

    return 0;
}
