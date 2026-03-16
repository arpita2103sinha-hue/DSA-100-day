#include <stdio.h>

#define MAX 100

int dq[MAX];
int front = -1, rear = -1;
int count = 0;

int empty() {
    return count == 0;
}

int size() {
    return count;
}

void push_front(int val) {
    if (count == MAX) return;

    if (empty()) {
        front = rear = 0;
    } else {
        front = (front - 1 + MAX) % MAX;
    }

    dq[front] = val;
    count++;
}

void push_back(int val) {
    if (count == MAX) return;

    if (empty()) {
        front = rear = 0;
    } else {
        rear = (rear + 1) % MAX;
    }

    dq[rear] = val;
    count++;
}

void pop_front() {
    if (empty()) return;

    if (front == rear) {
        front = rear = -1;
    } else {
        front = (front + 1) % MAX;
    }

    count--;
}

void pop_back() {
    if (empty()) return;

    if (front == rear) {
        front = rear = -1;
    } else {
        rear = (rear - 1 + MAX) % MAX;
    }

    count--;
}

int get_front() {
    if (empty()) return -1;
    return dq[front];
}

int get_back() {
    if (empty()) return -1;
    return dq[rear];
}

void display() {
    if (empty()) return;

    int i = front;
    for (int c = 0; c < count; c++) {
        printf("%d ", dq[i]);
        i = (i + 1) % MAX;
    }
}

int main() {

    push_back(10);
    push_back(20);
    push_front(5);
    push_back(30);

    printf("Front: %d\n", get_front());
    printf("Back: %d\n", get_back());

    pop_front();
    pop_back();

    printf("Deque elements: ");
    display();

    printf("\nSize: %d\n", size());

    return 0;
}
