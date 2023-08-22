#include <iostream>
#include<vector>
#include<queue>
using namespace std;
class Solution {
public:
    vector<int> bfsOfGraph(int V, vector<int> adj[])
    /*This is a function which returns vector
    V are number of nodes and vector<int> adj[] is array of vectors (adjacency array), both V and adjacency array
    will be provided in input*/ {
        vector<int> bfs;  // Vector to store the BFS traversal result
        vector<int> vis(V, 0);  // Visited array

        queue<int> q;
        q.push(0);  // Starting from node 0

        vis[0] = 1;  // Mark node 0 as visited

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            bfs.push_back(node);

            for (int neighbor : adj[node]) {
                if (!vis[neighbor]) {
                    q.push(neighbor);
                    vis[neighbor] = 1;  // Mark the neighbor as visited
                }
            }
        }

        return bfs;
    }
};

 int main(){
    
    return 0;
}