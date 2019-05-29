#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#define N 100
#define RIGHT(proc, nproc) (proc - 1 + nproc) % nproc
#define LEFT(proc, nproc) (proc + 1 + nproc) % nproc

void swap(int** x, int** y){
  int* tmp = *x;
  *x = *y;
  *y = tmp;
}

int main(int argc, char *argv[]) {
  int rank = 0;
  int npes = 1;
  int *my = (int *)malloc(sizeof(int) * N);
  int *sum = (int *)calloc(sizeof(int), N);
  int *recv = (int *)malloc(sizeof(int) * N);
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &npes);
  for (int i = 0; i < N; i++) {
    my[i] = rank;
  }
  MPI_Request request;
  for (int j = 0; j < npes - 1; j++) {
    // sendin and exploting the time to do the summation
    MPI_Isend(my, N, MPI_INT, LEFT(rank, npes), 101, MPI_COMM_WORLD, &request);
    for (int i = 0; i < N; i++) {
      sum[i] += my[i];
    }
    MPI_Recv(recv, N, MPI_INT, RIGHT(rank, npes), 101, MPI_COMM_WORLD,
             MPI_STATUS_IGNORE);
    MPI_Wait(&request, MPI_STATUS_IGNORE);
    // change the pointers to propagate the sum
    swap(&my,&recv);
  }
  // doing the last sum
  for (int i = 0; i < N; i++) {
    sum[i] += my[i];
  }
  if (rank < 6)
    printf("sum is %d\n", sum[0]);
  MPI_Finalize();
  free(my);
  free(sum);
  free(recv);
  return 0;
}
