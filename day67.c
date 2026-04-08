#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Stack
int stack[MAX];
int top = -1;

// Function to push into stack
void push(int x) {
    stack[++top] = x;
}

// DFS function
void dfs(int node, int visited[], int** graph, int* graphColSize) {
    visited[node] = 1;

    // Visit all neighbors
    for (int i = 0; i < graphColSize[node]; i++) {
        int neighbor = graph[node][i];
        if (!visited[neighbor]) {
            dfs(neighbor, visited, graph, graphColSize);
        }
    }

    // Push after visiting all neighbors
    push(node);
}

// Function to perform topological sort
void topologicalSort(int numCourses, int** graph, int* graphColSize) {
    int visited[MAX] = {0};

    // Call DFS for all unvisited nodes
    for (int i = 0; i < numCourses; i++) {
        if (!visited[i]) {
            dfs(i, visited, graph, graphColSize);
        }
    }

    // Print result (reverse of finishing time)
    printf("Topological Order: ");
    while (top != -1) {
        printf("%d ", stack[top--]);
    }
    printf("\n");
}

// Driver code
int main() {
    int numCourses = 6;

    // Allocate graph
    int** graph = (int**)malloc(numCourses * sizeof(int*));
    int* graphColSize = (int*)calloc(numCourses, sizeof(int));

    for (int i = 0; i < numCourses; i++) {
        graph[i] = (int*)malloc(numCourses * sizeof(int));
    }

    // Example DAG:
    // 5 ? 2, 0
    // 4 ? 0, 1
    // 2 ? 3
    // 3 ? 1

    graph[5][graphColSize[5]++] = 2;
    graph[5][graphColSize[5]++] = 0;
    graph[4][graphColSize[4]++] = 0;
    graph[4][graphColSize[4]++] = 1;
    graph[2][graphColSize[2]++] = 3;
    graph[3][graphColSize[3]++] = 1;

    topologicalSort(numCourses, graph, graphColSize);

    return 0;
}
