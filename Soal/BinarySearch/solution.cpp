#include <bits/stdc++.h>
using namespace std;

long long func(int a, int b, int c, int d, long long x){ // f(x)
    long long ret = a*x*x*x;
    ret += b*x*x;
    ret += c*x;
    ret += d;
    return ret;
}

int main(){
    int q;
    cin>>q;
    int linMAX = 1e9;
    int quadMAX = 1e5;
    int cubMAX = 1e3;

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