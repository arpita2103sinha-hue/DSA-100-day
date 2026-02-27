#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

// Create new node
struct Node* newNode(int data) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

// Get length of list
int getLength(struct Node* head) {
    int count = 0;
    while (head) {
        count++;
        head = head->next;
    }
    return count;
}

// Find intersection
struct Node* getIntersection(struct Node* head1, struct Node* head2) {
    int len1 = getLength(head1);
    int len2 = getLength(head2);

    int d = abs(len1 - len2);

    // Move longer list ahead
    if (len1 > len2)
        while (d--) head1 = head1->next;
    else
        while (d--) head2 = head2->next;

    // Traverse together
    while (head1 && head2) {
        if (head1 == head2)
            return head1;
        head1 = head1->next;
        head2 = head2->next;
    }
    return NULL;
}

int main() {
    int n, m, i, val;

    scanf("%d", &n);
    struct Node *head1 = NULL, *tail1 = NULL;

    for (i = 0; i < n; i++) {
        scanf("%d", &val);
        struct Node* temp = newNode(val);
        if (!head1) head1 = tail1 = temp;
        else {
            tail1->next = temp;
            tail1 = temp;
        }
    }

    scanf("%d", &m);
    struct Node *head2 = NULL, *tail2 = NULL;

    for (i = 0; i < m; i++) {
        scanf("%d", &val);
        struct Node* temp = newNode(val);
        if (!head2) head2 = tail2 = temp;
        else {
            tail2->next = temp;
            tail2 = temp;
        }
    }

    struct Node* result = getIntersection(head1, head2);

    if (result)
        printf("%d", result->data);
    else
        printf("No Intersection");

    return 0;
}
