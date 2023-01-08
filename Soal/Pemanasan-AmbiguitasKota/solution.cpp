#include <bits/stdc++.h>
using namespace std;

#define int long long

const int inf = 1e18;
const int maxn = 2e5 + 5;
vector<pair<int,int>> adj[maxn];
vector<int> dist(maxn, inf);
bool visited[maxn];

void dijkstra(int node){
    // Time Complexity : O(n + m log(m))
    dist[node]=0; 
    priority_queue<pair<int,int>> q; 
    q.push({0,node}); 

    while(!q.empty()){ 
        int curr = q.top().second;q.pop(); 
        if(visited[curr])continue; 
        visited[curr] = true;

        for(auto edge:adj[curr]){ 
            int next = edge.first;
            int weight = edge.second;
            if(dist[curr] + weight < dist[next]){ 
                dist[next] = dist[curr] + weight;
                q.push({-dist[next],next}); 
            }
        }
    }
}

int32_t main(){

    ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n, m, k;
    cin >> n >> m >> k;
    for(int i=0;i<m;i++){
        int a,b,w;
        cin>>a>>b>>w;
        adj[b].push_back({a,w});
    }
    
    dijkstra(k);

    map<int,int> cnt;
    int ans = 0;
    for(int i=1;i<=n;i++){
        if(dist[i] != inf){
            cnt[dist[i]]++;
        }
    }
    
    for(auto tmp : cnt){
        ans += (tmp.second * (tmp.second-1))/2;
    }

    cout << ans << endl;
}