#include <bits/stdc++.h>
using namespace std;
 
// Define Template          Python++
// Math
const int MOD = 1e9+7;
const long long INF = INT64_MAX;
// const long long INF = LLONG_MAX;
#define intlen(num)         to_string(num).size()
// Data Structure and Algorithm
#define all(vec)            vec.begin(),vec.end() 
#define arrsize(arr)        sizeof(arr)/sizeof(int)
#define sortarr(arr)        sort(arr,arr+arrsize(arr));
#define sortvec(vec)        sort(all(vec));
#define minarr(arr)         *min_element(arr,arr+arrsize(arr))
#define minvec(vec)         *min_element(all(vec))
#define maxarr(arr)         *max_element(arr,arr+arrsize(arr))
#define maxvec(vec)         *max_element(all(vec))
#define sumarr(arr)         accumulate(arr,arr+arrsize(arr),0)
#define sumvec(vec)         accumulate(all(vec),0)
#define reversearr(arr)     reverse(arr,arr+arrsize(arr));
#define reversevec(vec)     reverse(all(vec));
#define range(i,s,e)        for(int i=s;i<e;i++)
#define range2(i,s,e)       for(int i=s;i>=e;i--)
#define fors(var,arr)       for(auto &var:arr)
#define len(arr)            arr.size()
// Input Output Manage
#define fastIO              ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
#define fileread            freopen("input.txt","r",stdin);
#define query               cin>>QUERY;while(QUERY--)
#define inputarr(arr,am)    int arr[am];fors(num,arr)cin>>num;
#define inputvec(vec,am)    vector<int> vec(am);fors(num,vec)cin>>num;
#define input(var)          int var;cin>>var;
#define input2(a,b)         int a,b;cin>>a>>b;
#define inputs(var)         string var;cin>>var;
#define print(var)          cout<<var<<endl;
#define prints(var)         cout<<var<<" ";
#define print2(var1,var2)   cout<<var1<<" "<<var2<<endl;
#define printp(paired)      cout<<paired.first<<" "<<paired.second<<endl;
#define printyes(cond)      cout<<(cond?"YES":"NO")<<endl;
#define printarr(arr)       fors(num,arr){cout<<num<<" ";};cout<<endl;
#define printmap(hashmap)   fors(container,hashmap)cout<<container.first<<" : "<< container.second<<endl;
#define endline             cout<<endl;
 
#define int long long
int QUERY;
 
long long sigma(long long num){return num*(num+1)/2;}
 
 
int32_t main(){
#ifndef ONLINE_JUDGE
    // fileread;
#endif
    fastIO
    
    input(n)
    int dp[n+1];
    fors(num,dp)num = INF;
    dp[n] = 0;
    queue<int> process;
    process.push(n);
    while(!process.empty()){
        int num = process.front();
        process.pop();
 
        int tmp = num;
        while(tmp>0){
            int x = num-(tmp%10);
            if(dp[num]+1 < dp[x]){
                dp[x] = dp[num] + 1;
                process.push(x);
            }
            tmp/=10;
        }
    }
    print(dp[0])
 
    return 0;
}
 