#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "Heap.h"


//inputData[]를 입력받아 최대힙트리를 생성하는 함수
TreeNode* generateMaxHeapTree(int inputData[], int size) {
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    for (int i = 0; i < size; i++) {
        element item;
        item.key = inputData[i];
        InsertMaxHeapTreeSilent(root, item);
    }
    return root;
}

//기본 inputData[]로 생성한 트리를 출력하지 않고 노드를 추가하는 함수
void InsertMaxHeapTreeSilent(HeapType* h, element item) {
    if (is_full_heap(h)) {
        printf("힙이 가득 찼습니다. 노드를 추가할 수 없습니다.\n");
        return;
    }

    int i = ++(h->heap_size);

    while ((i > 1) && (h->heap[i / 2].key < item.key)) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }

    h->heap[i] = item;
}

//선택지를 프린트 하고 switch문으로 원하는 기능을 구현하는 함수
void runUserInterface(HeapType* root) {
    while (true) {
        for (int i = 0; i < 15; i++) {
            printf("ㅡ");
        }
        printf("\n");
        printf("| i   : 노드추가        |\n");
        printf("| d   : 노드삭제        |\n");
        printf("| p   : 레벨별 출력     |\n");
        printf("| c   : 종료            |\n");
        for (int i = 0; i < 15; i++) {
            printf("ㅡ");
        }
        printf("\n메뉴 입력: ");
        char select;
        scanf_s(" %c", &select);
        switch (select) {
        case 'i':
            printf("추가할 값 입력: ");
            int insert;
            scanf_s("%d", &insert);
            element item;
            item.key = insert;
            InsertMaxHeapTree(root, item);
            break;
        case 'd':
            delete_heap(root);
            break;
        case 'p':
            display_heap(root);
            break;
        case 'c':
            return;
        default:
            printf("잘못된 입력입니다.\n");
            break;
        }
    }
}

element delete_heap(HeapType* h) {
    if (is_empty_heap(h)) {
        printf("힙이 비어있습니다. 삭제할 수 없습니다.\n");
        element empty = { 0 };
        return empty;
    }

    int parent, child;
    element item, temp;
    int move_count = 0;

    item = h->heap[1];
    temp = h->heap[h->heap_size];
    (h->heap_size)--;

    for (parent = 1, child = 2; child <= h->heap_size; parent = child, child *= 2) {
        if ((child < h->heap_size) && (h->heap[child].key < h->heap[child + 1].key)) {
            child++;
        }
        for (int j = 2; j <= h->heap_size + 1; j++) { // 1번 인덱스는 제외
            if (j == child) {
                printf("%d ", temp.key);
            }
            else {
                printf("%d ", h->heap[j].key);
            }
        }
        printf("\n");

        if (temp.key >= h->heap[child].key) break;
        h->heap[parent] = h->heap[child];
        move_count++;
    }
    h->heap[parent] = temp;

    // 마지막을 제거하고 프린트
    for (int j = 2; j <= h->heap_size + 1; j++) { // 1번 인덱스는 제외
        if (j == parent) {
            printf("%d ", temp.key);
        }
        else {
            printf("%d ", h->heap[j].key);
        }
    }
    printf("\n");

    // 사이즈가 1개 줄어든 상태로 다시 프린트
    for (int j = 2; j <= h->heap_size; j++) { // 1번 인덱스는 제외
        printf("%d ", h->heap[j].key);
    }
    printf("\n노드가 이동된 횟수: %d\n", move_count);

    return item;
}


HeapType* create_heap() {
    return (HeapType*)malloc(sizeof(HeapType));
}

void init_heap(HeapType* h) {
    h->heap_size = 0;
}

void destroy_heap(HeapType* h) {
    free(h);
}

int is_empty_heap(HeapType* h) {
    return (h->heap_size == 0);

}

int is_full_heap(HeapType* h) {
    return (h->heap_size == (MAX_SIZE - 1));

}

//runUserInterface에서 입력받은 값을 힙에 추가하며 트리의 이동을 프린트 하는 함수
void InsertMaxHeapTree(HeapType* h, element item) {
    if (is_full_heap(h)) {
        printf("힙이 가득 찼습니다. 노드를 추가할 수 없습니다.\n");
        return;
    }

    int i = ++(h->heap_size);
    int move_count = 0;

    while ((i > 1) && (h->heap[i / 2].key < item.key)) {
        for (int j = 1; j <= h->heap_size; j++) {
            if (j == i) {
                printf("%d ", item.key);
            }
            else {
                printf("%d ", h->heap[j].key);
            }
        }
        printf("\n");

        h->heap[i] = h->heap[i / 2];
        i /= 2;
        move_count++;
    }

    h->heap[i] = item;

    for (int j = 1; j <= h->heap_size; j++) {
        if (j == i) {
            printf("%d ", item.key);
        }
        else {
            printf("%d ", h->heap[j].key);
        }
    }
    printf("\n노드가 이동된 횟수: %d\n", move_count);
}



element find_heap(HeapType* h) {
    return h->heap[1];
}

//힙을 레벨별로 출력하는 함수
void display_heap(HeapType* h) {
    printf("트리 레벨별 출력\n");

    int index = 1;
    int level = 1;

    while (index <= h->heap_size) {
        printf("[%d] ", level);

        int nodes_in_level = 1 << (level - 1);
        for (int i = 0; i < nodes_in_level && index <= h->heap_size; i++) {
            printf("%02d ", h->heap[index++].key);
        }
        printf("\n");
        level++;
    }
    printf("\n");
}
