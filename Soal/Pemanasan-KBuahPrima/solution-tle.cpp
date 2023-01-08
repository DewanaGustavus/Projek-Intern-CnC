#include <bits/stdc++.h>
using namespace std;


int main(){
    const int maxn = 1e6;
    int primecnt[maxn + 1] = {};

    for(int p=2;p*p<=maxn;p++)
        if(primecnt[p] == 0)
            for(int i=p;i<=maxn;i+=p) // O(log(n)) harmonic series
                primecnt[i]++;

    int q;cin>>q;
while(q--){
    int k,l,r;
    cin>>k>>l>>r;
    int ans = 0;
    for(int i=l;i<=r;i++){
        if(primecnt[i] == k){
            ans++;
        }
    }
    cout << ans << endl;
}

    return 0;
}