#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define N 1000000000

double f(double x) { return 1 / (1 + x * x); }

int main(int argc, char *argv[]) {
  double h = 1. / N;
  double approx = 0;
  int i;
  for (i = 1; i < N; i++) {
    double x_i = i * h;
    approx += f(x_i);
  }
  printf("%f \n", h * approx * 4);
  return 0;
}