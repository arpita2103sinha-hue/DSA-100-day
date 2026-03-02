#include <stdio.h>
#include <stdlib.h>

// Structure definition
struct Node {
    int data;
    struct Node* next;
};

int main() {
    int n, k, i, value;
    struct Node *head = NULL, *temp = NULL, *newNode = NULL;
    
    scanf("%d", &n);
    
    if(n <= 0)
        return 0;

    // Create first node
    scanf("%d", &value);
    head = (struct Node*)malloc(sizeof(struct Node));
    head->data = value;
    head->next = NULL;
    temp = head;

    // Create remaining nodes
    for(i = 1; i < n; i++) {
        scanf("%d", &value);
        newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = value;
        newNode->next = NULL;
        temp->next = newNode;
        temp = newNode;
    }

    scanf("%d", &k);

    // If k is greater than n
    k = k % n;

    if(k == 0) {
        temp = head;
        while(temp != NULL) {
            printf("%d ", temp->data);
            temp = temp->next;
        }
        return 0;
    }

    // Step 1: Make it circular
    temp->next = head;

    // Step 2: Move to (n - k)th node
    int steps = n - k;
    struct Node* newTail = head;

    for(i = 1; i < steps; i++) {
        newTail = newTail->next;
    }

    // Step 3: Set new head and break circular link
    head = newTail->next;
    newTail->next = NULL;

    // Print rotated list
    temp = head;
    while(temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }

    return 0;
}
