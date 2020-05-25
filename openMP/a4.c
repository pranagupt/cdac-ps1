#include <stdio.h>
#include <omp.h>
#define vector_size 10
#define mat_height 5
int main(){
	int vectr[vector_size],mat[mat_height][vector_size];
    for (int i = 0; i<vector_size; i++)
        vectr[i] = i;

    for(int i = 0; i<mat_height;i++){
        for(int j = 0; j<vector_size; j++)
            mat[i][j] = i + j;
    }

    printf("vector:\n");
    for(int i = 0; i<vector_size;i++){
        printf("%d \n",vectr[i]);
    }
    printf("\n");

    printf("matrice:\n");
    for(int i = 0; i<mat_height;i++){
        for(int j = 0; j<vector_size; j++)
            printf("%d ",mat[i][j]);
        printf("\n");
    }
    printf("\n");
    int i;
    int prod[mat_height] = {0};
    #pragma omp parallel for private(i)
	for(int j = 0; j< mat_height; j++){
        for(int i = 0; i< vector_size; i++){
            prod[j]+=vectr[i]*mat[j][i];
        }
    }

    printf("product:\n");
    for(int i = 0; i<mat_height;i++){
        printf("%d \n",prod[i]);
    }
    printf("\n");
    return 0;
}