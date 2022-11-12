#include <bits/stdc++.h>
using namespace std;
const long long mod =1e9 + 7;
const long long maxn = 2e5 + 7;

long long factorial[maxn];
long long moduloinverse[maxn];


long long binary_exponentiation(long long a,long long b)
{
    long long result = 1;
    a %= mod;

    while(b > 0)
    {
        if(b%2 == 1) result = (result*a)%mod;
        b/=2;
        a = (a*a)%mod;
    }

    return result;
}

void precompute()
{
    factorial[0] = 1;
    for(long long i = 1;i < maxn;i++)
    {
        factorial[i] = (i*factorial[i-1])%mod;

        moduloinverse[i] = binary_exponentiation(factorial[i],mod-2);
    }
}


int32_t main()
{
    precompute();

    int q;cin>>q;

    while(q--)
    {
        long long n,t;
        cin >> n >> t;

        long long ans = factorial[n];

        for(int i = 0;i < t;i++)
        {
            long long temp;
            cin >> temp;
            ans = (ans * moduloinverse[temp])%mod;
        }
        cout << ans << "\n";
    }



    return 0;
}
