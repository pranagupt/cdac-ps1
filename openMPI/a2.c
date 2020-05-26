#include <stdio.h>
#include "mpi.h"

#define MASTER_PROCESS 0

int main(int argc,char *argv[])
{
    int my_rank, world_size, val, newnum, sum = 0;
    MPI_Status status;

    MPI_Init(&argc,&argv);
    
    MPI_Comm_size(MPI_COMM_WORLD,&world_size);
    MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);

    if(my_rank == MASTER_PROCESS){

       for(int i = 1 ; i < world_size ; i++){
            MPI_Recv(&val, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
            sum = sum + val;
       }
       printf("sum = %d\n", sum);
    }
    else{
        MPI_Send(&my_rank, 1, MPI_INT, MASTER_PROCESS, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();

}

