#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include<omp.h>
using namespace std;

vector<int> graph[100];
bool visited[100];

void BFS(int start)
{
    queue<int> q;
    q.push(start);
    visited[start] = true;

    while(!q.empty()){
        int node = q.front();
        q.pop();
        cout<<node<<" ";

        #pragma omp parallel for
        for(int i = 0 ; i<graph[node].size() ; i++){
            int adj = graph[node][i];
            #pragma omp critical
            {
                if(!visited[adj])
                {
                    visited[adj] = true;
                    q.push(adj);
                }
            }
        }
    }
}

void DFS(int start){
    stack<int> st;
    st.push(start);
    

    while(!st.empty()){
        int node = st.top();
        st.pop();
        
        if(!visited[node]){
            visited[node] = true;
            cout << node <<" ";
            
            #pragma omp parallel for
            for(int i = 0 ; i<graph[node].size() ; i++)
            {
                int adj = graph[node][i];
                #pragma omp critical
                {
                    if(!visited[adj])
                    {
                        st.push(adj);
                    }
                }
            }
        }
    }
}

int main(){

    int n,m;
    cout<<"Enter nodes and edges:\n";
    cin>>n>>m;

    for(int i = 0 ; i<m ; i++){
        int u,v;
        cout<<"Enter edges:\n";
        cin>>u>>v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    for(int i =0 ; i<n ;  i++){
        visited[i] = false;
    }

    cout<<"BFS:";
    BFS(0);
    
    for(int i =0 ; i<n ;  i++){
        visited[i] = false;
    }

    cout<<"DFS:";
    DFS(0);

    return 0;
}