#include <stdio.h>
#include <stdlib.h>

// Tree Node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Create new node
struct Node* newNode(int data) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}

// Queue for BFS
struct Node* queue[100];
int front = 0, rear = 0;

void enqueue(struct Node* node) {
    queue[rear++] = node;
}

struct Node* dequeue() {
    return queue[front++];
}

int isEmpty() {
    return front == rear;
}

// Zigzag Traversal
void zigzagTraversal(struct Node* root) {
    if (root == NULL) return;

    int leftToRight = 1;

    enqueue(root);

    while (!isEmpty()) {
        int size = rear - front;

        int level[100];
        int index = 0;

        // Process one level
        for (int i = 0; i < size; i++) {
            struct Node* curr = dequeue();

            level[index++] = curr->data;

            if (curr->left)
                enqueue(curr->left);

            if (curr->right)
                enqueue(curr->right);
        }

        // Print based on direction
        if (leftToRight) {
            for (int i = 0; i < index; i++)
                printf("%d ", level[i]);
        } else {
            for (int i = index - 1; i >= 0; i--)
                printf("%d ", level[i]);
        }

        // Change direction
        leftToRight = !leftToRight;
    }
}

// Build tree from level order
struct Node* buildTree(int arr[], int n) {
    if (n == 0 || arr[0] == -1) return NULL;

    struct Node* root = newNode(arr[0]);
    struct Node* q[100];
    int f = 0, r = 0;

    q[r++] = root;

    int i = 1;

    while (i < n) {
        struct Node* curr = q[f++];

        if (arr[i] != -1) {
            curr->left = newNode(arr[i]);
            q[r++] = curr->left;
        }
        i++;

        if (i < n && arr[i] != -1) {
            curr->right = newNode(arr[i]);
            q[r++] = curr->right;
        }
        i++;
    }

    return root;
}

int main() {
    int n;
    scanf("%d", &n);

    int arr[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    struct Node* root = buildTree(arr, n);

    zigzagTraversal(root);

    return 0;
}
