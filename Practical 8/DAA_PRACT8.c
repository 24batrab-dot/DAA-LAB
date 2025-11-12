#include <stdio.h>
#include <stdbool.h>
 
#define MAX 20
 
bool isSafe(int v, int graph[MAX][MAX], int color[], int c, int V) {
	for (int i = 0; i < V; i++) {
    	if (graph[v][i] && color[i] == c)
        	return false;
	}
	return true;
}
 
bool graphColoringUtil(int graph[MAX][MAX], int m, int color[], int v, int V) {
	if (v == V)
    	return true;
 
	for (int c = 1; c <= m; c++) {
    	if (isSafe(v, graph, color, c, V)) {
        	color[v] = c;
        	if (graphColoringUtil(graph, m, color, v + 1, V))
            	return true;
        	color[v] = 0;
    	}
	}
	return false;
}
 
void graphColoring(int graph[MAX][MAX], int m, int V) {
	int color[MAX];
	for (int i = 0; i < V; i++)
    	color[i] = 0;
 
	if (!graphColoringUtil(graph, m, color, 0, V)) {
        printf("No solution exists using %d colors.\n", m);
    	return;
	}
 
	printf("Color assigned to each vertex:\n");
	for (int i = 0; i < V; i++)
        printf("Vertex %d --> Color %d\n", i + 1, color[i]);
}
 
int main() {
	int V, m;
	int graph[MAX][MAX];
 
	printf("Enter number of vertices: ");
    scanf("%d", &V);
 
	printf("Enter number of colors: ");
    scanf("%d", &m);
 
	printf("Enter adjacency matrix (%d x %d):\n", V, V);
	for (int i = 0; i < V; i++) {
    	for (int j = 0; j < V; j++) {
            scanf("%d", &graph[i][j]);
    	}
	}
 
    graphColoring(graph, m, V);
	return 0;
}

