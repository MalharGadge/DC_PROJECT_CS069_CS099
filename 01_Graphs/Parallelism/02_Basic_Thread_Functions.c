#include <omp.h>
#include <stdio.h>

int main(int argc, char* argv[]) {

    #pragma omp parallel
    {
        /*There is a call to find the number of threads
        and each thread has a thread id(unique) suppose you need to find the dot product of say thousand entries
        and divide the work into four parts say 4 threads
        then say thread with id 0 will do part 1 with id 1 does part 2 and so on...
        this helps keep track of the thread*/
        /******************/
        /*Get the total no of OMP threads */
        int numt = omp_get_num_threads();
        /*Get the thread id */
        int tid = omp_get_thread_num();
        /*Get the thread id */
        printf("Thread %d of %d\n", tid, numt);
        /*print Hello World along with thread id and no of threads*/
        printf("Hello World from thread %d of %d\n", tid, numt);
        /*checking the output you will find the instruction in each thread
        is performed sequentially but the order of which thread will execute first is not
        sequential*/



        /*study race condition L15 last part*/
       
    }
    
    return 0;
}
