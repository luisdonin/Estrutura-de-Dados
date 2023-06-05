#include <stdio.h>
#include <stdlib.h>



typedef struct Node {
    int vert;
    struct Node* prox;
}node;

node* createNode(int);

typedef struct {
    int numVertx;
    node** adjList;
}graph;

node *createNode(int v){
    node *newNode = (node*)malloc(sizeof(node*));
    newNode->vert = v;
    newNode->prox = NULL;
    return newNode;
}

graph* createGraph(int vertices){
    int i=0;
    graph* grafo = (graph*)malloc(sizeof(graph));
    grafo->numVertx = vertices;
    grafo->adjList = malloc(vertices * sizeof(graph));//checar com professor
    for(i = 0; i < vertices; i++)
        grafo->adjList[i] = NULL;
    return grafo;
}

void addEdge(graph* grafo, int s, int d){
    node* newNode = createNode(d);
    newNode->prox = grafo->adjList[s];
    grafo->adjList[s] = newNode;

    newNode = createNode(s);
    newNode->prox = grafo->adjList[d];
    grafo->adjList[d] = newNode;
}

void printGraph(graph* grafo){
    int v = 0;
    for(v = 0; v <grafo->numVertx; v++){
        node* tmp = grafo->adjList[v];
        printf("\n Vertice: %d", v);
        while(tmp){
            tmp = tmp->prox;
        }
        printf("\n");
    }

}
