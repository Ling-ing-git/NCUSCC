#include <stdio.h>
#include<stdlib.h>
#include<time.h>
// 制造随机的数组
int* shuzu(int size) {
	clock_t start, end;
    double cpu_time_used;
    srand((unsigned)time(NULL));
    int sui=100000;
    sui=size;
    printf("这次的数据有%d个\n",sui);
    	printf("正在写入..."); 
    	start = clock();
    int* shu = (int*)malloc(sui * sizeof(int));
    for (int i = 0; i < sui; i++) {
        shu[i] = rand() % 10000;
    }
    printf("\n");
    FILE* fp = fopen("text.txt", "a");
    if (fp == NULL) {
        perror("Error opening file");
        free(shu);
        return NULL;
    }
        fprintf(fp,"这次的数据有%d个\n",sui);
       fprintf(fp,"原始的堆是：\n");
    for (int i = 0; i < sui; i++) {
        fprintf(fp, "%d ", shu[i]);
    }
    end = clock();
     cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    fprintf(fp,"共用时%f秒",cpu_time_used);
    fclose(fp);
    printf("写入完成\n"); 
    printf("共用时%f秒\n",cpu_time_used);
    return shu;
}

void exchange(int *number1, int *number2) {
    int temp = *number1;
    *number1 = *number2;
    *number2 = temp;
}

int compare(int *one, int *two) {
    if (*one < *two) {
        exchange(one, two);
        return 1; // 发生了交换
    } else {
        return 0; // 没有发生交换
    }
}

int main() {
			int size;
		    int check = 1;
		   	clock_t start, end,sl,el,ab,cd;
		    double cpu_time_used;
		    int *heap =shuzu(size);
		    printf("开始执行排序...\n");
		        	start = clock();
		        	sl=clock();
		    while (check) {
		        check = 0; // 每次开始调整前，假设没有交换发生
		        // 从最后一个非叶子节点开始向上调整堆
		        for (int i = 0; i <=(size / 2)+1 ;i++) {
		            // 检查左子节点是否存在并比较
		            if (2 * (i + 1) - 1 < size && compare(&heap[i], &heap[2 * (i + 1) - 1])) {
		                check = 1; // 发生了交换，需要继续检查
		            }
		            // 检查右子节点是否存在并比较
		            if (2 * (i + 1) < size && compare(&heap[i], &heap[2 * (i + 1)])) {
		                check = 1; // 发生了交换，需要继续检查
		            }
		        }
		    }
			        end = clock();
		     cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		     printf("排序完成\n共用时%f秒\n",cpu_time_used);
				 FILE* fp = fopen("Ttest.txt", "a");
				     fprintf(fp,"这次的数据有%d个\n",size);
		   			fprintf(fp,"共用时%f秒\n",cpu_time_used);
		   			puts("正在写入...");
		   				start = clock();
			       fprintf(fp,"现在的堆是：\n");
			    for (int i = 0; i < size; i++) {
			        fprintf(fp, "%d ", heap[i]);
			    }
			     end = clock();
		         cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
			    fprintf(fp,"\n写入完成\n共用时%f秒",cpu_time_used);
					printf("排序完成\n共用时%f秒\n",cpu_time_used);
		          el = clock();
		          cpu_time_used = ((double) (el - sl)) / CLOCKS_PER_SEC;
					fprintf(fp,"运行完成\n共用时%f秒\n",cpu_time_used);
			    fclose(fp);
		        free(heap);
		         el = clock();
		         cpu_time_used = ((double) (el - sl)) / CLOCKS_PER_SEC;
		  			printf("运行完成\n共用时%f秒\n",cpu_time_used);
		  			puts("\n");
    return 0;
}