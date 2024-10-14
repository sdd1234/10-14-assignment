#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "Heap.h"


//inputData[]�� �Է¹޾� �ִ���Ʈ���� �����ϴ� �Լ�
TreeNode* generateMaxHeapTree(int inputData[], int size) {
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    for (int i = 0; i < size; i++) {
        element item;
        item.key = inputData[i];
        InsertMaxHeapTreeSilent(root, item);
    }
    return root;
}

//�⺻ inputData[]�� ������ Ʈ���� ������� �ʰ� ��带 �߰��ϴ� �Լ�
void InsertMaxHeapTreeSilent(HeapType* h, element item) {
    if (is_full_heap(h)) {
        printf("���� ���� á���ϴ�. ��带 �߰��� �� �����ϴ�.\n");
        return;
    }

    int i = ++(h->heap_size);

    while ((i > 1) && (h->heap[i / 2].key < item.key)) {
        h->heap[i] = h->heap[i / 2];
        i /= 2;
    }

    h->heap[i] = item;
}

//�������� ����Ʈ �ϰ� switch������ ���ϴ� ����� �����ϴ� �Լ�
void runUserInterface(HeapType* root) {
    while (true) {
        for (int i = 0; i < 15; i++) {
            printf("��");
        }
        printf("\n");
        printf("| i   : ����߰�        |\n");
        printf("| d   : ������        |\n");
        printf("| p   : ������ ���     |\n");
        printf("| c   : ����            |\n");
        for (int i = 0; i < 15; i++) {
            printf("��");
        }
        printf("\n�޴� �Է�: ");
        char select;
        scanf_s(" %c", &select);
        switch (select) {
        case 'i':
            printf("�߰��� �� �Է�: ");
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
            printf("�߸��� �Է��Դϴ�.\n");
            break;
        }
    }
}

element delete_heap(HeapType* h) {
    if (is_empty_heap(h)) {
        printf("���� ����ֽ��ϴ�. ������ �� �����ϴ�.\n");
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
        for (int j = 2; j <= h->heap_size + 1; j++) { // 1�� �ε����� ����
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

    // �������� �����ϰ� ����Ʈ
    for (int j = 2; j <= h->heap_size + 1; j++) { // 1�� �ε����� ����
        if (j == parent) {
            printf("%d ", temp.key);
        }
        else {
            printf("%d ", h->heap[j].key);
        }
    }
    printf("\n");

    // ����� 1�� �پ�� ���·� �ٽ� ����Ʈ
    for (int j = 2; j <= h->heap_size; j++) { // 1�� �ε����� ����
        printf("%d ", h->heap[j].key);
    }
    printf("\n��尡 �̵��� Ƚ��: %d\n", move_count);

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

//runUserInterface���� �Է¹��� ���� ���� �߰��ϸ� Ʈ���� �̵��� ����Ʈ �ϴ� �Լ�
void InsertMaxHeapTree(HeapType* h, element item) {
    if (is_full_heap(h)) {
        printf("���� ���� á���ϴ�. ��带 �߰��� �� �����ϴ�.\n");
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
    printf("\n��尡 �̵��� Ƚ��: %d\n", move_count);
}



element find_heap(HeapType* h) {
    return h->heap[1];
}

//���� �������� ����ϴ� �Լ�
void display_heap(HeapType* h) {
    printf("Ʈ�� ������ ���\n");

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
