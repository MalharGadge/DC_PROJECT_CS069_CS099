//here we will check whether the graph is Bipartite or not using BFS algorithm
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Solution{
    bool is_Bipartite(int V,vector<int> adj[]){
   queue<int>q;
   int vis[V];//considering zero based indexing
   for(int i=0;i<V;i++){
    vis[i]= -1;
   }
     
   q.push(0);
   vis[0] =0;
   while(!q.empty()){
    int node = q.front();
    q.pop();
    for(auto it : adj[node]){
        if(vis[it]==-1 ){
            vis[it]= !vis[node];

        }
        else if(vis[it]==vis[(node)]){
            return false;
        
        }
    }
   }
   return true;
   

       }
      
};
 int main(){
   
    
    return 0;
}