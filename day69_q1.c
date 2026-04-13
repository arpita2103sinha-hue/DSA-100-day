#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define V5   // Number of vertices

// Structure for adjacency list node
struct AdjListNode {
    int dest;
    int weight;
    struct AdjListNode* next;
};

// Structure for adjacency list
struct AdjList {
    struct AdjListNode* head;
};

// Structure for graph
struct Graph {
    int V;
    struct AdjList* array;
};

// Min Heap Node
struct MinHeapNode {
    int v;
    int dist;
};

// Min Heap
struct MinHeap {
    int size;
    int capacity;
    int* pos;
    struct MinHeapNode** array;
};

// Create new adjacency list node
struct AdjListNode* newAdjListNode(int dest, int weight) {
    struct AdjListNode* newNode =
        (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

// Create graph
struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;

    graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));

    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;

    return graph;
}

// Add edge
void addEdge(struct Graph* graph, int src, int dest, int weight) {
    struct AdjListNode* newNode = newAdjListNode(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    newNode = newAdjListNode(src, weight);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// Create min heap node
struct MinHeapNode* newMinHeapNode(int v, int dist) {
    struct MinHeapNode* minHeapNode =
        (struct MinHeapNode*) malloc(sizeof(struct MinHeapNode));
    minHeapNode->v = v;
    minHeapNode->dist = dist;
    return minHeapNode;
}

// Create min heap
struct MinHeap* createMinHeap(int capacity) {
    struct MinHeap* minHeap =
        (struct MinHeap*) malloc(sizeof(struct MinHeap));
    minHeap->pos = (int*) malloc(capacity * sizeof(int));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array =
        (struct MinHeapNode**) malloc(capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

// Swap nodes
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

// Heapify
void minHeapify(struct MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size &&
        minHeap->array[left]->dist < minHeap->array[smallest]->dist)
        smallest = left;

    if (right < minHeap->size &&
        minHeap->array[right]->dist < minHeap->array[smallest]->dist)
        smallest = right;

    if (smallest != idx) {
        struct MinHeapNode* smallestNode = minHeap->array[smallest];
        struct MinHeapNode* idxNode = minHeap->array[idx];

        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;

        swapMinHeapNode(&minHeap->array[smallest],
                        &minHeap->array[idx]);

        minHeapify(minHeap, smallest);
    }
}

// Check empty
int isEmpty(struct MinHeap* minHeap) {
    return minHeap->size == 0;
}

// Extract min
struct MinHeapNode* extractMin(struct MinHeap* minHeap) {
    if (isEmpty(minHeap))
        return NULL;

    struct MinHeapNode* root = minHeap->array[0];
    struct MinHeapNode* lastNode =
        minHeap->array[minHeap->size - 1];

    minHeap->array[0] = lastNode;

    minHeap->pos[root->v] = minHeap->size - 1;
    minHeap->pos[lastNode->v] = 0;

    --minHeap->size;
    minHeapify(minHeap, 0);

    return root;
}

// Decrease key
void decreaseKey(struct MinHeap* minHeap, int v, int dist) {
    int i = minHeap->pos[v];
    minHeap->array[i]->dist = dist;

    while (i && minHeap->array[i]->dist < minHeap->array[(i - 1) / 2]->dist) {
        minHeap->pos[minHeap->array[i]->v] = (i - 1) / 2;
        minHeap->pos[minHeap->array[(i - 1) / 2]->v] = i;

        swapMinHeapNode(&minHeap->array[i],
                        &minHeap->array[(i - 1) / 2]);

        i = (i - 1) / 2;
    }
}

// Check if vertex is in heap
int isInMinHeap(struct MinHeap *minHeap, int v) {
    return minHeap->pos[v] < minHeap->size;
}

// Dijkstra Algorithm
void dijkstra(struct Graph* graph, int src) {
    int V = graph->V;
    int dist[V];

    struct MinHeap* minHeap = createMinHeap(V);

    for (int v = 0; v < V; ++v) {
        dist[v] = INT_MAX;
        minHeap->array[v] = newMinHeapNode(v, dist[v]);
        minHeap->pos[v] = v;
    }

    minHeap->array[src] = newMinHeapNode(src, 0);
    minHeap->pos[src] = src;
    dist[src] = 0;
    minHeap->size = V;

    decreaseKey(minHeap, src, 0);

    while (!isEmpty(minHeap)) {
        struct MinHeapNode* minNode = extractMin(minHeap);
        int u = minNode->v;

        struct AdjListNode* pCrawl = graph->array[u].head;
        while (pCrawl != NULL) {
            int v = pCrawl->dest;

            if (isInMinHeap(minHeap, v) &&
                dist[u] != INT_MAX &&
                pCrawl->weight + dist[u] < dist[v]) {

                dist[v] = dist[u] + pCrawl->weight;
                decreaseKey(minHeap, v, dist[v]);
            }
            pCrawl = pCrawl->next;
        }
    }

    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < V; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}

// Driver code
int main() {
    int V = 5;
    struct Graph* graph = createGraph(V);

    addEdge(graph, 0, 1, 10);
    addEdge(graph, 0, 4, 5);
    addEdge(graph, 1, 2, 1);
    addEdge(graph, 4, 1, 3);
    addEdge(graph, 4, 2, 9);
    addEdge(graph, 4, 3, 2);
    addEdge(graph, 2, 3, 4);
    addEdge(graph, 3, 2, 6);

    dijkstra(graph, 0);

    return 0;
}
