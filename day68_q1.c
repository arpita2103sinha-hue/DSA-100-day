#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Queue structure
int queue[MAX], front = 0, rear = 0;

void enqueue(int x) {
    queue[rear++] = x;
}

int dequeue() {
    return queue[front++];
}

int isEmpty() {
    return front == rear;
}

int main() {
    int V = 6;  // number of vertices

    // Adjacency matrix
    int adj[MAX][MAX] = {0};

    // Example edges
    int edges[][2] = {
        {5,2}, {5,0}, {4,0}, {4,1}, {2,3}, {3,1}
    };
    int E = 6;

    // In-degree array
    int indegree[MAX] = {0};

    // Build graph
    for (int i = 0; i < E; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        adj[u][v] = 1;
        indegree[v]++;
    }

    // Add nodes with 0 in-degree to queue
    for (int i = 0; i < V; i++) {
        if (indegree[i] == 0) {
            enqueue(i);
        }
    }

    int topo[MAX];
    int index = 0;

    // Kahn's Algorithm
    while (!isEmpty()) {
        int node = dequeue();
        topo[index++] = node;

        for (int i = 0; i < V; i++) {
            if (adj[node][i] == 1) {
                indegree[i]--;
                if (indegree[i] == 0) {
                    enqueue(i);
                }
            }
        }
    }

    // Check for cycle
    if (index != V) {
        printf("Cycle exists! Topological sort not possible.\n");
    } else {
        printf("Topological Order: ");
        for (int i = 0; i < V; i++) {
            printf("%d ", topo[i]);
        }
    }

    return 0;
}
