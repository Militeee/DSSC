#include <math.h>
#include <stdio.h>

#define BDIM 1024

__global__ void fast_transpose(double *a, double *b, int N) {
  // buffer
  __shared__ double buffer[BDIM];
  int y = blockIdx.y * blockDim.y + threadIdx.y;
  int x = blockIdx.x * blockDim.x + threadIdx.x;
  // doing the transposition on the shared memory
  buffer[threadIdx.y * blockDim.x + threadIdx.x] = a[y * N + x];
  __syncthreads();
  // copy back on global memory
  b[x * N + y] = buffer[threadIdx.y * blockDim.x + threadIdx.x];
}

// naive transpose
__global__ void transpose(double *a, double *b, int N) {
  int row = (blockIdx.x * blockDim.x + threadIdx.x) / N;
  int col = (blockIdx.x * blockDim.x + threadIdx.x) % N;
  b[col * N + row] = a[row * N + col];
}

// just randomlly fill the matrix
void random_fill(double *mat, int N) {
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      mat[i * N + j] = (double)rand() / (double)RAND_MAX * 100.;
}

// Used for error-checking
void transpose_cpu(double *a, double *b, int N) {
  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      b[j * N + i] = a[i * N + j];
}

// check if two matrix are equals
int is_equal(double *a, double *b, int N) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++)
      if (b[i * N + j] != a[i * N + j])
        return 0;
  }
  return 1;
}

void print_mat(double *a, int N) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      printf("%.1f ", a[i * N + j]);
    }
    printf("\n");
  }
  printf("\n");
}

int main(int argc, char *argv[]) {

  double *a, *b, *c, *d; // host copies of a, b, c
  const int N = 8192;
  double *dev_a, *dev_b, *dev_c;     // device copies of a, b, c
  int size = N * N * sizeof(double); // we need space for 512
  // Get the number of block dimensions (dim1*dim2 = number of threads)
  if (argc < 3) {
    printf("Insert the dimensions, first x, second y\n");
    return -1;
  }
  // get block dimensions from command line
  const int dim1 = atoi(argv[1]);
  const int dim2 = atoi(argv[2]);
  const int Nblocks = (N * N) / 1024;
  if (dim1 * dim2 != BDIM) {
    printf("Give rigth dimensions\n");
    return -2;
  }
  dim3 grid, block;
  block.x = dim1;
  block.y = dim2;
  grid.x = N / block.x;
  grid.y = N / block.y;

  // allocate device copies of a, b, c
  cudaMalloc((void **)&dev_a, size);
  cudaMalloc((void **)&dev_b, size);
  a = (double *)malloc(size);
  b = (double *)malloc(size);
  d = (double *)malloc(size);
  // fill the matrix with random numbers
  random_fill(a, N);
  cudaMemcpy(dev_a, a, size, cudaMemcpyHostToDevice);
  // cuda event for timing
  cudaEvent_t start, stop;
  cudaEventCreate(&start);
  cudaEventCreate(&stop);

  cudaEventRecord(start);
  fast_transpose<<<grid, block>>>(dev_a, dev_b, N);
  cudaEventRecord(stop);
  cudaEventSynchronize(stop);
  float milliseconds = 0;
  cudaEventElapsedTime(&milliseconds, start, stop);
  cudaMemcpy(b, dev_b, size, cudaMemcpyDeviceToHost);
  //    print_mat(b,N);
  transpose_cpu(a, d, N);
  int equal = is_equal(b, d, N);
  if (equal)
    printf("Correct fast\n");
  else
    printf("Uncorrect fast\n");
  // Bandwith for reading from matrix a + writing on matrix b
  printf("Time fast= %f\n", milliseconds);
  printf("Bandwidth fast= %f\n", N * N * 2 * 8 / milliseconds / 1e6);
  free(b);
  cudaFree(dev_b);
  c = (double *)malloc(size);
  cudaMalloc((void **)&dev_c, size);

  cudaEventRecord(start);
  transpose<<<Nblocks, 1024>>>(dev_a, dev_c, N);
  cudaEventRecord(stop);
  cudaEventSynchronize(stop);
  cudaEventElapsedTime(&milliseconds, start, stop);
  cudaMemcpy(c, dev_c, size, cudaMemcpyDeviceToHost);
  equal = is_equal(c, d, N);
  if (equal)
    printf("Correct naive\n");
  else
    printf("Uncorrect naive\n");
  printf("Time naive = %f\n", milliseconds);
  printf("Bandwidth naive= %f\n", N * N * 2 * 8 / milliseconds / 1e6);
  free(a);
  free(c);
  free(d);
  cudaFree(dev_a);
  cudaFree(dev_c);
  return 0;
}
