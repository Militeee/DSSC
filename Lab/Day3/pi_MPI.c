#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <mpi.h>

<<<<<<< HEAD
#define N 10000000


double f(double x){
    return 1/(1+x*x);
=======
#define N 10000000000


double f(double x){
  return 1/(1+x*x);
>>>>>>> 1487dbbc03113717227c67ae5d381c90346e61d4
} 


int main( int argc, char * argv[] ) {
<<<<<<< HEAD
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
=======
  double tstart = omp_get_wtime();
  int imesg = 0;
  int rank = 0;
  int npes = 1; 
  double global;
  double h = 1./N;
  MPI_Init( &argc, &argv );
  MPI_Comm_rank( MPI_COMM_WORLD, &rank );
  MPI_Comm_size( MPI_COMM_WORLD, &npes );
    
  long int start = N/npes * rank;
  long int end;
  if(rank + 1 == npes && N%npes != 0)  end = N%npes + N/npes * (rank+1);
  else end =  N/npes * (rank + 1);
  long int i;
  double local=0;
  for(i = start; i < end; i++){
    double x_i = i*h+h/2;
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
>>>>>>> 1487dbbc03113717227c67ae5d381c90346e61d4
}
