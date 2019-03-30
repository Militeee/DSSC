#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#define N 100000000


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
    int i;
    #pragma omp parallel num_threads(threads) private(i)
    {
        double partial=0;
        #pragma omp for 
        for(i = 1; i < N; i++){
            double x_i = i*h;
            partial += f(x_i);
             //I know that the function is thread-safe
        }
        #pragma omp atomic
        global_result += partial;
    }
    double tend = omp_get_wtime();

    printf("pi=%f time=%fsec \n",h*global_result*4, tend-tstart);
    return 0;
}
