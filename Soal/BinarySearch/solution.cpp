#include <bits/stdc++.h>
using namespace std;

#define int long long 

long long func(int a, int b, int c, int d, long long x){ // f(x)
    long long ret = a*x*x*x;
    ret += b*x*x;
    ret += c*x;
    ret += d;
    return ret;
}

int32_t main(){
    int q;
    cin>>q;
    int linMAX = 2e15;
    int quadMAX = 5e7;
    int cubMAX = 2e5;

    while(q--){
        int a,b,c,d,fn;
        cin>>a>>b>>c>>d>>fn;
        int low = 0;
        int high;
        if(a != 0)high = cubMAX;
        else if(b != 0)high = quadMAX;
        else high = linMAX;
        
        while(low<=high){
            int mid = (low+high)/2;
            long long tmp = func(a,b,c,d,mid);
            if(tmp == fn){
                cout<<mid<<endl;
                break;
            }else if(tmp < fn)low=mid+1;
            else high=mid-1;
        }
    }


    return 0;
}