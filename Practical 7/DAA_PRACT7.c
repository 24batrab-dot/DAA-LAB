#include <stdio.h>
#include <stdbool.h>

#define MAX 10

int V; // Number of vertices

bool isSafe(int v, int graph[MAX][MAX], int path[], int pos) {
    // Check if current vertex and previous vertex are adjacent
    if (graph[path[pos - 1]][v] == 0)
        return false;

    // Check if vertex already included in path
    for (int i = 0; i < pos; i++)
        if (path[i] == v)
            return false;

    return true;
}

bool hamiltonianCycleUtil(int graph[MAX][MAX], int path[], int pos) {
    // Base case: all vertices included
    if (pos == V) {
        // Check if last vertex connects back to first
        if (graph[path[pos - 1]][path[0]] == 1)
            return true;
        else
            return false;
    }

    // Try different vertices as next in cycle
    for (int v = 1; v < V; v++) {
        if (isSafe(v, graph, path, pos)) {
            path[pos] = v;

            if (hamiltonianCycleUtil(graph, path, pos + 1))
                return true;

            // Backtrack
            path[pos] = -1;
        }
    }

    return false;
}

void printSolution(int path[]) {
    printf("Hamiltonian Cycle Found:\n");
    for (int i = 0; i < V; i++)
        printf("%c -> ", 'A' + path[i]);
    printf("%c\n", 'A' + path[0]); // Return to start
}

void hamiltonianCycle(int graph[MAX][MAX]) {
    int path[MAX];
    for (int i = 0; i < V; i++)
        path[i] = -1;

    path[0] = 0; // Start from Area A (HQ)

    if (hamiltonianCycleUtil(graph, path, 1) == false) {
        printf("No Hamiltonian Cycle exists.\n");
        return;
    }

    printSolution(path);
}

int main() {
    int graph[MAX][MAX];

    printf("Enter number of areas (vertices): ");
    scanf("%d", &V);

    printf("Enter adjacency matrix (%d x %d):\n", V, V);
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    hamiltonianCycle(graph);
    return 0;
}

