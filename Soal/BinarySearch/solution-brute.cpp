// COBA BRUTEFORCE
#include<bits/stdc++.h>
#define int long long
#define vi vector<int>
#define forn(i,n) for(int i = 0; i < n; ++i)

using namespace std;
const int MOD = 1000000007;

void solve() {
    int a,b,c,d,e;
    cin >> a >> b >> c >> d >> e;
    if(a == 0 && b == 0) {
        cout << (e - d) /c << '\n';
    }
    else {
        for(int i = 0; i <= 1e6; i++) {
            int tmp = 0;
            if(a > 0)tmp += a*i*i*i;
            if(b > 0)tmp += b*i*i;
            if(c > 0)tmp += c*i;
            if(d > 0)tmp += d;
            if(tmp == e){
                cout << i << '\n';
                return;
            }
        }
    }
}

int32_t main() 
{
    int tc = 1;
    cin >> tc;
    for (int t = 1; t <= tc; t++) {
        solve();
    }
}