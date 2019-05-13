#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#define N 10000000000


double f(double x){
    return 1/(1+x*x);
} 


int main( int argc, char * argv[] ) {
    double tstart = omp_get_wtime();
    int threads;
    if(argc < 2) threads = 1;
    else threads = atoi(argv[1]);
    double global_result=0.0;
    double h = 1./N;
    long int i;
    #pragma omp parallel for reduction(+:global_result) num_threads(threads)
        for(i = 0; i < N; i++){
            double x_i = i*h+h/2.0;
            global_result += f(x_i);
        } 
    double tend = omp_get_wtime();

    printf("pi=%f time=%fsec \n",h*global_result*4, tend-tstart);
    return 0;
}
