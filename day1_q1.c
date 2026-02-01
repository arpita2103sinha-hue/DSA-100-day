#include <stdio.h>

int main() {
    int n, pos, x;
    int arr[100];   // assuming max size is 100

    // Read number of elements
    scanf("%d", &n);

    // Read array elements
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Read position (1-based)
    scanf("%d", &pos);

    // Read element to insert
    scanf("%d", &x);

    // Shift elements to the right
    for (int i = n; i >= pos; i--) {
        arr[i] = arr[i - 1];
    }

    // Insert element at correct position
    arr[pos - 1] = x;

    // Print updated array
    for (int i = 0; i <= n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}

