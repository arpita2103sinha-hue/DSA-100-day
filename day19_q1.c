#include <stdio.h>
#include <stdlib.h>

// Function to compare for qsort
int compare(const void *a, const void *b)
{
    return (*(int*)a - *(int*)b);
}

int main()
{
    int n, i;
    scanf("%d", &n);

    int arr[n];

    // Input array
    for(i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    // Sort the array
    qsort(arr, n, sizeof(int), compare);

    int left = 0;
    int right = n - 1;

    int min_sum = arr[left] + arr[right];
    int min_left = left;
    int min_right = right;

    // Two pointer technique
    while(left < right)
    {
        int sum = arr[left] + arr[right];

        if(abs(sum) < abs(min_sum))
        {
            min_sum = sum;
            min_left = left;
            min_right = right;
        }

        if(sum < 0)
            left++;
        else
            right--;
    }

    // Print result
    printf("%d %d", arr[min_left], arr[min_right]);

    return 0;
}

