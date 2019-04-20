#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <mpi.h>

#define N 10000000


double f(double x){
    return 1/(1+x*x);
} 


int main( int argc, char * argv[] ) {
    double tstart = omp_get_wtime();
    int imesg = 0;
    int rank = 0;
    int npes = 1; 
    double global;
    double h = 1./N;
    MPI_Init( &argc, &argv );
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    MPI_Comm_size( MPI_COMM_WORLD, &npes );
    
    int start = N/npes * rank;
    int end =  N/npes * (rank + 1);
    int i;
    double local=0;
    for(i = start; i < end; i++){
        double x_i = i*h;
        local += f(x_i);
        }

    MPI_Reduce(&local, &global, 1, MPI_DOUBLE, MPI_SUM, npes-1, MPI_COMM_WORLD);
    double tend = omp_get_wtime();
    if(rank == 0)
        printf("time=%fsec \n",tend-tstart);
    if(rank == npes - 1)
        MPI_Send(&global, 1, MPI_DOUBLE, 0, 101, MPI_COMM_WORLD);
    if(rank == 0){
        MPI_Recv(&global, 1 , MPI_DOUBLE, npes-1, 101, MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        printf("pi=%f \n",h*global*4);
    }    

    MPI_Finalize();
    
    return 0;
}