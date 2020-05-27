#include <stdio.h>
#include "mpi.h"

#define NUMBER_OF_THREADS 10
#define MASTER_PROCESS 0
int main(int argc,char *argv[])
{
    int my_rank, world_size, val;
    MPI_Status status;
    int arr[NUMBER_OF_THREADS] = {23,12,73,53,4,32,234,36,43,93};
    

    MPI_Init(&argc,&argv);
    
    MPI_Comm_size(MPI_COMM_WORLD,&world_size);
    MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);

    if(my_rank == MASTER_PROCESS){
        printf("Array: ");
        for(int i = 0; i < NUMBER_OF_THREADS; i++)
            printf(" %d", arr[i]);
        printf("\n");
    }
    int current_sum=0;

    if(world_size != NUMBER_OF_THREADS){
        printf("Please set number of threads as %d", NUMBER_OF_THREADS);
        return -1;
    }
    
    if(my_rank == MASTER_PROCESS){
        current_sum = arr[0];
        for (int i = 1; i < NUMBER_OF_THREADS; i++){
            MPI_Send(&current_sum, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Recv(&current_sum, 1, MPI_INT, i, 1, MPI_COMM_WORLD, &status);
            arr[i] = current_sum;
        }
        // MPI_Send(&arr[my_rank], 1, MPI_INT, my_rank+1, 0, MPI_COMM_WORLD);
    }
    // else if(my_rank == NUMBER_OF_THREADS-1){
    //     MPI_Recv(&val, 1, MPI_INT, my_rank-1, 0, MPI_COMM_WORLD, &status);
    //     arr[my_rank] += val;
    // }
    else{
        MPI_Recv(&val, 1, MPI_INT, MASTER_PROCESS, 0, MPI_COMM_WORLD, &status);
        arr[my_rank] += val;
        MPI_Send(&arr[my_rank], 1, MPI_INT, MASTER_PROCESS, 1, MPI_COMM_WORLD);
    }


    if(my_rank == MASTER_PROCESS){
        printf("Prefix calculation: ");
        for(int i = 0; i < NUMBER_OF_THREADS; i++)
            printf(" %d", arr[i]);
        printf("\n");
    }
    MPI_Finalize();
    
}

