#include <stdio.h>
#include <mpi.h>

#define length 4

void transpose(int b[][length], int starting_row){
    int temp;
    for (int i = 1; i < length; i++){
        for (int j = 0;j < i; j++){
            temp = b[starting_row+i][j];
            b[starting_row + i][j] = b[starting_row + j][i];
            b[starting_row + j][i] = temp;
        }
    }
}

int main (int argc, char *argv[]){
    int a[24][4];
    int b[24][4];

    int world_size, my_rank;

    MPI_Init (&argc, &argv);
    MPI_Comm_size (MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank (MPI_COMM_WORLD, &my_rank);

  
    if (world_size != 6){
        if (my_rank == 0){
            printf ("Please set number of processes as 6\n");
            return 1;
        }
    }

    //initialising matrix in each thread
    for (int i = 0; i < 24; i++)
        for (int j = 0; j < 6; j++)
            a[i][j] = i + 2*j + 4*my_rank;


    MPI_Alltoall (&a[0][0], 4 * 4, MPI_INT, &b[0][0], 4 * 4, MPI_INT, MPI_COMM_WORLD);

    //transposing all 4x4 matrices which were sent over MPI to other threads
    for (int i = 0; i < 6; i++)
        transpose (b, 4*i);


    MPI_Finalize ();
    return 0;
}
