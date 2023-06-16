#ifndef GRAPH_H
#define GRAPH_H

#include <stdlib.h>

#define MAX 100

typedef struct node {
    int vertex;
    struct node* next;
} Node;

typedef struct graph {
    int numVertices;
    Node** adjLists;
} Graph;

Node* createNode(int v);
Graph* createGraph(int vertices);
void addEdge(Graph* graph, int src, int dest);

#endif