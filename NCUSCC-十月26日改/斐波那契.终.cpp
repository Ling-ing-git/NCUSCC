#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

FibonacciHeapNode *FibonacciHeapCreateNode(int key) {
    FibonacciHeapNode *node = (FibonacciHeapNode *)malloc(sizeof(FibonacciHeapNode));
    if (node) {
        node->key = key;
        node->degree = 0;
        node->parent = NULL;
        node->child = NULL;
        node->left = node;
        node->right = node;
        node->mark = 0;
    }
    return node;
}

void FibonacciHeapInsert(FibonacciHeap *heap, FibonacciHeapNode *node) {
    node->left = node->right = node;
    if (!heap->min) {
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

FibonacciHeap *FibonacciHeapInit() {
    FibonacciHeap *heap = (FibonacciHeap *)malloc(sizeof(FibonacciHeap));
    if (heap) {
        heap->min = NULL;
        heap->size = 0;
    }
    return heap;
}

void PrintFibonacciHeap(FibonacciHeap *heap, FILE *file) {
    if (!heap || !heap->min) return;
    FibonacciHeapNode *x = heap->min;
    do {
        fprintf(file, "Key: %d, Degree: %d, Mark: %d\n", x->key, x->degree, x->mark);
        x = x->right;
    } while (x != heap->min);
}

int main() {
    int n = 1000000; // 数组大小
    int *arr = (int *)malloc(n * sizeof(int)); // 分配数组

    if (arr == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    srand((unsigned)time(NULL)); // 初始化随机数生成器
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 10000; // 生成随机数
    }

    // 打开文件以写入数据
    FILE *file = fopen("tst.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        free(arr);
        return 1;
    }

    // 写入原始数组到文件
    for (int i = 0; i < 10 && i < n; i++) { // 打印前10个数作为示例
        fprintf(file, "%d ", arr[i]);
    }
    fprintf(file, "\n...\n");

    FibonacciHeap *heap = FibonacciHeapInit();
    for (int i = 0; i < n; i++) {
        FibonacciHeapNode *node = FibonacciHeapCreateNode(arr[i]);
        node->mark = i;
        FibonacciHeapInsert(heap, node);
    }

    // 写入斐波那契堆到文件
    PrintFibonacciHeap(heap, file);

    // 清理斐波那契堆和数组
    // 注意：实际应用中需要编写代码来释放斐波那契堆中的每个节点以及堆本身占用的内存
    free(arr);
    // free(heap); // 需要更详细的内存清理逻辑

    // 关闭文件
    fclose(file);
    return 0;
}