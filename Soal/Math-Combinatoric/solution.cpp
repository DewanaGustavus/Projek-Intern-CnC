#include <bits/stdc++.h>
using namespace std;
long long int mod =1e9 + 7;
const int maxn = 2e5 + 7;

int factorial[maxn];
int moduloinverse[maxn];


int binary_exponentiation(int a,int b)
{
    int result = 1;
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
    for(int i = 1;i < maxn;i++)
    {
        factorial[i] = (i*factorial[i-1])%mod;

        moduloinverse[i] = binary_exponentiation(factorial[i],mod-2);
    }
}


int main()
{
    precompute();

    int q;

    while(q--)
    {
        int n,t;
        cin >> n >> t;

        int ans = factorial[n];

        for(int i = 0;i < t;i++)
        {
            int temp;
            cin >> temp;
            ans = (ans * moduloinverse[n-temp])%mod;
        }
        cout << ans << "\n";
    }



    return 0;
}
