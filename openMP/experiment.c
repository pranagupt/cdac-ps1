#include <stdio.h>
#include <omp.h>

//#define pad 8
#define NUM_THREADS 12


static long num_steps = 100000;
int main(){
    double sum[NUM_THREADS];
    int num_threads;
    double step = 1.0/(double)num_steps;
    double ans=0; double t1=0, t2=0;
    t1 = omp_get_wtime();
    omp_set_num_threads(NUM_THREADS);
    #pragma omp parallel
    {
        int id = omp_get_thread_num(), nthreads = omp_get_num_threads();
        double x = 0;
        if(id == 0) num_threads = nthreads;
        for (int i = id; i < num_steps; i+=nthreads){
            x = (i+0.5)*step;
            sum[id] += 4.0/(1.0 + x*x);
        }
    }
    t2 = omp_get_wtime();
    for (int i = 0; i<num_threads; i++){ans+=sum[i];}
    ans*=step;
    printf("%lf\n", ans);
    printf("threads:%d  time:%lf \n", num_threads, t2-t1);
}