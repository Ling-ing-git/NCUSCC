#include <stdio.h>
#include<stdlib.h>
#include<time.h>
// �������������
int* shuzu(int size) {
	clock_t start, end;
    double cpu_time_used;
    srand((unsigned)time(NULL));
    int sui=rand()%100000+90000;
    sui=size;
    printf("��ε�������%d��\n",sui);
    	printf("����д��..."); 
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
        fprintf(fp,"��ε�������%d��\n",sui);
       fprintf(fp,"ԭʼ�Ķ��ǣ�\n");
    for (int i = 0; i < sui; i++) {
        fprintf(fp, "%d ", shu[i]);
    }
    end = clock();
     cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    fprintf(fp,"����ʱ%f��",cpu_time_used);
    fclose(fp);
    printf("д�����\n"); 
    printf("����ʱ%f��\n",cpu_time_used);
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
        return 1; // �����˽���
    } else {
        return 0; // û�з�������
    }
}

int main() {
			int size;
		    int check = 1;
		   	clock_t start, end,sl,el,ab,cd;
		    double cpu_time_used;
		    int *heap =shuzu(size);
		    printf("��ʼִ������...\n");
		        	start = clock();
		        	sl=clock();
		    while (check) {
		        check = 0; // ÿ�ο�ʼ����ǰ������û�н�������
		        // �����һ����Ҷ�ӽڵ㿪ʼ���ϵ�����
		        for (int i = 0; i <=(size / 2)+1 ;i++) {
		            // ������ӽڵ��Ƿ���ڲ��Ƚ�
		            if (2 * (i + 1) - 1 < size && compare(&heap[i], &heap[2 * (i + 1) - 1])) {
		                check = 1; // �����˽�������Ҫ�������
		            }
		            // ������ӽڵ��Ƿ���ڲ��Ƚ�
		            if (2 * (i + 1) < size && compare(&heap[i], &heap[2 * (i + 1)])) {
		                check = 1; // �����˽�������Ҫ�������
		            }
		        }
		    }
			        end = clock();
		     cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		     printf("�������\n����ʱ%f��\n",cpu_time_used);
				 FILE* fp = fopen("Ttest.txt", "a");
				     fprintf(fp,"��ε�������%d��\n",size);
		   			fprintf(fp,"����ʱ%f��\n",cpu_time_used);
		   			puts("����д��...");
		   				start = clock();
			       fprintf(fp,"���ڵĶ��ǣ�\n");
			    for (int i = 0; i < size; i++) {
			        fprintf(fp, "%d ", heap[i]);
			    }
			     end = clock();
		         cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
			    fprintf(fp,"\nд�����\n����ʱ%f��",cpu_time_used);
					printf("�������\n����ʱ%f��\n",cpu_time_used);
		          el = clock();
		          cpu_time_used = ((double) (el - sl)) / CLOCKS_PER_SEC;
					fprintf(fp,"�������\n����ʱ%f��\n",cpu_time_used);
			    fclose(fp);
		        free(heap);
		         el = clock();
		         cpu_time_used = ((double) (el - sl)) / CLOCKS_PER_SEC;
		  			printf("�������\n����ʱ%f��\n",cpu_time_used);
		  			puts("\n");
    return 0;
}
