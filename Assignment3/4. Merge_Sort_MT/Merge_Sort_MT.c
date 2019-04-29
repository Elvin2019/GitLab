#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define NOTHREADS 2


int arr[] = {1024, 2048, 8, 2, 16, 4, 32, 128, 64, 256, 512};

typedef struct node {
    int left;
    int right;
} NODE;

void merge(int left, int right)  
{
		int m, ar, br;
		int s[right - left + 1], sr = 0;	
		
		m = (left + right)/2;  //m - middle
		ar = left;
        br = m+1;
		
        while(ar <= m && br <= right) {
                if (arr[ar] > arr[br])
                        s[sr++] = arr[br++];
                else                    
                        s[sr++] = arr[ar++];
        }

        while(ar <= m) {
                s[sr++] = arr[ar++];
        }

        while(br <= right) {
                s[sr++] = arr[br++];
        }

        for (ar = 0; ar < (right-left+1) ; ar++)
                arr[left+ar] = s[ar];

}

void * mergesort(void *a)
{
        NODE *p = (NODE *)a;
        NODE n1, n2;
        int mid = (p->left+p->right)/2;
        pthread_t tid1, tid2;
        int ret;

        n1.left = p->left;
        n1.right = mid;

        n2.left = mid+1;
        n2.right = p->right;

        if (p->left >= p->right) return "0";

        ret = pthread_create(&tid1, NULL, mergesort, &n1);
      

        ret = pthread_create(&tid2, NULL, mergesort, &n2);
       
        pthread_join(tid1, NULL);
        pthread_join(tid2, NULL);

        merge(p->left, p->right);
        pthread_exit(NULL);
}


int main()
{
		
		int i, len;
		len = sizeof(arr) / sizeof(int); 
		printf("Given array: \n");
		for (i = 0; i < len; i++){
                    printf ("%d ", arr[i]);
        }
		printf("\n");
        NODE m;
        m.left = 0;
        m.right = len - 1;
        
		pthread_t tid;
        int ret; 

        ret=pthread_create(&tid, NULL, mergesort, &m);
       
	   
        pthread_join(tid, NULL);
		printf("Sorted array: \n");
        for (i = 0; i < len; i++)
                    printf ("%d ", arr[i]);

        printf ("\n");

        // pthread_exit(NULL);
        return 0;
}