#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int vert;
    struct Node* prox;
} node;

node* createNode(int v) {
    node* newNode = (node*)malloc(sizeof(node));
    newNode->vert = v;
    newNode->prox = NULL;
    return newNode;
}

typedef struct {
    int numVertx;
    node** adjList;
} graph;

graph* createGraph(int vertices) {
    int i;
    graph* grafo = (graph*)malloc(sizeof(graph));
    grafo->numVertx = vertices;
    grafo->adjList = (node**)malloc(vertices * sizeof(node*));
    for (i = 0; i < vertices; i++)
        grafo->adjList[i] = NULL;
    return grafo;
}

void addEdge(graph* grafo, int s, int d) {
    node* newNode = createNode(d);
    newNode->prox = grafo->adjList[s];
    grafo->adjList[s] = newNode;

    newNode = createNode(s);
    newNode->prox = grafo->adjList[d];
    grafo->adjList[d] = newNode;
}

void printGraph(graph* grafo) {
    int v;
    for (v = 0; v < grafo->numVertx; v++) {
        node* tmp = grafo->adjList[v];
        printf("\nVertex %d:", v);
        while (tmp) {
            printf(" %d", tmp->vert);
            tmp = tmp->prox;
        }
        printf("\n");
    }
}
