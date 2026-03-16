#include <stdio.h>

#define MAX 100

int main() {
    int q[MAX];
    int n, m;
    int front = 0, rear = -1;

    scanf("%d", &n);

    // Enqueue elements
    for(int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);
        rear = (rear + 1) % n;
        q[rear] = x;
    }

    scanf("%d", &m);

    // Perform dequeue operations
    for(int i = 0; i < m; i++) {
        front = (front + 1) % n;
    }

    // Print circular queue elements
    int count = n;
    int i = front;

    while(count--) {
        printf("%d ", q[i]);
        i = (i + 1) % n;
    }

    return 0;
}
