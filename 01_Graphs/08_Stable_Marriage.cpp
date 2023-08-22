/*Input for the given problem looks like
Enter the number of men/women: 3

Enter men's preferences:
Preferences for Man 0: 1 0 2
Preferences for Man 1: 2 1 0
Preferences for Man 2: 0 2 1

Enter women's preferences:
Preferences for Woman 0: 1 0 2
Preferences for Woman 1: 0 2 1
Preferences for Woman 2: 1 2 0
*/
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Function to check if a person prefers a new partner over the old one
bool prefersNewPartner(const vector<vector<int>>& preference, int person, int newPartner, int currentPartner) {
    for (int i = 0; i < preference[person].size(); ++i) {
        if (preference[person][i] == newPartner)
            return true;
        if (preference[person][i] == currentPartner)
            return false;
    }
    return false;
}

// Function to solve the Stable Marriage problem using bipartite graph
void stableMarriage(const vector<vector<int>>& menPrefs, const vector<vector<int>>& womenPrefs) {
    int n = menPrefs.size(); // Number of men/women

    vector<vector<int>> graph(n * 2); // Bipartite graph represented as an adjacency list

    // Construct the bipartite graph
    for (int man = 0; man < n; ++man) {
        for (int woman : menPrefs[man]) {
            graph[man].push_back(woman + n); // Men are in the first partition (0 to n-1), women in the second (n to 2n-1)
        }
    }

    vector<int> womenPartner(n, -1); // Stores the current partner for each woman
    vector<bool> menEngaged(n, false); // Stores whether a man is available (false) or engaged (true)
    int engagedCount = 0; // Count of engaged men

    queue<int> freeMen; // Queue to keep track of free men
    for (int i = 0; i < n; ++i) {
        freeMen.push(i);
    }

    while (!freeMen.empty()) {
        int freeMan = freeMen.front();
        freeMen.pop();

        for (int woman : graph[freeMan]) {
            if (womenPartner[woman - n] == -1) {
                // Woman is not yet engaged, pair her with the free man
                womenPartner[woman - n] = freeMan;
                menEngaged[freeMan] = true;
                engagedCount++;
                break;
            } else {
                int currentPartner = womenPartner[woman - n];
                if (prefersNewPartner(womenPrefs, woman - n, freeMan, currentPartner)) {
                    // Woman prefers the new man over the current partner, update the pairings
                    womenPartner[woman - n] = freeMan;
                    menEngaged[freeMan] = true;
                    menEngaged[currentPartner] = false;
                    freeMen.push(currentPartner);
                    break;
                }
            }
        }
    }

    // Print the stable matches
    cout << "Stable Matches:" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "Man " << i << " is matched to Woman " << womenPartner[i] << endl;
    }
}

int main() {
    int n; // Number of men/women

    cout << "Enter the number of men/women: ";
    cin >> n;

    vector<vector<int>> menPrefs(n, vector<int>(n));
    vector<vector<int>> womenPrefs(n, vector<int>(n));

    cout << "Enter men's preferences:" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "Preferences for Man " << i << ": ";
        for (int j = 0; j < n; ++j) {
            cin >> menPrefs[i][j];
        }
    }

    cout << "Enter women's preferences:" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "Preferences for Woman " << i << ": ";
        for (int j = 0; j < n; ++j) {
            cin >> womenPrefs[i][j];
        }
    }

    stableMarriage(menPrefs, womenPrefs);

    return 0;
}
