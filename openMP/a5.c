#include <stdio.h>
#include <omp.h>

int main(){
	int i,j;
	int sum=0;
#pragma omp parallel for
	for (i=0;i<100;i++) 
	for (j=0;j<100;j++) {
		sum++;
	}
    printf("correct value: 10000, value obtained: %d\n", sum);
    return 0;
}