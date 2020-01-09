#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <pthread.h>

#define MAXTHREADS 1024
long long sum[MAXTHREADS]; // holds the sum calculated by each thread

typedef struct da_params { // struct of parameters passed to the thread
    int thread_num;  // thread num (not thread id)
    long long start; // inial number to sum
    long long stop;  // last number to sum
} t_param;

// sums the results from all threads
long long sum_array(long long a[], int num_elements) {
    long long i, sum = 0;
    for (i = 0; i < num_elements; i++) {
        sum = sum + a[i];
    }
    return (sum);
}

// function to calculate sum of range of numbers
void *summer(void *param) {
    t_param *my_param = (t_param *) param;  // cast the input void * parameter to
                                            // proper type
    sum[my_param->thread_num] = 0;

    for (long long i = my_param->start; i <= my_param->stop; i++) {
        sum[my_param->thread_num] += i;
    }
    pthread_exit(0);

}

int main(int argc, char *argv[]) {
    t_param theparams[MAXTHREADS]; // array of parameters for each thread
    pthread_t tids[MAXTHREADS];    // array of thread ids
    int num_threads;

    num_threads = atoi(argv[1]);  // number of threads is 1st command line arg
    long long start = 0;
    long long stop = atoll(argv[2]);  // stop point its 2nd command line arg
    long long div = (stop - start) / num_threads;  // calculate range for each thread
    long long rem = (stop - start) % num_threads;  // what was left over add to last thread

    for (int i = 0; i < num_threads; i++) {
        // set parameters for each thread
        theparams[i].thread_num = i;
        theparams[i].start = div * i + start + 1;
        theparams[i].stop = div * (i + 1) + start;
        // add rem to last thread if didn't divide evenly
        if (i == num_threads - 1) {
            theparams[i].stop += rem;
        }
        // print parameters sent to the thread
        printf("Thread: %2d, start:%10lld, stop:%10lld\n", i, theparams[i].start, theparams[i].stop);
        pthread_create(&tids[i], NULL, summer, &theparams[i]);
    }

    // wait for all threads to finish prior to continuing
    for (int i = 0; i < num_threads; i++) {
        pthread_join(tids[i], NULL);
    }

    setlocale(LC_NUMERIC, "");  // allow for commas in output
    printf("sum = %'lld\n", sum_array(sum, num_threads)); // output sum with commas
}