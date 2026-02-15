#include <stdio.h>

int main() {
    int m, n;
    printf("Enter number of rows and columns: ");
    scanf("%d %d", &m, &n);

    int matrix[m][n];
    int i, j;
    int sum = 0;

    // Input matrix
    printf("Enter matrix elements:\n");
    for(i = 0; i < m; i++) {
        for(j = 0; j < n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }

    // Check if matrix is square
    if(m != n) {
        printf("Primary diagonal exists only for square matrix");
        return 0;
    }

    // Calculate primary diagonal sum
    for(i = 0; i < n; i++) {
        sum += matrix[i][i];
    }

    // Output result
    printf("%d", sum);

    return 0;
}

