#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int n = 10;

int edges[][2] = {
    { 1, 10 },
    { 1, 7 },
    { 1, 3 },
    { 2, 10 },
    { 2, 8 },
    { 2, 7 },
    { 2, 6 },
    { 2, 5 },
    { 2, 3 },
    { 3, 9 },
    { 3, 8 },
    { 3, 4 },
    { 4, 7 },
    { 4, 6 },
    { 5, 10 },
    { 5, 9 },
    { 5, 7 },
    { 5, 6 },
    { 6, 10 },
    { 6, 9 },
    { 6, 7 },
    { 7, 10 },
    { 8, 10 },
    { 8, 9 }
};

typedef struct node Node;

struct node {
    Node *prox;
    int val;
};

typedef struct graph {
	Node **v;
	int n;
} Graph;

Graph *my_graph;

Node* graph_new_node(int val);

void graph_construction(void) {
    my_graph = (Graph*)malloc(sizeof(Graph*));
    my_graph->v = (Node**)malloc(sizeof(Node*) * n);

    for (int i = 0; i < n; i++) {
        my_graph->v[i] = graph_new_node(-1);
    }

    my_graph->n = n;
}

Node* graph_new_node(int val) {
    Node *new_node = (Node*)malloc(sizeof(Node*));

    new_node->prox = NULL;
    new_node->val = val;

    return new_node;
}

int get_edge_el(int arr[][2], int i, int j) {
    return arr[i][j];
}

void graph_add_neighbor(int a, int b) {
    Node *n = my_graph->v[a - 1];

    if (n != NULL) {
        Node *old_node;
        old_node = my_graph->v[a - 1];

        Node *new_node;
        new_node = graph_new_node(b - 1);
        new_node->prox = old_node;

        my_graph->v[a - 1] = new_node;
    } else {
        my_graph->v[a - 1] = graph_new_node(b - 1);
    }

}

void graph_add_edge(int a, int b) {
    graph_add_neighbor(a, b);
    graph_add_neighbor(b, a);
}

int main(void) {
    graph_construction();

    for (int i = 0; i < 24; i++) {
        graph_add_edge(get_edge_el(edges, i, 0), get_edge_el(edges, i, 1));
    }

    for (int i = 0; i < n; i++) {
        printf("%d : ", i);
        
        for (Node* node = my_graph->v[i]; node->prox; node = node->prox) {
            printf("%d", node->val);
            if (node->prox->prox != NULL) {
                printf(", ");
            }
        }

        printf("\n");
    }

    return 0;
}