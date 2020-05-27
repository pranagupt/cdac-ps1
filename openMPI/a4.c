#include <stdio.h>
#include "mpi.h"
#include <string.h>
#include <ctype.h>

#define MASTER_PROCESS 0

int main(int argc,char *argv[])
{
    int my_rank, world_size, sum = 0;
    MPI_Status status;
    char sentence[] = "Hello, this is a sentence"; 
    int len = strlen(sentence);
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD,&world_size);
    MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
    
    
    if(my_rank == MASTER_PROCESS){

       for(int i = 0 ; i < len ; i++){
            MPI_Recv(&sentence[i], 1, MPI_CHAR, MPI_ANY_SOURCE, i, MPI_COMM_WORLD, &status);
       }
        printf("%s\n", sentence);

    }
    else{
        for(int j = my_rank-1; j < len; j+=(world_size-1)){
            sentence[j] = toupper(sentence[j]);
            MPI_Send(&sentence[j], 1, MPI_CHAR, MASTER_PROCESS, j, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();

}

