#include <stdio.h>
#include <stdlib.h>

// Tree Node structure
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Queue Node for BFS
struct QNode {
    struct Node* node;
    int hd;
};

// Create new tree node
struct Node* newNode(int data) {
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}

// Queue implementation
struct QNode queue[100];
int front = 0, rear = 0;

void enqueue(struct Node* node, int hd) {
    queue[rear].node = node;
    queue[rear].hd = hd;
    rear++;
}

struct QNode dequeue() {
    return queue[front++];
}

int isEmpty() {
    return front == rear;
}

// Vertical Order Traversal
void verticalOrder(struct Node* root) {
    if (root == NULL) return;

    // Map using array (HD range -50 to +50 assumed)
    int map[100][100]; // store nodes
    int count[100] = {0};

    // offset to handle negative index
    int offset = 50;

    enqueue(root, 0);

    while (!isEmpty()) {
        struct QNode temp = dequeue();
        struct Node* curr = temp.node;
        int hd = temp.hd;

        int index = hd + offset;

        map[index][count[index]++] = curr->data;

        if (curr->left)
            enqueue(curr->left, hd - 1);

        if (curr->right)
            enqueue(curr->right, hd + 1);
    }

    // Print result
    for (int i = 0; i < 100; i++) {
        if (count[i] > 0) {
            for (int j = 0; j < count[i]; j++) {
                printf("%d ", map[i][j]);
            }
            printf("\n");
        }
    }
}

// Build tree from level order input
struct Node* buildTree(int arr[], int n) {
    if (n == 0 || arr[0] == -1) return NULL;

    struct Node* root = newNode(arr[0]);
    struct Node* q[100];
    int front = 0, rear = 0;

    q[rear++] = root;

    int i = 1;

    while (i < n) {
        struct Node* curr = q[front++];

        if (arr[i] != -1) {
            curr->left = newNode(arr[i]);
            q[rear++] = curr->left;
        }
        i++;

        if (i < n && arr[i] != -1) {
            curr->right = newNode(arr[i]);
            q[rear++] = curr->right;
        }
        i++;
    }

    return root;
}

int main() {
    int n;
    scanf("%d", &n);

    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    struct Node* root = buildTree(arr, n);

    verticalOrder(root);

    return 0;
}
