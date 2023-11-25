#include <bits/stdc++.h>
#include <vector>
#include <queue>
#include <omp.h>
#include <chrono>
#include <iomanip>
#include <random>    
#include <algorithm>
using namespace std;

std::vector<std::vector<int>> createRandomMatrix(int n) {
    std::vector<std::vector<int>> matrix(n, std::vector<int>(n));

    #pragma omp parallel for num_threads(40) 
    for (int i = 0; i < n; ++i) {
        // Each thread will have its own random number generator
        std::random_device rd;
        std::default_random_engine rng(rd() ^ (i + 1)); // Seed is unique for each thread

        for (int j = 0; j < n; ++j) {
            matrix[i][j] = j; 
        }
        std::shuffle(matrix[i].begin(), matrix[i].end(), rng);
    }

    return matrix;
}

bool prefersNewPartner(const vector<vector<int>>& preferenceRank, int woman, int man, int currentPartner) {
    return preferenceRank[woman][man] < preferenceRank[woman][currentPartner];
}

// Function to solve the Stable Marriage problem
void stableMarriage(const vector<vector<int>>& menPrefs, const vector<vector<int>>& womenPrefs) {
    int n = menPrefs.size();
    vector<int> womenPartner(n, -1), menNextPropose(n, 0);
    vector<bool> menEngaged(n, false);
    vector<vector<int>> womenPreferenceRank(n, vector<int>(n));

    // Preprocess women's preferences
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            womenPreferenceRank[i][womenPrefs[i][j]] = j;
        }
    }

    // Initially, all men are free
    queue<int> freeMen;
    #pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        #pragma omp critical
        freeMen.push(i);
    }

    auto start = std::chrono::steady_clock::now();

    while (!freeMen.empty()) {
        int man = freeMen.front();
        int woman = menPrefs[man][menNextPropose[man]];

        // Man proposes to the next woman in his preference list
        if (womenPartner[woman] == -1) { // Woman is free
            #pragma omp critical

            womenPartner[woman] = man;
            menEngaged[man] = true;
            freeMen.pop();
        } else if (prefersNewPartner(womenPreferenceRank, woman, man, womenPartner[woman])) {
            // Woman prefers this man over her current partner
            #pragma omp critical

            int currentPartner = womenPartner[woman];
            menEngaged[currentPartner] = false;
            freeMen.pop();
            #pragma omp critical

            freeMen.push(currentPartner);

            womenPartner[woman] = man;
            menEngaged[man] = true;
        }

        // If the man was rejected, he will propose to the next woman in his list next time
        if (!menEngaged[man]) {
            menNextPropose[man]++;
        }
    }

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    elapsed_seconds*=1e3;
    std::cout << "Gale Shapley Algorithm exe_time : " << elapsed_seconds.count() << "ms\n";

    // Print the stable matches
    // cout << "Stable Matches:" << endl;
    // for (int i = 0; i < n; ++i) {
    //     cout << "Man " << i << " is matched to Woman " << womenPartner[i] << endl;
    // }

}

int main() {
    int n;
    cin >> n;

    vector<vector<int>> menPrefs(n, vector<int>(n));
    vector<vector<int>> womenPrefs(n, vector<int>(n));


    menPrefs = createRandomMatrix(n);
    womenPrefs = createRandomMatrix(n);


    auto start3 = std::chrono::steady_clock::now();
    stableMarriage(menPrefs, womenPrefs);
    auto end3 = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds3 = end3 - start3;
    elapsed_seconds3*=1e3;
    std::cout << "Total Time Elapsed : " << elapsed_seconds3.count() << "ms\n";


    return 0;
}