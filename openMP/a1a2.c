#include <stdio.h>
#include <omp.h>

int main(){
    #pragma omp parallel
    {
        int ID = omp_get_thread_num();
        printf("hello world in thread %d\n", ID);
    }
    printf("\n");
}