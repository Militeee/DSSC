#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

void print_usage(int *a, int N, int nthreads) {

  int tid, i;
  for (tid = 0; tid < nthreads; ++tid) {

    fprintf(stdout, "%d: ", tid);

    for (i = 0; i < N; ++i) {

      if (a[i] == tid)
        fprintf(stdout, "*");
      else
        fprintf(stdout, " ");
    }
    printf("\n");
  }
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    printf("Not enough argument");
    return -1;
  }
  int threads = atoi(argv[1]);
  int chunks = atoi(argv[2]);

  const int N = 250;
  int a[N];
  int b[N];
  int nthreads = 0;
  int i;
#pragma omp parallel num_threads(threads)
  {
    int thread_id = omp_get_thread_num();
    nthreads = omp_get_num_threads();
#pragma omp for schedule(static, chunks)
    for (i = 0; i < N; ++i) {
      a[i] = thread_id;
    }
#pragma omp for schedule(dynamic, chunks)
    for (i = 0; i < N; ++i) {
      b[i] = thread_id;
    }
  }
  printf("Static schedule with ntreads = %d and chunk size = %d\n\n\n",
         nthreads, chunks);
  print_usage(a, N, nthreads);
  print_usage(b, N, nthreads);

  return 0;
}
