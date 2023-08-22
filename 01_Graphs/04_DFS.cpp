#include <iostream>
#include <vector>
using namespace std;

class Solution{
    private:
    void dfs(int node,vector<int> adj[],int vis[],vector<int> &ls){
        vis[node]=1;
        ls.push_back(node);
        for(auto it : adj[node]){
            if(!vis[it]){
               dfs(it,adj,vis,ls);
            }
            
        }
    }

    public:
    vector<int> dfs(int V,vector<int> adj[])/*This is a function which returns vector
    V are number of nodes and vector<int> adj[] is array of vectors (adjacency array), both V and adjacency array
    will be provided in input*/ 
    {int vis[V]={0};//considering zero based indexing 
    int node1 =0;
    vector<int> ls;//for getting the output
    dfs(node1,adj,vis,ls);
    return ls;


    }
    
}; 
 int main(){
    
    return 0;
}