#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Function to find the vertex with the minimum key value, 
// from the set of vertices not yet included in MST
int findMinKey(int key[], int mstSet[], int N) {
    int min = INT_MAX, min_index = -1;

    for (int v = 0; v < N; v++) {
        // Find the node that hasn't been processed AND has the smallest current key value
        if (mstSet[v] == 0 && key[v] < min) {
            min = key[v];
            min_index = v;
        }
    }
    return min_index;
}

// Function to print the MST cost adjacency matrix and calculate total cost
void printMST(int parent[], int** graph, int N) {
    long long total_cost = 0;
    
    // Allocate memory for the MST matrix dynamically
    int** mst_matrix = (int**)malloc(N * sizeof(int*));
    if (mst_matrix == NULL) {
        printf("Error: Failed to allocate memory for MST matrix.\n");
        return;
    }
    for(int i = 0; i < N; i++) {
        mst_matrix[i] = (int*)malloc(N * sizeof(int));
        if (mst_matrix[i] == NULL) {
            printf("Error: Failed to allocate memory for MST matrix row.\n");
            // Clean up rows allocated so far
            for(int k = 0; k < i; k++) free(mst_matrix[k]);
            free(mst_matrix);
            return;
        }
        // Initialize MST matrix row to 0
        for(int j = 0; j < N; j++) {
            mst_matrix[i][j] = 0;
        }
    }
    
    // Build the MST matrix and calculate total cost
    // We only iterate from i=1 because parent[start_index] is -1 (the root)
    for (int i = 0; i < N; i++) {
        if (parent[i] != -1) {
            int u = parent[i];
            int v = i;
            int weight = graph[i][parent[i]];
            
            // Add edge to the MST matrix (undirected graph)
            mst_matrix[u][v] = weight;
            mst_matrix[v][u] = weight;
            
            total_cost += weight;
        }
    }
    
    // Display the MST cost adjacency matrix
    printf("\nOutput:\n");
    printf("Cost Adjacency Matrix of the Minimum Spanning Tree (T'):\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", mst_matrix[i][j]);
        }
        printf("\n");
    }

    // Display the total cost
    printf("\nTotal cost of the minimum spanning tree T: %lld\n", total_cost);

    // Free allocated memory for the MST matrix
    for(int i = 0; i < N; i++) {
        free(mst_matrix[i]);
    }
    free(mst_matrix);
}

// Prim's Algorithm function
void primMST(int** graph, int N, int start_vertex) {
    // Array to store the constructed MST
    int parent[N]; 
    
    // Key values used to pick minimum weight edge
    int key[N];    
    
    // To represent set of vertices not yet included in MST
    int mstSet[N]; 

    // Initialize all keys to infinity and mstSet to false
    for (int i = 0; i < N; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0; // 0 means not yet in MST
    }

    // Key of the starting vertex is 0, so it is picked first.
    int start_index = start_vertex - 1;
    key[start_index] = 0;
    parent[start_index] = -1; // Root of MST

    // The loop runs N times, picking one vertex in each iteration
    for (int count = 0; count < N; count++) {
        // Pick the minimum key vertex from the set of vertices not yet included in MST
        int u = findMinKey(key, mstSet, N);
        
        // If no valid vertex is found (happens in disconnected graphs), we stop
        if (u == -1 || key[u] == INT_MAX)
            break; 

        // Add the picked vertex to the MST Set
        mstSet[u] = 1;

        // Update key value and parent index of the adjacent vertices
        for (int v = 0; v < N; v++) {
            // Check 1: graph[u][v] is non-zero (there is an edge)
            // Check 2: v is not yet in MST (mstSet[v] == 0)
            // Check 3: The edge weight is less than current key[v]
            if (graph[u][v] != 0 && mstSet[v] == 0 && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    // Print the final result
    printMST(parent, graph, N);
}

int main() {
    int N;
    int start_vertex;
    
    // --- 1. Get Number of Vertices ---
    printf("Input:\n");
    printf("Enter the number of Vertices: ");
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
            perror("Failed to allocate memory for graph row");
            // Clean up previously allocated memory
            for(int j = 0; j < i; j++) free(graph[j]);
            free(graph);
            return 1;
        }
    }

    // --- 2. Input Adjacency Matrix ---
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
    
    // --- 3. Get Starting Vertex ---
    printf("Enter the Starting Vertex (1 to %d): ", N);
    if (scanf("%d", &start_vertex) != 1 || start_vertex < 1 || start_vertex > N) {
        printf("Invalid starting vertex.\n");
        // Clean up memory
        for(int k = 0; k < N; k++) free(graph[k]);
        free(graph);
        return 1;
    }

    // --- 4. Apply Prim's Algorithm ---
    primMST(graph, N, start_vertex);

    // --- 5. Clean up memory ---
    for (int i = 0; i < N; i++) {
        free(graph[i]);
    }
    free(graph);

    return 0;
}