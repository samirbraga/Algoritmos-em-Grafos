#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int m = 20;

int w[] = {
    25.8,
    53.6,
    56.6,
    -19.8,
    -72.6,
    -96.7,
    -71.7,
    27.1,
    2.7,
    27.5,
    22.5,
    -78.2,
    5.3,
    -41.5,
    -61.6,
    5.2,
    83.8,
    -29.5,
    -87.4,
    -96.0,
    78.0,
    70.2,
    52.0,
    8.0
};

typedef struct node Node;

struct node {
    Node *next;
    int val;
};

typedef struct graph {
    Node **v;
    int n;
} Graph;

typedef struct set {
    int size;
    Node* first;
} Set;

typedef struct edge {
    double weight;
    int from;
    int to;
} Edge;

typedef struct heap {
	Edge **data;
	int size;
} Heap;

Heap *my_heap;

// Assinatura dos métodos de manipulações da Heap

void heap_construction(void);

void heap_shiftup(int node_index);

void heap_add(int i);

void heap_shiftdown(int node_index);

void heap_remove_min(void);

Edge* heap_min(Edge **arr);

void print_arr(double *arr);


// Assinatura dos métodos de manipulações da Grafo

void graph_construction(void);

Node* graph_new_node(int val);

int get_edge_el(int arr[][2], int i, int j);

void graph_add_neighbor(int a, int b);

void graph_add_edge(int a, int b);

Edge* graph_create_edge(int i);

Graph* graph_AVG();



// Implementações dos métodos de manipulações da Heap

void heap_construction(void) {
    my_heap = (Heap*)malloc(sizeof(Heap*));
    my_heap->data = (Edge**)malloc(sizeof(Edge*) * m);

    int i = 0;
    for (int i; i < m; i++) {
        my_heap->data[i] = NULL;
    }

    my_heap->size = 0;
}

void heap_shiftup(int node_index) {
	int parent_index;
    Edge* tmp;

    // Concertando a heap
    if (node_index != 0) {
        parent_index = (int)(node_index / 2);
        if (my_heap->data[parent_index]->weight > my_heap->data[node_index]->weight) {
            tmp = my_heap->data[parent_index];
            my_heap->data[parent_index] = my_heap->data[node_index];
            my_heap->data[node_index] = tmp;
            heap_shiftup(parent_index);
        }
    }
}

void heap_add(int i) {
    Edge *new_edge = graph_create_edge(w[i]);

    // Adicionando noh no fim do vetor
    my_heap->size++;
    my_heap->data[my_heap->size - 1] = new_edge;

    int current_index = my_heap->size - 1;

    heap_shiftup(current_index);
}

void heap_shiftdown(int node_index) {
    int left_child_index, right_child_index, min_index;
    Edge *tmp;
    left_child_index = node_index * 2;
    right_child_index = node_index * 2 + 1;

    if (right_child_index >= my_heap->size) {
        if (left_child_index >= my_heap->size) {
            return;
        } else {
            min_index = left_child_index;
        }
    } else {
        if (my_heap->data[left_child_index]->weight <= my_heap->data[right_child_index]->weight) {
            min_index = left_child_index;
        } else {
            min_index = right_child_index;
        }
    }

    if (my_heap->data[node_index]->weight > my_heap->data[min_index]->weight) {
        tmp = my_heap->data[min_index];
        my_heap->data[min_index] = my_heap->data[node_index];
        my_heap->data[node_index] = tmp;
        heap_shiftdown(min_index);
    }
}

void heap_remove_min(void) {
    my_heap->data[0] = my_heap->data[my_heap->size - 1];
    my_heap->size--;

    if (my_heap->size > 0) {
        heap_shiftdown(0);
    }
}

Edge* heap_min(Edge **arr) {
    return arr[0];
}

void print_arr(double *arr) {
    for (int i = 0; i < m; i++)
        printf("%lf %d\n", arr[i], i);
}


// Código referente ao Grafo

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

Graph *my_graph;

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

    if (new_node) {
        new_node->next = NULL;
        new_node->val = val;

        return new_node;
    }
}

int get_edge_el(int arr[][2], int i, int j) {
    return arr[i][j];
}

void graph_add_neighbor(int a, int b) {
    Node *n = my_graph->v[a];

    if (n != NULL) {
        Node *new_node;
        new_node = graph_new_node(b);
        new_node->next = n;

        my_graph->v[a] = new_node;
    } else {
        my_graph->v[a] = graph_new_node(b);
    }

}

void graph_add_edge(int a, int b) {
    graph_add_neighbor(a, b);
    graph_add_neighbor(b, a);
}

Edge* graph_create_edge(int i) {
    Edge *edge = (Edge*)malloc(sizeof(Edge*));
    edge->from = edges[i][0];
    edge->to = edges[i][1];
    edge->weight = w[i];

    return edge;
}

Graph* graph_AVG() {
    Graph *T;
    T = (Graph*)malloc(sizeof(Graph*));
    T->v = (Node**)malloc(sizeof(Node*) * n);

    Set *L[n];

    for (int i = 0; i < n - 1; i++) {
        Set *C = (Set*)malloc(sizeof(Set*));
        Node *N = (Node*)malloc(sizeof(Node*));
        N->val = i;
        N->next = NULL;
        C->size = 1;
        C->first = N;
        L[i] = C;
    }

    int m = 0;

    for (int i = 0; i < m; i++) {
        heap_add(i);
    } 

    Set *A;
    Set *B;
    Set *C;
    Set *D;

    while (m < n - 1) {
        Edge *edge = heap_min(my_heap->data);

        if (L[edge->from] != L[edge->to]) {
            graph_add_edge(edge->from - 1, edge->to - 1);
            ++m;

            A = L[edge->from];
            B = L[edge->to];

            if (A->size < B->size) {
                C = A;
                B = D;
            } else {
                C = B;
                D = A;
            }

            Node *P;
            P = C->first;
            Node *u;

            while (P != NULL) {
                int v = P->val;
                L[v] = D;
                // edge->from = v;
                u = P;
                P = P->next;
            }

            u->next = D->first;
            D->first = C->first;
            D->size = D->size + C->size;

            free(C->first);
        }
    }

    return T;
}

int main(void) {
    graph_construction(); // Inicialização da Grafo
    heap_construction(); // Inicialização da Heap

    for (int i = 0; i < 24; i++) {
        graph_add_edge(get_edge_el(edges, i, 0), get_edge_el(edges, i, 1));
    }

    Graph *T = graph_AVG();

    // for (int i = 0; i < n; i++) {
    //     printf("%d : ", i);

    //     for (Node* node = T->v[i]; node->next; node = node->next) {
    //         printf("%d", node->val);
    //         if (node->next->next != NULL) {
    //             printf(", ");
    //         }
    //     }

    //     printf("\n");
    // }

    return 0;
}