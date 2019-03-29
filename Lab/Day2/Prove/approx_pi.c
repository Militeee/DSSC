#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#define N 100000000


double f(double x){
    return 1/(1+x*x);
} 


int main( int argc, char * argv[] ) {
    int threads;
    if(argc < 2) threads = 1;
    else threads = atoi(argv[1]);
    double global_result=0.0;
    double h = 1./N;
    #pragma omp parallel reduction(+:global_result) num_threads(threads)
    {
        int nthreads = omp_get_num_threads();
        int id = omp_get_thread_num();
        int local_n = N/nthreads;
        double start = id*local_n;
        double end = start + local_n;
        int i;
        for(i = start; i < end; i++){
            double x_i = i*h;
            global_result += f(x_i);
        }
    }
    printf("%f \n",h*global_result*4);
    return 0;
}