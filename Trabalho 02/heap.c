#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int m = 20;

typedef struct heap {
	double *data;
	int size;
} Heap;

Heap *my_heap;

// Assinatura dos métodos de manipulações da Heap

void heap_construction(void);

void heap_shiftup(int node_index);

void heap_add(double node);

void heap_shiftdown(int node_index);

void heap_remove_min(void);

double heap_min(double *arr);

void print_arr(double *arr);

// Implementações dos métodos de manipulações da Heap

void heap_construction(void) {
	my_heap = (Heap*)malloc(sizeof(Heap*));
      my_heap->data = (double*)malloc(sizeof(double) * m);

	int i = 0;
	for (int i; i < m; i++) {
		my_heap->data[i] = 9999999999999.0;
	}

      my_heap->size = 0;
}

void heap_shiftup(int node_index) {
	int parent_index, tmp;

      // Concertando a heap
      if (node_index != 0) {
            parent_index = (int)(node_index / 2);
            if (my_heap->data[parent_index] > my_heap->data[node_index]) {
                  tmp = my_heap->data[parent_index];
                  my_heap->data[parent_index] = my_heap->data[node_index];
                  my_heap->data[node_index] = tmp;
                  heap_shiftup(parent_index);
            }
      }
}

void heap_add(double node) {
	// Adicionando noh no fim do vetor
	my_heap->size++;
	my_heap->data[my_heap->size - 1] = node;

	int current_index = my_heap->size - 1;

	heap_shiftup(current_index);
}

void heap_shiftdown(int node_index) {
      int left_child_index, right_child_index, min_index, tmp;
      left_child_index = node_index * 2;
      right_child_index = node_index * 2 + 1;

      if (right_child_index >= my_heap->size) {
            if (left_child_index >= my_heap->size) {
                  return;
            } else {
                  min_index = left_child_index;
            }
      } else {
            if (my_heap->data[left_child_index] <= my_heap->data[right_child_index]) {
                  min_index = left_child_index;
            } else {
                  min_index = right_child_index;
            }
      }

      if (my_heap->data[node_index] > my_heap->data[min_index]) {
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

double heap_min(double *arr) {
      return arr[0];
}

void print_arr(double *arr) {
      for (int i = 0; i < m; i++)
            printf("%lf %d\n", arr[i], i);
}

int main() {
      heap_construction(); // Inicialização da Heap

      int arr[] = {3, 2, 4, 1, 6, 11, 8, 12, 16, 14, 7, 0, 13, 19, 18, 9, 17, 15, 5, 10};

      for (int i = 0; i < m; i++) {
            heap_add(arr[i]);
      }

      for (int i = 0; i < m; i++) {
            printf("%lf\n", heap_min(my_heap->data));
            heap_remove_min();
      }

	return 0;
}
