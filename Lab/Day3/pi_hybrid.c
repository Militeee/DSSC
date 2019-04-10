#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <mpi.h>

#define N 10000000000


double f(double x){
  return 1/(1+x*x);
} 


int main( int argc, char * argv[] ) {
  double tstart = omp_get_wtime();
  int imesg = 0;
  int rank = 0;
  int npes = 1;
  int req[100]; 
  double global;
  int threads = atoi(argv[1]);
  double h = 1./N;
  MPI_Init_thread( &argc, &argv, MPI_THREAD_FUNNELED, req );
  MPI_Comm_rank( MPI_COMM_WORLD, &rank );
  MPI_Comm_size( MPI_COMM_WORLD, &npes );
    
  long int start = N/npes * rank;
  long int end;
  if(rank + 1 == npes && N%npes != 0) end = N%npes + N/npes * (rank+1);
  else end = N/npes * (rank + 1);
  long int i;
  double local=0;  
  #pragma omp parallel num_threads(threads) 
{
  double local2 = 0;
  //printf("Hi from thread %d of process %d\n", omp_get_thread_num(), rank);
  #pragma omp for
  for(i = start; i < end; i++){
    double x_i = i*h+h/2;
    local2 += f(x_i);
  }
  #pragma omp atomic 
  local += local2;
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
