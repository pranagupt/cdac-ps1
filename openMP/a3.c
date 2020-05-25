#include <stdio.h>
#include <omp.h>
#define vector_size 10
int main(){
	int vectr[vector_size],scalar = 5;
    for (int i = 0; i<vector_size; i++)
        vectr[i] = i;

    printf("before:\n");
    for(int i = 0; i<vector_size;i++){
        printf("%d ",vectr[i]);
    }
    printf("\n");

    #pragma omp parallel for
	for(int i = 0; i< vector_size; i++){
        vectr[i] += scalar;
    }

    printf("after adding %d:\n", scalar);
    for(int i = 0; i<vector_size;i++){
        printf("%d ",vectr[i]);
    }
    printf("\n");
    return 0;
}