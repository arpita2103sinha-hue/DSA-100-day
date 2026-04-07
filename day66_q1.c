#include <stdio.h>
#include <stdbool.h>

#define MAX 100

int graph[MAX][MAX];  // Adjacency matrix
int V;                // Number of vertices

bool visited[MAX];
bool recStack[MAX];

// DFS function to detect cycle
bool isCyclicUtil(int v) {
    visited[v] = true;
    recStack[v] = true;

    for (int i = 0; i < V; i++) {
        if (graph[v][i]) {  // Edge exists
            if (!visited[i] && isCyclicUtil(i))
                return true;
            else if (recStack[i])
                return true;
        }
    }

    recStack[v] = false;  // Remove from recursion stack
    return false;
}

// Main function to check cycle
bool isCyclic() {
    for (int i = 0; i < V; i++) {
        visited[i] = false;
        recStack[i] = false;
    }

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            if (isCyclicUtil(i))
                return true;
        }
    }

    return false;
}

int main() {
    int edges, u, v;

    printf("Enter number of vertices: ");
    scanf("%d", &V);

    // Initialize graph
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            graph[i][j] = 0;

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter edges (u v):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;  // Directed edge
    }

    if (isCyclic())
        printf("YES\n");
    else
        printf("NO\n");

    return 0;
}
