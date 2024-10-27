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
FibonacciHeapNode *FibonacciHeapCreateNode(int kek) {
    FibonacciHeapNode *node = (FibonacciHeapNode *)malloc(sizeof(FibonacciHeapNode));
    //节点在这里被创建
    if (node == NULL) {
        return NULL;
    }
    //这一段毫无意义啊
    node->key = kek;
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
    //这不是纯纯有病啊，不过是不想确认第一个
    if (heap->min == NULL) {
        heap->min = node;
    } else {
        node->right = heap->min->right;
        node->left = heap->min;
        heap->min->right->left = node;
        heap->min->right = node;
        //插入最小的右边，顺序巧妙，层层递进
        if (node->key < heap->min->key) {
            heap->min = node;
            //调整箭头
        }
    }
    heap->size++;
}
void HeapInsert( FibonacciHeapNode *node) {
        node->right = node->right->child->right;
        node->left = node->right->child;
        node->right->child->right->left = node;
        node->right->child->right = node;
        //插入最小的右边，顺序巧妙，层层递进
}
void HeapInsertc( FibonacciHeapNode *node) {
        node->right = node->left->child->right;
        node->left = node->left->child;
        node->left->child->right->left = node;
        node->left->child->right = node;
        //插入最小的右边，顺序巧妙，层层递进
}
FibonacciHeap *FibonacciHeapInit() {
    FibonacciHeap *heap = (FibonacciHeap *)malloc(sizeof(FibonacciHeap));
    if (heap == NULL) {
        return NULL;
    }
    heap->min = NULL;
    heap->size = 0;
    return heap;
}
int hebing(FibonacciHeapNode*a){
	if(a->degree==a->right->degree){
		if(a->key > a->right->key){
			a->parent=a->right;
			if(a->right->child==NULL)
			{
				a->right->child=a;
			}
			else{
				HeapInsert(a);
			}
			a->right->left=NULL;
			a->right->degree=a->right->degree+1;
		}
		else{
		    a->right->parent=a;
			if(a->child==NULL)
			{
				a->child=a->right;
			}
			else{
				HeapInsertc(a->right);
			}
			a->right=NULL;
			a->degree=a->degree+1;
		}
		return 1;  
	}
	return 0;
}
int main() {
	int i ;
    int arr[] = {};
    int n = sizeof(arr) / sizeof(arr[0]);

    scanf("%f",arr);
    printf("Original array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    FibonacciHeap *heap = FibonacciHeapInit();
	for(int yy=0;yy<size;yy) 
	{
		FibonacciHeapNode *node = FibonacciHeapCreateNode(arr[i]);
		if(yy==0){
					FibonacciHeapNode *start;
		            start=node;
		}
		*(node->mark)=yy;
		 FibonacciHeapInsert(heap, node);
	}//chuangzaoyuansu
	//开始合并
	int check=1;
	int count=1;
	FibonacciHeapNode*note;
	note=start;
	while(check) {
		
		check=0;
		count=1;
		while(*(note->mark) < *(note->right->mark)){
			if(hebing(note))
			check=1;
			note=note->right;
			count++;
		}
	}
	
    printf("Sorted array: ");
    note=start;
    printf()
    printf("\n");

    return 0;
}