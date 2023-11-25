Stable Marriage Problem Solver

Overview

This project implements a solution to the Stable Marriage Problem using the Gale-Shapley algorithm. The program is designed to efficiently match 'n' men and 'n' women based on their preferences.

Features

Gale-Shapley Algorithm: A proven algorithm to find a stable match in polynomial time.
Parallel Processing: Utilizes OpenMP for parallel processing to improve performance on large datasets.
Random Data Generator: Generates random preference lists for both men and women for testing purposes.
Execution Time Analysis: Records and displays the execution time for various input sizes.
How it Works

The program first generates random preference lists for a specified number of men and women. It then uses the Gale-Shapley algorithm to find a stable match. The execution time is measured for both the standard and parallelized versions of the algorithm.

Requirements

C++ Compiler with OpenMP support (e.g., GCC)
C++ Standard Library

Compilation and Execution

Compile the program using a C++ compiler with OpenMP support. For example:

Copy code
g++ -fopenmp -o stable_marriage stable_marriage.cpp
To run the program:

bash
Copy code
./stable_marriage
The program will prompt you to enter the number of men and women.

Parallelization

The code has been parallelized using OpenMP, which significantly reduces the execution time for larger input sizes. The parallelization mainly focuses on the main loop of the Gale-Shapley algorithm, where multiple men propose to women concurrently.

Conclusions

The parallelized version of the Gale-Shapley algorithm shows a significant improvement in execution time, especially for larger datasets. This makes the solution more scalable and efficient for practical use cases involving large numbers of participants.
