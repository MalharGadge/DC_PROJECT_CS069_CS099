#include <iostream>
#include <chrono>
#include <omp.h>
using namespace std;

#define size 1000000

int arr[size];

int main() {
    for (int i = 0; i < size; i++) {
        arr[i] = 1;
    }

    // Serial Execution
    int sum_series = 0;
    auto start = std::chrono::steady_clock::now();

    for (int i = 0; i < size; i++) {
        sum_series += arr[i];
    }

    auto end = std::chrono::steady_clock::now();

    cout << "Series Result " << sum_series << endl;
    cout << "Time Required " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << endl;

    // Parallel Execution
    int sum_parallel = 0;
    int i, tid, numt;

    auto t1 = std::chrono::steady_clock::now();

    #pragma omp parallel default(shared) private(i, tid)
    {
        int from, to;
        int psum = 0;

        tid = omp_get_thread_num();
        numt = omp_get_num_threads();

        // Manual distribution of work to each thread
        if (tid == numt - 1) {
            to = size - 1;
        } else {
            from = (size / numt) * tid;
            to = (size / numt) * (tid + 1) - 1;
        }

        // Each thread stores value in a local variable psum
        for (int i = from; i <= to; i++) {
            psum += arr[i];
        }

        // Here, each thread individually updates the sum without interfering with others using a critical section
        #pragma omp critical
        sum_parallel += psum;
    }

    auto t2 = std::chrono::steady_clock::now();

    cout << "Parallel Result " << sum_parallel << endl;
    cout << "Time Required " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << " ms" << endl;

    return 0;
}
