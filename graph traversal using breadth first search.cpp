#include <stdio.h>
#include <stdlib.h>
#define MAX_NODES 100

// Structure for representing a queue
struct Queue {
    int items[MAX_NODES];
    int front;
    int rear;
};

// Function to create an empty queue
struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = -1;
    queue->rear = -1;
    return queue;
}

// Function to check if the queue is empty
int isEmpty(struct Queue* queue) {
    return queue->rear == -1;
}

// Function to enqueue an element
void enqueue(struct Queue* queue, int item) {
    if (queue->rear == MAX_NODES - 1)
        printf("Queue is full.\n");
    else {
        if (queue->front == -1)
            queue->front = 0;
        queue->rear++;
        queue->items[queue->rear] = item;
    }
}

// Function to dequeue an element
int dequeue(struct Queue* queue) {
    int item;
    if (isEmpty(queue)) {
        printf("Queue is empty.\n");
        item = -1;
    } else {
        item = queue->items[queue->front];
        queue->front++;
        if (queue->front > queue->rear) {
            queue->front = -1;
            queue->rear = -1;
        }
    }
    return item;
}

// Structure for representing a graph node
struct GraphNode {
    int data;
    struct GraphNode* next;
};

// Structure for representing a graph
struct Graph {
    int numNodes;
    struct GraphNode** adjacencyList;
    int* visited;
};

// Function to create a graph node
struct GraphNode* createGraphNode(int data) {
    struct GraphNode* newNode = (struct GraphNode*)malloc(sizeof(struct GraphNode));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph
struct Graph* createGraph(int numNodes) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->numNodes = numNodes;
    graph->adjacencyList = (struct GraphNode**)malloc(numNodes * sizeof(struct GraphNode*));
    graph->visited = (int*)malloc(numNodes * sizeof(int));

    for (int i = 0; i < numNodes; i++) {
        graph->adjacencyList[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

// Function to add an edge to the graph
void addEdge(struct Graph* graph, int src, int dest) {
    struct GraphNode* newNode = createGraphNode(dest);
    newNode->next = graph->adjacencyList[src];
    graph->adjacencyList[src] = newNode;

    newNode = createGraphNode(src);
    newNode->next = graph->adjacencyList[dest];
    graph->adjacencyList[dest] = newNode;
}

// Function to perform BFS traversal of the graph
void BFS(struct Graph* graph, int startNode) {
    struct Queue* queue = createQueue();

    graph->visited[startNode] = 1;
    enqueue(queue, startNode);

    while (!isEmpty(queue)) {
        int current = dequeue(queue);
        printf("%d ", current);

        struct GraphNode* temp = graph->adjacencyList[current];
        while (temp != NULL) {
            int adjNode = temp->data;
            if (graph->visited[adjNode] == 0) {
                graph->visited[adjNode] = 1;
                enqueue(queue, adjNode);
            }
            temp = temp->next;
        }
    }
}

int main() {
    int numNodes = 6;
    struct Graph* graph = createGraph(numNodes);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 3);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 4);
    addEdge(graph, 3, 5);

    int startNode = 0;
    printf("Breadth First Traversal starting from node %d:\n", startNode);
    BFS(graph, startNode);
    printf("\n");

    return 0;
}
