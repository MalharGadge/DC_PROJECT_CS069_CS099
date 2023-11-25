#include <iostream>
#include <cmath>
#include <omp.h>
#include <chrono>

// Function to integrate (you can change this to any other function)
double f(double x) {
    return x*sin(x);
}

int main() {
    const int num_intervals = 1000000;  // Number of intervals
    const double a = 0.0;              // Lower limit of integration
    const double b = 100.0;              // Upper limit of integration
    const double dx = (b - a) / num_intervals;

    double integral = 0.0;

    // Serial implementation
    auto start = std::chrono::steady_clock::now();

    for (int i = 0; i < num_intervals; i++) {
        double x = a + i * dx;
        integral += 0.5 * (f(x) + f(x + dx)) * dx;
    }
    auto end = std::chrono::steady_clock::now();
    auto time = end - start;

    std::cout << "Serial Result: " << integral << std::endl;
    std::cout << "Serial Execution Time: " << time.count() << " nano seconds" << std::endl;

    // Parallel implementation
    integral = 0.0;
    auto t1 = std::chrono::steady_clock::now();

    #pragma omp parallel for reduction(+:integral)
    for (int i = 0; i < num_intervals; i++) {
        double x = a + i * dx;
        integral += 0.5 * (f(x) + f(x + dx)) * dx;
    }
    auto t2 = std::chrono::steady_clock::now();

    std::cout << "Parallel Result: " << integral << std::endl;
    std::cout << "Parallel Execution Time: " << (t2 - t1).count() << " nano seconds" << std::endl;

    return 0;
}
