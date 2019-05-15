#include <math.h>
#include <stdio.h>

#define N 200

__global__ void reverse(int *a, int *b) {
  int idx = blockIdx.x * blockDim.x + threadIdx.x;
  b[gridDim.x - idx - 1] = a[idx];
}

void random_ints(int *p, int n) {
  int i;
  for (i = 0; i < n; i++) {
    p[i] = rand() % 100;
  }
}

int main(void) {
  int *a, *b;                 // host copies of a, b, c
  int *dev_a, *dev_b;         // device copies of a, b, c
  int size = N * sizeof(int); // we need space for 512
                              // // integers
  int i;

  // allocate device copies of a, b, c
  cudaMalloc((void **)&dev_a, size);
  cudaMalloc((void **)&dev_b, size);
  a = (int *)malloc(size);
  b = (int *)malloc(size);

  random_ints(a, N);
  // copy inputs to device
  cudaMemcpy(dev_a, a, size, cudaMemcpyHostToDevice);

  // launch an add() kernel with N threads
  reverse<<<N, 1>>>(dev_a, dev_b);

  // copy device result back to host copy of c
  cudaMemcpy(b, dev_b, size, cudaMemcpyDeviceToHost);

  for (i = 0; i < N; i++) {
    if (b[i] != a[N - 1 - i]) {
      printf("Uncorrect\n");
      break;
    }
  }
  printf("Correct\n");

  free(a);
  free(b);
  cudaFree(dev_a);
  cudaFree(dev_b);
  return 0;
}
