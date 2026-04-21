#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100

// Adjacency list node
struct Node {
    int vertex, weight;
    struct Node* next;
};

struct Node* adj[MAX];

// Min Heap Node
struct HeapNode {
    int vertex, dist;
};

// Min Heap
struct MinHeap {
    int size;
    struct HeapNode heap[MAX];
};

// Function to add edge
void addEdge(int u, int v, int w) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->vertex = v;
    newNode->weight = w;
    newNode->next = adj[u];
    adj[u] = newNode;
}

// Swap heap nodes
void swap(struct HeapNode* a, struct HeapNode* b) {
    struct HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify
void heapify(struct MinHeap* h, int i) {
    int smallest = i;
    int left = 2*i, right = 2*i + 1;

    if (left <= h->size && h->heap[left].dist < h->heap[smallest].dist)
        smallest = left;

    if (right <= h->size && h->heap[right].dist < h->heap[smallest].dist)
        smallest = right;

    if (smallest != i) {
        swap(&h->heap[i], &h->heap[smallest]);
        heapify(h, smallest);
    }
}

// Extract min
struct HeapNode extractMin(struct MinHeap* h) {
    struct HeapNode root = h->heap[1];
    h->heap[1] = h->heap[h->size--];
    heapify(h, 1);
    return root;
}

// Insert into heap
void insertHeap(struct MinHeap* h, int vertex, int dist) {
    h->size++;
    int i = h->size;

    h->heap[i].vertex = vertex;
    h->heap[i].dist = dist;

    while (i > 1 && h->heap[i].dist < h->heap[i/2].dist) {
        swap(&h->heap[i], &h->heap[i/2]);
        i = i/2;
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    // Initialize adjacency list
    for (int i = 1; i <= n; i++)
        adj[i] = NULL;

    // Input edges
    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        addEdge(u, v, w);
        addEdge(v, u, w);  // undirected
    }

    int source;
    scanf("%d", &source);

    int dist[MAX];
    for (int i = 1; i <= n; i++)
        dist[i] = INT_MAX;

    dist[source] = 0;

    struct MinHeap heap;
    heap.size = 0;

    insertHeap(&heap, source, 0);

    while (heap.size > 0) {
        struct HeapNode current = extractMin(&heap);
        int u = current.vertex;

        // Traverse neighbors
        struct Node* temp = adj[u];
        while (temp != NULL) {
            int v = temp->vertex;
            int w = temp->weight;

            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                insertHeap(&heap, v, dist[v]);
            }
            temp = temp->next;
        }
    }

    // Output distances
    for (int i = 1; i <= n; i++) {
        printf("%d ", dist[i]);
    }

    return 0;

