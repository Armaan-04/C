#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Function to find the vertex with the minimum distance value, 
// from the set of vertices not yet included in the shortest path tree (Min-Priority Queue simulation)
int minDistance(int dist[], int sptSet[], int N) {
    int min = INT_MAX, min_index = -1;

    for (int v = 0; v < N; v++) {
        // Find the node that hasn't been processed AND has the smallest current distance
        if (sptSet[v] == 0 && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// Utility function to print the shortest path from parent array
void printPath(int parent[], int j) {
    // Base case: If j is the source (parent is -1)
    if (parent[j] == -1) {
        printf("%d", j + 1);
        return;
    }

    printPath(parent, parent[j]);
    printf("->%d", j + 1);
}

// Function that implements Dijkstra's algorithm
void dijkstra(int** graph, int N, int src) {
    int dist[N];      // dist[i] will hold the shortest distance from src to i
    int sptSet[N];    // sptSet[i] will be true if vertex i is included in MST
    int parent[N];    // parent array to store shortest path tree

    // Initialize all distances as INFINITE and sptSet[] as false
    for (int i = 0; i < N; i++) {
        dist[i] = INT_MAX;
        sptSet[i] = 0;
        parent[i] = -1;
    }

    // Distance of source vertex from itself is always 0
    int src_index = src - 1;
    dist[src_index] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < N - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not yet processed
        int u = minDistance(dist, sptSet, N);

        // If no more reachable vertices are found, break
        if (u == -1 || dist[u] == INT_MAX)
            break;

        // Mark the picked vertex as processed
        sptSet[u] = 1;

        // Update dist value of the adjacent vertices of the picked vertex
        for (int v = 0; v < N; v++) {
            // Update dist[v] only if:
            // 1. It's not in sptSet
            // 2. There is an edge from u to v (graph[u][v] != 0)
            // 3. Total weight of path from src to v through u is smaller than current dist[v]
            if (!sptSet[v] && graph[u][v] != 0 && dist[u] != INT_MAX && 
                dist[u] + graph[u][v] < dist[v]) {
                parent[v] = u;
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    // --- Output Results ---
    printf("\nOutput:\n");
    printf("Source\tDestination\tCost\tPath\n");
    for (int i = 0; i < N; i++) {
        printf("%d\t%d\t\t%d\t", src, i + 1, dist[i]);
        if (dist[i] == INT_MAX) {
            printf("N/A (Unreachable)\n");
        } else {
            printPath(parent, i);
            printf("\n");
        }
    }
}

int main() {
    int N;
    int source_vertex;

    // --- User Input for Vertices ---
    printf("Enter the Number of Vertices: ");
    if (scanf("%d", &N) != 1 || N <= 0) {
        printf("Invalid number of vertices.\n");
        return 1;
    }

    // Dynamic memory allocation for the graph (Adjacency Matrix)
    int** graph = (int**)malloc(N * sizeof(int*));
    if (graph == NULL) {
        perror("Failed to allocate memory");
        return 1;
    }
    for (int i = 0; i < N; i++) {
        graph[i] = (int*)malloc(N * sizeof(int));
        if (graph[i] == NULL) {
            perror("Failed to allocate memory");
            // Clean up previously allocated memory
            for(int j = 0; j < i; j++) free(graph[j]);
            free(graph);
            return 1;
        }
    }

    // --- User Input for Adjacency Matrix ---
    printf("Enter the Cost Adjacency Matrix (%d x %d). Enter 0 for no direct edge:\n", N, N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (scanf("%d", &graph[i][j]) != 1) {
                printf("Error reading matrix element.\n");
                // Clean up memory
                for(int k = 0; k < N; k++) free(graph[k]);
                free(graph);
                return 1;
            }
        }
    }

    // --- User Input for Source Vertex ---
    printf("Enter the Source Vertex (1 to %d): ", N);
    if (scanf("%d", &source_vertex) != 1 || source_vertex < 1 || source_vertex > N) {
        printf("Invalid source vertex.\n");
        // Clean up memory
        for(int k = 0; k < N; k++) free(graph[k]);
        free(graph);
        return 1;
    }
    
    // --- Run Dijkstra's Algorithm ---
    printf("\n--- Running Dijkstra's Algorithm ---\n");
    dijkstra(graph, N, source_vertex);

    // --- Clean up memory ---
    for (int i = 0; i < N; i++) {
        free(graph[i]);
    }
    free(graph);

    return 0;
}