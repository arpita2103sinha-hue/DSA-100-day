#include <stdio.h>

int main()
{
    int n, k, i;

    // Input size
    scanf("%d", &n);

    int arr[n], result[n];

    // Input array elements
    for(i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    // Input k
    scanf("%d", &k);

    // If k is greater than n
    k = k % n;

    // Rotate array
    for(i = 0; i < n; i++)
    {
        result[(i + k) % n] = arr[i];
    }

    // Print rotated array
    for(i = 0; i < n; i++)
    {
        printf("%d ", result[i]);
    }

    return 0;
}

