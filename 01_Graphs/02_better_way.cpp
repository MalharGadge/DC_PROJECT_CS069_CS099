#include <iostream>
#include<vector>
using namespace std;

 int main(){
    int m,n;
    cin>>m>>n;
    vector<int>adj[n+1];

    for(int i=0;i<=m;i++){
        int u,v;
        adj[u].push_back(v);//on the uth index store v
        adj[v].push_back(u);//on the vth index store u
        /*for directed graph we dont need adj[v].push_back(u); 
        since only v is neighbour of u and not the other way round (u----->v)*/

    }
    return 0;
}