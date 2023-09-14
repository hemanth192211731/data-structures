#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in the adjacency list
struct Node {
    int data;
    struct Node* next;
};

// Structure to represent the adjacency list
struct Graph {
    int vertices;
    struct Node** adjList;
    int* visited;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph with 'V' vertices
struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->vertices = V;
    graph->adjList = (struct Node*)malloc(V * sizeof(struct Node));
    graph->visited = (int*)malloc(V * sizeof(int));

    for (int i = 0; i < V; i++) {
        graph->adjList[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

// Function to add an edge to the graph
void addEdge(struct Graph* graph, int src, int dest) {
    struct Node* newNode = createNode(dest);
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    // For undirected graph, you can add the reverse edge as well
    // newNode = createNode(src);
    // newNode->next = graph->adjList[dest];
    // graph->adjList[dest] = newNode;
}

// Depth First Search (DFS) algorithm
void DFS(struct Graph* graph, int vertex) {
    printf("%d ", vertex);
    graph->visited[vertex] = 1;

    struct Node* adjListEntry = graph->adjList[vertex];
    while (adjListEntry != NULL) {
        int connectedVertex = adjListEntry->data;
        if (!graph->visited[connectedVertex]) {
            DFS(graph, connectedVertex);
        }
        adjListEntry = adjListEntry->next;
    }
}

int main() {
    struct Graph* graph = createGraph(5); // Create a graph with 5 vertices

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 4);

    printf("Depth First Traversal starting from vertex 0:\n");
    DFS(graph, 0);

    return 0;
}