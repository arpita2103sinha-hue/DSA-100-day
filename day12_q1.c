#include <stdio.h>

int main() {
    int m, n;
    scanf("%d %d", &m, &n);

    int matrix[100][100];

    // If not square, directly not symmetric
    if (m != n) {
        printf("Not a Symmetric Matrix");
        return 0;
    }

    // Input matrix
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    // Check symmetry
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            if(matrix[i][j] != matrix[j][i]) {
                printf("Not a Symmetric Matrix");
                return 0;
            }
        }
    }

    printf("Symmetric Matrix");

    return 0;
}

