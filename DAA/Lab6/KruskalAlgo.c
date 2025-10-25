#include <stdio.h>
#include <stdlib.h>

// Structure to represent an edge
typedef struct {
    int u, v; // Vertices of the edge
    int weight;
} Edge;

// Structure for Disjoint Set Union (DSU) - Note: parent array size limits max nodes to 100
typedef struct {
    int parent[100]; 
    int n;
} DSU;

// --- DSU Operations ---

// Initializes the DSU set: each node is its own parent
void make_set(DSU* dsu, int n) {
    dsu->n = n;
    for (int i = 1; i <= n; i++) {
        dsu->parent[i] = i;
    }
}

// Finds the representative (root) of the set containing node 'i' (with path compression)
int find_set(DSU* dsu, int i) {
    if (dsu->parent[i] == i)
        return i;
    return dsu->parent[i] = find_set(dsu, dsu->parent[i]);
}

// Unions two sets
void union_sets(DSU* dsu, int i, int j) {
    int root_i = find_set(dsu, i);
    int root_j = find_set(dsu, j);
    if (root_i != root_j) {
        dsu->parent[root_j] = root_i;
    }
}

// --- Kruskal's Logic ---

// Comparison function for qsort: sorts edges by weight in non-decreasing (ascending) order
int compareEdges(const void* a, const void* b) {
    return ((Edge*)a)->weight - ((Edge*)b)->weight;
}

void kruskalMST(Edge edges[], int n, int m) {
    // Sort all edges by weight
    qsort(edges, m, sizeof(Edge), compareEdges);

    DSU dsu;
    make_set(&dsu, n);

    // MST will have n-1 edges. We don't need to store them explicitly here.
    int edge_count = 0;
    long long total_cost = 0;
    
    // Output header
    printf("\nOutput:\n");
    printf("Edge\tCost\n");

    for (int i = 0; i < m && edge_count < n - 1; i++) {
        Edge current_edge = edges[i];

        // Check if adding the edge forms a cycle
        if (find_set(&dsu, current_edge.u) != find_set(&dsu, current_edge.v)) {
            // Add edge to MST
            union_sets(&dsu, current_edge.u, current_edge.v);
            edge_count++;
            total_cost += current_edge.weight;
            
            // Display the selected edge and cost
            printf("%d-%d\t%d\n", current_edge.u, current_edge.v, current_edge.weight);
        }
    }
    
    // Check if a spanning tree was actually formed
    if (edge_count == n - 1) {
        printf("\nTotal cost of the minimum spanning tree T: %lld\n", total_cost);
    } else {
        printf("\nError: A spanning tree could not be formed (Graph is disconnected).\n");
    }
}

int main() {
    int n, m;
    
    // --- 1. Get Number of Nodes (n) and Edges (m) ---
    printf("Input:\n");
    printf("Enter the number of nodes (n) and edges (m) separated by a space (e.g., 9 14): ");
    if (scanf("%d %d", &n, &m) != 2 || n <= 1 || m <= 0) {
        printf("Invalid input for nodes or edges.\n");
        return 1;
    }
    
    // Check for DSU limits
    if (n >= 100) {
        printf("Node limit exceeded. Max nodes supported is 99.\n");
        return 1;
    }
    
    // --- 2. Dynamic Allocation for Edges ---
    Edge* edges = (Edge*)malloc(m * sizeof(Edge));
    if (edges == NULL) {
        perror("Failed to allocate memory for edges");
        return 1;
    }

    // --- 3. Input Edge List ---
    printf("Enter the %d edges in the format 'u v weight' on separate lines:\n", m);
    for (int i = 0; i < m; i++) {
        if (scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].weight) != 3) {
            printf("Error reading edge data for edge %d.\n", i + 1);
            free(edges);
            return 1;
        }
        // Basic input validation
        if (edges[i].u < 1 || edges[i].u > n || edges[i].v < 1 || edges[i].v > n) {
            printf("Error: Node IDs must be between 1 and %d.\n", n);
            free(edges);
            return 1;
        }
    }
    
    // --- 4. Apply Kruskal's Algorithm ---
    kruskalMST(edges, n, m); 

    // --- 5. Clean up memory ---
    free(edges);

    return 0;
}