// #include <stdio.h>
// #include <omp.h>

// int main(int argc, char *argv[]) {
//     int numt, tid;

//     #pragma omp parallel
//     {
//         numt = omp_get_num_threads();
//         tid = omp_get_thread_num();
//         printf("Hello World from thread %d of %d\n", tid, numt);
//     }

//     return 0;
// }
/*the above code causes race conditions*/
#include <stdio.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    int numt, tid;

    #pragma omp parallel private(tid)/*works as if tid is declared insdide
    it means it is now private to evry thread and not global, if instead of private i would have written it 
    would mean it it global */
    {
        numt = omp_get_num_threads();
        tid = omp_get_thread_num();
        printf("Hello World from thread %d of %d\n", tid, numt);
    }

    return 0;
}