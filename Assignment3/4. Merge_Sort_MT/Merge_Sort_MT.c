// gcc -pthread merge_sort.c -o merge_sort
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int arr[] = {1024, 2048, 8, 2, 16, 4, 32, 128, 64, 256, 512};


typedef struct node {
    int left;
    int right;
} NODE;

//merge left and right part 
void merge(int left, int right)  
{
		int m, ar, br;
		int s[right - left + 1], sr = 0;	
		
		m = (left + right)/2;  //m - middle
		ar = left; //left value
        br = m+1; //first righ value after mid value
		
		//merging left and right values in increasing order 
        while(ar <= m && br <= right) {
                if (arr[ar] > arr[br])
                        s[sr++] = arr[br++];
                else                    
                        s[sr++] = arr[ar++];
        }
		
		//insert to left part 
        while(ar <= m) {
                s[sr++] = arr[ar++];
        }
		//insert to right part 
        while(br <= right) {
                s[sr++] = arr[br++];
        }
		//storing values
        for (ar = 0; ar < (right-left+1) ; ar++)
                arr[left+ar] = s[ar];

}

void * mergesort(void *a)
{
        NODE *p = (NODE *)a;
        NODE n1, n2;
		//mid point
        int mid = (p->left+p->right)/2;
        pthread_t tid1, tid2; //thread id 1 and 2
        int ret;
		//first half part
        n1.left = p->left;
        n1.right = mid;
		//second half part 
        n2.left = mid+1;
        n2.right = p->right;

        if (p->left >= p->right) return "0";
		// creating 2 threads 
        ret = pthread_create(&tid1, NULL, mergesort, &n1); //creating 1 st thread 
        ret = pthread_create(&tid2, NULL, mergesort, &n2); // 2 nd thread
       //joining them
        pthread_join(tid1, NULL);
        pthread_join(tid2, NULL);
		//merging left and right parts based on two threads
        merge(p->left, p->right);
        pthread_exit(NULL);
}


int main()
{		
		int i, len; //len size of array
		len = sizeof(arr) / sizeof(int); 
		//given values
		printf("Given array: \n");
		for (i = 0; i < len; i++){
                    printf ("%d ", arr[i]);
        }
		printf("\n");
        
		NODE m;
        m.left = 0; //left start array location is 0
        m.right = len - 1; // right finish array location is size - 1
        
		pthread_t tid;
        int ret; 

        ret=pthread_create(&tid, NULL, mergesort, &m); //creating thread
       
        pthread_join(tid, NULL); //joining
		//sorted array
		printf("Sorted array: \n");
        for (i = 0; i < len; i++){
			printf ("%d ", arr[i]);
		}
        printf ("\n");
        return 0;
}