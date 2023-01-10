#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec
{
protected:
    int N, M, K;
    vector<int> U, V, W;
    long long ans;

    const int NMAX = 2e5;
    const int WMAX = 1e5;

    void InputFormat()
    {
        LINE(N, M, K);
        LINES(U, V, W) % SIZE(M);
    }

    void OutputFormat()
    {
        LINE(ans);
    }

    void GradingConfig()
    {
        TimeLimit(1);
        MemoryLimit(256);
    }

    void Constraints()
    {
        CONS(1 <= N && N <= NMAX);
        CONS(check_m(N, M));
        CONS(1 <= K && K <= N);
        CONS(edge_cons(U, V, W, N, M));
    }

private:
    bool check_m(int n, int m){
        long long tmp = n;
        tmp *= n-1;
        return 0 <= m && m <= NMAX && m <= tmp;

    }
    bool edge_cons(vector<int>& U, vector<int>& V, vector<int>& W, int N, int M){
        if(U.size() != M || V.size() != M || W.size() != M)return false;

        set<pair<int,int>> edges;
        for(int i=0;i<M;i++){
            if(1 < W[i] && W[i] > WMAX)return false;
            if(U[i] == V[i])return false; // self loop
            pair<int,int> tmp = {U[i], V[i]};
            if(edges.count(tmp))return false; // multi edge
            edges.insert(tmp);
        }
        return true;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec>
{
protected:
    void SampleTestCase1()
    {
        Input({
            "7 6 4",
            "5 4 1",
            "1 4 1",
            "6 5 2",
            "2 1 2",
            "6 2 10",
            "1 3 10"});
        Output({"2"});
    }

    void BeforeTestCase()
    {
        U.clear();
        V.clear();
        W.clear();
    }

    void TestCases()
    {
        for(int i=0;i<3;i++)CASE(N = rnd.nextInt(1,100), M = rndM(N), K = rnd.nextInt(1,N), random_graph(N,M,10,U,V,W));
        for(int i=0;i<3;i++)CASE(N = rnd.nextInt(1,100), M = N*(N-1), K = rnd.nextInt(1,N), random_graph(N,M,10,U,V,W));
        for(int i=0;i<3;i++)CASE(N = rnd.nextInt(100,1e4), M = rndM(N), K = rnd.nextInt(1,N), random_graph(N,M,100,U,V,W));
        for(int i=0;i<3;i++)CASE(N = rnd.nextInt(1,NMAX), M = rndM(N), K = rnd.nextInt(1,N), random_graph(N,M,1000,U,V,W));
        for(int i=0;i<3;i++)CASE(N = rnd.nextInt(NMAX), M = NMAX, K = rnd.nextInt(1,N), random_graph(N,M,WMAX,U,V,W));
        for(int i=0;i<3;i++)CASE(N = rnd.nextInt(1e3, 1e4), M = NMAX, K = rnd.nextInt(1,N), random_graph(N,M,50,U,V,W));
        CASE(N = NMAX, M = 0, U.clear(), V.clear(), W.clear());   
    }

private:
    int rndM(int n){
        long long tmp = n;
        tmp *= n-1;
        return rnd.nextInt(0, min((long long)NMAX, tmp));
    }
    void random_graph(int n, int m, int maxw, vector<int>& U, vector<int>& V, vector<int>& W){
        set<pair<int,int>> selected;
        for(int i=0;i<m;i++){
            int a,b;
            do{
                a = rnd.nextInt(1,n);
                b = rnd.nextInt(1,n);
            }while(a == b || selected.count({a,b}));
            selected.insert({a,b});
            U.push_back(a);
            V.push_back(b);
            W.push_back(rnd.nextInt(1,maxw));
        }
    }
};