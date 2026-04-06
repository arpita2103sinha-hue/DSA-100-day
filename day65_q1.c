#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NODES 100

// Adjacency list representation
typedef struct Node {
    int dest;
    struct Node* next;
} Node;

typedef struct Graph {
    Node* adjList[MAX_NODES];
} Graph;

Node* createNode(int dest) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    newNode = createNode(src);
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

bool isCyclicUtil(Graph* graph, int u, bool visited[], int parent) {
    visited[u] = true;
    Node* temp = graph->adjList[u];

    while (temp != NULL) {
        int v = temp->dest;
        if (!visited[v]) {
            if (isCyclicUtil(graph, v, visited, u))
                return true;
        } else if (v != parent) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

bool isCyclic(Graph* graph, int numNodes) {
    bool* visited = (bool*)malloc(numNodes * sizeof(bool));
    for (int i = 0; i < numNodes; i++)
        visited[i] = false;

    for (int i = 0; i < numNodes; i++) {
        if (!visited[i]) {
            if (isCyclicUtil(graph, i, visited, -1)) {
                free(visited);
                return true;
            }
        }
    }
    free(visited);
    return false;
}

int main() {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    for (int i = 0; i < MAX_NODES; i++) {
        graph->adjList[i] = NULL;
    }
    int numNodes = 4;
    addEdge(graph, 0, 1);
    addEdge(graph, 1, 2);
    addEdge(graph, 2, 0);
    addEdge(graph, 2, 3);

    if (isCyclic(graph, numNodes))
        printf("YES\n");
    else
        printf("NO\n");

    // Clean up memory (basic example, full cleanup would be more complex)
    return 0;
}
