#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
/*inout grid will be given*/
class Solution{
    public:
    //Function to find minimum time reuired to rot all oranges
    int orangesRotting(vector<vector<int>> &grid){
        int n = grid.size();//no. of rows
        int m = grid[0].size();
        queue<pair<pair<int,int>,int>> q;
        //queue which contain pair like {{row,col}, time}
        vector<vector<int>> vis;
        //visited 2d array
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(grid[i][j]==2){
                    q.push({{i,j},0});
                    /*traversing through whole grid and adding
                    only rotten oranges to the queue and time =0*/
                    vis[i][j]=2;
                    //marking them in visited array 
                }
            }
        }
        int time=0;
        int drow[]= {-1,0,+1,0};
        int dcol[]={0,1,0,-1};
        /*Explaination to this is my notes*/
        while(!q.empty()){
            int row =q.front().first.first;
            int col = q.front().first.second;
            int t = q.front().second;
            time = max(time,t);
            /*q.front() implies front element of queue
            q.front().first implies first pair of pairs
             queue<pair<pair ---><int,int><-----,int>> q;
             q.front().first.second implies second element of first pair
              queue<pair<pair<int,---->int<----->,int>> q;*/
            q.pop();
            for(int i=0;i<4;i++)//since there are 4 neighbours
             {
                int nrow = row + drow[i];
                /*nrow and ncol are respectively neighbouring row 
                and neighbouring col*/
                int ncol = col + dcol[i];
                if(nrow>=0&&nrow<=n&&ncol>=0&&ncol<=m&&
                 vis[nrow][ncol]!=2 && grid[n][m]==1){
                    q.push({{nrow,ncol},t+1});
                    vis[nrow][ncol]= 2;
                 }
             }
        }
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(vis[i][j]!=2 && grid[i][j]==1){
                    return -1;
                }
            }
        }
        return time;


         


         


    }
};
 int main(){
    
    return 0;
}