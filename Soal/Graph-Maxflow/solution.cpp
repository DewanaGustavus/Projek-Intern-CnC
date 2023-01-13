#include <bits/stdc++.h>
using namespace std;
 
// Define Template          Python++
// Data Structure and Algorithm
#define all(vec)            (vec).begin(),(vec).end() 
#define arrsize(arr)        sizeof(arr)/sizeof(int)
#define sortarr(arr)        sort(arr,arr+arrsize(arr));
#define sortvec(vec)        sort(all(vec));
#define minarr(arr)         *min_element(arr,arr+arrsize(arr))
#define minvec(vec)         *min_element(all(vec))
#define maxarr(arr)         *max_element(arr,arr+arrsize(arr))
#define maxvec(vec)         *max_element(all(vec))
#define sumarr(arr)         accumulate(arr,arr+arrsize(arr),0LL)
#define sumvec(vec)         accumulate(all(vec),0LL)
#define reversearr(arr)     reverse(arr,arr+arrsize(arr));
#define reversevec(vec)     reverse(all(vec));
#define range(i,s,e)        for(int i=s;i<e;i++)
#define range2(i,s,e)       for(int i=s;i>=e;i--)
#define fors(var,arr)       for(auto &var:arr)
// Input Output Manage
#define debug(x)    cout<<(#x)<<" : "<<(x)<<endl;
#define test        cout<<"test"<<endl;
#define fastIO              ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define floatprecision      cout<<fixed<<setprecision(9);
#define fileread            freopen("input.txt","r",stdin);
#define fileout             freopen("output.txt","w",stdout);
#define query               cin>>QUERY;while(QUERY--)
#define inputarr(arr,am)    int arr[am];fors(num,arr)cin>>num;
#define inputvec(vec,am)    vector<int> vec(am);fors(num,vec)cin>>num;
#define input(var)          int var;cin>>var;
#define input2(a,b)         int a,b;cin>>a>>b;
#define inputs(var)         string var;cin>>var;
#define print(var)          cout<<(var)<<endl;
#define prints(var)         cout<<(var)<<' ';
#define print2(var1,var2)   cout<<(var1)<<' '<<(var2)<<endl;
#define printp(paired)      cout<<(paired.first)<<' '<<(paired.second)<<endl;
#define printyes(cond)      cout<<((cond)?"YES":"NO")<<endl;
#define printarr(arr)       fors(num,arr){cout<<num<<' ';};cout<<endl;
#define printmap(hashmap)   for(auto[x,y]:hashmap)cout<<x<<":"<<y<<endl;
#define endline             cout<<endl;
// Macro
#define ll long long
#define pii pair<int,int>
#define vi vector<int>
#define vvi vector<vector<int>>
#define mii map<int,int>
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define pq priority_queue
#define ms multiset
// Oneliner Function
ll sigma(ll num){return num*(num+1)/2;}
ll gcd(ll a, ll b){return (a==0?b:gcd(b%a,a));}
ll lcm(ll a, ll b){return (a*b)/gcd(a,b);}
ll binpow(ll a,ll b,ll m=INT64_MAX){ll r=1;a%=m;while(b){if(b&1)r=(r*a)%m;a=(a*a)%m;b>>=1;}return r;}
ll invmod(ll a,ll m){return gcd(a,m)==1?binpow(a,m-2,m):0;}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

#define int long long
#define float long double
int QUERY;
// Constant
const int MOD = 1e9+7;
const long long INF = 1e18;


const int maxn = 4e3; // max node = n * primefactor, around n * log(max(A)) = 100 * 31
int capacity[maxn][maxn] = {};
vector<int> adj[maxn];
map<pii, int> indexcomp;
int maxnode = 1;

void add_edge(int from, int to, int cap){
    adj[from].pb(to);
    adj[to].pb(from);
    capacity[from][to] += cap;
}

int bfs(int source, int sink, vector<int>& parent) {
    const int inf = 1e9;
    fill(parent.begin(), parent.end(), -1);
    parent[source] = -2;
    queue<pair<int, int>> q;
    q.push({source, inf});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) 
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == sink)
                    return new_flow;
                q.push({next, new_flow});
            }
    }

    return 0;
}

int maxflow(int source, int sink) {
    int flow = 0;
    vector<int> parent(maxnode + 1);
    int new_flow;

    while (new_flow = bfs(source, sink, parent)) {
        flow += new_flow;
        int cur = sink;
        while (cur != source) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}

vector<pair<int,int>> primefactor(long long num){
    // Time Complexity : O(sqrt(n))
    vector<pair<int,int>> ret;

    for(int p=2;p*p<=num;p++){ 
        int count = 0;
        while(num%p==0){ 
            count++;
            num/=p;
        }
        if(count>0)ret.push_back({p, count});
    }

    if(num>1)ret.push_back({num,1});
    return ret;
}

int get_node(int idx, int prime){
    if(indexcomp[{idx, prime}] == 0){
        indexcomp[{idx, prime}] = maxnode++;
    }
    return indexcomp[{idx, prime}];
}

int32_t main(){
    fastIO
    
    int n, m;
    cin>>n>>m;
    inputvec(arr, n)
    vector<pii> factorized[n];
range(i,0,n){
    factorized[i] = primefactor(arr[i]);
}
    int source = 0;
    range(i,0,n){
        fors(p, factorized[i]){
            get_node(i, p.first);
        }
    }
    int sink = maxnode++;

range(i,0,m){
    input2(a,b)
    a--;b--;
    if(a%2)swap(a,b);
    int tmp = gcd(arr[a], arr[b]);
    auto factorizedgcd = primefactor(tmp);
    fors(p, factorizedgcd){
        int node1 = get_node(a, p.first);
        int node2 = get_node(b, p.first);
        add_edge(node1, node2, p.second);
    }
}

    for(int i=0;i<n;i+=2){
        fors(p, factorized[i]){
            int node = get_node(i, p.first);
            add_edge(source, node, p.second);
        }
    }
    
    for(int i=1;i<n;i+=2){
        fors(p, factorized[i]){
            int node = get_node(i, p.first);
            add_edge(node, sink, p.second);
        }
    }

    print(maxflow(source, sink))
    
    
    return 0;
}
