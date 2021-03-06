#include <mpi.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

void print_matrix(double *M, int row, int col) {

  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++)
      printf("%.0f\t", M[i * col + j]);
    printf("\n");
  }
}

void fprint_matrix(double *M, int row, int col, FILE *fp) {

  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++)
      fprintf(fp, "%.0f\t", M[i * col + j]);
    fprintf(fp, "\n");
  }
}

void swap(double **x, double **y) {

  double *tmp = *x;
  *x = *y;
  *y = tmp;
}

int main(int argc, char *argv[]) {

  int rank = 0;
  int nproc = 1;
  const int N = atoi(argv[1]);
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &nproc);
  // adjust for the rest
  int Nsize = N / nproc;
  int rest = N % nproc;
  if (rank < rest)
    Nsize++;
  int g_idx;
  // create a global index
  if (rank < rest)
    g_idx = rank * Nsize;
  else
    g_idx = (rank - rest) * Nsize + rest * (Nsize + 1);
  // I'm using a buffer to alternate writing and reading
  double *Buff;
  if (rank == 0)
    Buff = (double *)malloc(sizeof(double) * N * Nsize);
  int l_idx = 0;
  double *Mat = (double *)malloc(sizeof(double) * N * Nsize);
  for (int i = g_idx; i < g_idx + Nsize; i++) {
    for (int j = 0; j < N; j++) {
      if (i == j)
        Mat[l_idx * N + j] = 1.;
      else
        Mat[l_idx * N + j] = 0.;
    }
    l_idx++;
  }
  if (rank != 0)
    MPI_Send(Mat, N * Nsize, MPI_DOUBLE, 0, 101, MPI_COMM_WORLD);
  else {
    FILE *f;
    MPI_Request irreq;
    MPI_Status status;
    int size = Nsize;
    int size_print;
    f = fopen("matrix_res.txt", "w");
    // receive the message, write in the meanwhile and exchange the pointers
    for (int i = 1; i < nproc; i++) {
      size_print = size;
      if (i < rest || rest == 0)
        size = Nsize;
      else
        size = Nsize - 1;
      MPI_Irecv(Buff, size * N, MPI_DOUBLE, i, 101, MPI_COMM_WORLD, &irreq);
      if (N < 10)
        print_matrix(Mat, size_print, N);
      else
        fprint_matrix(Mat, size_print, N, f);
      MPI_Wait(&irreq, &status);
      swap(&Mat, &Buff);
    }
    // I have to do another print iteration, to manage the last communication
    if (rest == 0)
      size = Nsize;
    else
      size = Nsize - 1;
    if (N < 10)
      print_matrix(Mat, size, N);
    else
      fprint_matrix(Mat, size, N, f);

    if (N > 10)
      fclose(f);
  }
  free(Mat);
  if (rank == 0)
    free(Buff);
  MPI_Finalize();

  return 0;
}
