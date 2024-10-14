#pragma once
#define MAX_SIZE 100

typedef struct {
	int key;
}element;

typedef struct {
	element heap[MAX_SIZE];
	int heap_size;
}HeapType;

typedef struct tree_node {
	int data;
	struct tree_node* left, * right;
} TreeNode;

extern TreeNode* generateMaxHeapTree(int* inputData, int size);
extern void runUserInterface(TreeNode* root);
extern HeapType* create_heap();
extern void init_heap(HeapType* h);
extern void destroy_heap(HeapType* h);
extern int is_empty_heap(HeapType* h);
extern int is_full_heap(HeapType* h);
extern void InsertMaxHeapTree(HeapType* h, element item);
extern element delete_heap(HeapType* h);
extern element find_heap(HeapType* h);
extern void display_heap(HeapType* h);
extern void InsertMaxHeapTreeSilent(HeapType* h, element item);