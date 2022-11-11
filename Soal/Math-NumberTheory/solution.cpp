#include <bits/stdc++.h>

int main(){
    #define int long long
    int q;std::cin>>q;
while(q--){
    int n;std::cin>>n;
    std::priority_queue<int, std::vector<int>, std::greater<int>> pow2;
    for(int i=1;i<64;i++){
        pow2.push((1LL << i));
    }
    int ans = 2*n - 2;
    while(ans >= pow2.top()){
        pow2.pop();
        ans += 2;
    }
    std::cout<<ans<<std::endl;
}


    return 0;
}