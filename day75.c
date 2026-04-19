#include <stdio.h>

#define MAX 1000

int maxLenZeroSum(int arr[], int n) {
    int prefixSum[MAX];
    int index[MAX];
    int size = 0;

    int sum = 0, maxLen = 0;

    for (int i = 0; i < n; i++) {
        sum += arr[i];

        // Case 1: sum becomes 0
        if (sum == 0) {
            maxLen = i + 1;
        }

        int found = -1;

        // Check if sum seen before
        for (int j = 0; j < size; j++) {
            if (prefixSum[j] == sum) {
                found = j;
                break;
            }
        }

        if (found != -1) {
            int len = i - index[found];
            if (len > maxLen) {
                maxLen = len;
            }
        } else {
            prefixSum[size] = sum;
            index[size] = i;
            size++;
        }
    }

    return maxLen;
}

int main() {
    int arr[] = {15, -2, 2, -8, 1, 7, 10, 23};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("%d\n", maxLenZeroSum(arr, n));
    return 0;
}
