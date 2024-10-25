#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct FibonacciHeapNode {
    int key;
    int degree;
    struct FibonacciHeapNode *parent;
    struct FibonacciHeapNode *child;
    struct FibonacciHeapNode *left;
    struct FibonacciHeapNode *right;
    int mark;
} FibonacciHeapNode;

typedef struct FibonacciHeap {
    FibonacciHeapNode *min;
    int size;
} FibonacciHeap;

// 函数声明
FibonacciHeap *FibonacciHeapInit();
FibonacciHeapNode *FibonacciHeapCreateNode(int key);
void FibonacciHeapInsert(FibonacciHeap *heap, FibonacciHeapNode *node);
FibonacciHeapNode *FibonacciHeapExtractMin(FibonacciHeap *heap);
void FibonacciHeapConsolidate(FibonacciHeap *heap);
void FibonacciHeapLink(FibonacciHeap *heap, FibonacciHeapNode *y, FibonacciHeapNode *x);
void FibonacciHeapFreeNode(FibonacciHeapNode *node);
void FibonacciHeapFree(FibonacciHeap *heap);

// 初始化斐波那契堆
FibonacciHeap *FibonacciHeapInit() {
    FibonacciHeap *heap = (FibonacciHeap *)malloc(sizeof(FibonacciHeap));
    if (heap == NULL) {
        return NULL;
    }
    heap->min = NULL;
    heap->size = 0;
    return heap;
}

// 创建一个斐波那契堆节点
FibonacciHeapNode *FibonacciHeapCreateNode(int key) {
    FibonacciHeapNode *node = (FibonacciHeapNode *)malloc(sizeof(FibonacciHeapNode));
    if (node == NULL) {
        return NULL;
    }
    node->key = key;
    node->degree = 0;
    node->parent = NULL;
    node->child = NULL;
    node->left = node;
    node->right = node;
    node->mark = 0;
    return node;
}

// 插入节点
void FibonacciHeapInsert(FibonacciHeap *heap, FibonacciHeapNode *node) {
    node->left = node->right = node;
    if (heap->min == NULL) {
        heap->min = node;
    } else {
        node->right = heap->min->right;
        node->left = heap->min;
        heap->min->right->left = node;
        heap->min->right = node;
        if (node->key < heap->min->key) {
            heap->min = node;
        }
    }
    heap->size++;
}

// 找到最小节点
FibonacciHeapNode *FibonacciHeapFindMin(FibonacciHeap *heap) {
    return heap->min;
}

// 提取最小节点
FibonacciHeapNode *FibonacciHeapExtractMin(FibonacciHeap *heap) {
    if (heap == NULL || heap->min == NULL) return NULL;

    FibonacciHeapNode *minNode = heap->min;
    FibonacciHeapNode *child = minNode->child;

    // 将最小节点的所有子节点添加到根列表中
    while (child != NULL) {
        FibonacciHeapNode *nextChild = child->right;
        child->parent = NULL;
        child->left = heap->min;
        child->right = heap->min->right;
        heap->min->right = child;
        child->right->left = child;
        child = nextChild;
    }

    // 从根列表中移除最小节点
    minNode->left->right = minNode->right;
    minNode->right->left = minNode->left;
    if (minNode == minNode->right) {
        heap->min = NULL;
    } else {
        heap->min = minNode->right;
        FibonacciHeapConsolidate(heap);
    }

    heap->size--;
    return minNode;
}

// 辅助函数：链接两个节点
void FibonacciHeapLink(FibonacciHeap *heap, FibonacciHeapNode *y, FibonacciHeapNode *x) {
    y->left->right = y->right;
    y->right->left = y->left;
    y->parent = x;
    y->mark = 0;

    if (x->child == NULL) {
        x->child = y;
        y->left = y;
        y->right = y;
    } else {
        y->left = x->child;
        y->right = x->child->right;
        x->child->right = y;
        y->right->left = y;
    }
    x->degree++;
}

// 辅助函数：合并具有相同度数的根节点
void FibonacciHeapConsolidate(FibonacciHeap *heap) {
    int D = heap->size;
    FibonacciHeapNode **A = (FibonacciHeapNode **)malloc((D + 1) * sizeof(FibonacciHeapNode *));
    for (int i = 0; i <= D; i++) {
        A[i] = NULL;
    }

    FibonacciHeapNode *w = heap->min;
    FibonacciHeapNode *x = NULL;
    FibonacciHeapNode *y = NULL;
    FibonacciHeapNode *z = NULL;

    while (w != NULL) {
        int d = w->degree;
        while (A[d] != NULL) {
            y = A[d];
            if (w->key > y->key) {
                FibonacciHeapNode *temp = w;
                w = y;
                y = temp;
            }
            FibonacciHeapLink(heap, y, w);
            A[d] = NULL;
            d++;
        }
        A[d] = w;
        x = w;
        w = w->right;
        if (w == x) break;
    }

    heap->min = NULL;
    for (int i = 0; i <= D; i++) {
        if (A[i] != NULL) {
            A[i]->left = A[i];
            A[i]->right = A[i];
            if (heap->min == NULL || A[i]->key < heap->min->key) {
                heap->min = A[i];
            }
        }
    }

    free(A);
}

// 释放一个节点
void FibonacciHeapFreeNode(FibonacciHeapNode *node) {
    if (node == NULL) return;
    FibonacciHeapNode *child = node->child;
    while (child != NULL) {
        FibonacciHeapNode *nextChild = child->right;
        FibonacciHeapFreeNode(child);
        child = nextChild;
    }
    free(node);
}

// 释放斐波那契堆
void FibonacciHeapFree(FibonacciHeap *heap) {
    if (heap == NULL) return;
    FibonacciHeapNode *x = heap->min;
    if (x != NULL) {
        do {
            FibonacciHeapNode *next = x->right;
            FibonacciHeapFreeNode(x);
            x = next;
        } while (x != heap->min);
    }
    free(heap);
}

// 斐波那契堆排序
void FibonacciHeapSort(int *arr, int n) {
    FibonacciHeap *heap = FibonacciHeapInit();
    if (heap == NULL) {
        fprintf(stderr, "Failed to initialize heap\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        FibonacciHeapNode *node = FibonacciHeapCreateNode(arr[i]);
        FibonacciHeapInsert(heap, node);
    }

    for (int i = 0; i < n; i++) {
        FibonacciHeapNode *minNode = FibonacciHeapExtractMin(heap);
        if (minNode != NULL) {
            arr[i] = minNode->key;
            free(minNode);
        }
    }

    FibonacciHeapFree(heap);
}

int main() {
    int arr[] = {10, 20, 5, 3, 40, 25};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    FibonacciHeapSort(arr, n);

    printf("Sorted array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}