#include <stdio.h>
#include <stdlib.h>
#include "Heap.h"

main() {
	int inputData[] = { 90, 89, 70, 36, 75, 63, 65, 21, 18, 15 };
	int size = sizeof(inputData) / sizeof(int);

	TreeNode* root = generateMaxHeapTree(inputData, size);


	runUserInterface(root);

	free(root);
	return 0;
}