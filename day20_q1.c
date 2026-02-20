#include <stdio.h>

int main() {
    int n, i, j;
    
    printf("Enter size of array: ");
    scanf("%d", &n);
    
    int arr[n];
    
    printf("Enter elements:\n");
    for(i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    
    int count = 0;
    
    // Check all possible subarrays
    for(i = 0; i < n; i++) {
        int sum = 0;
        for(j = i; j < n; j++) {
            sum += arr[j];
            
            if(sum == 0) {
                count++;
            }
        }
    }
    
    printf("Count of subarrays with sum zero: %d", count);
    
    return 0;
}
