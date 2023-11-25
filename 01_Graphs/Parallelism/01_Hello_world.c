#include <omp.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    
    #pragma omp parallel
    {
        printf("Hello World!\n");
        /*in the terminal by giving instruction 
        "export OMP_NUM_THREADS=n" you can print it(execute it)
        for n times*/
    }
    
    return 0;
}
