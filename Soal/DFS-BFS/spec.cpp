#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec {
protected:

    int N,M;
    const int NMAX = 1000;
    vector<vector<int>> Jaring;

    int ans;
    void InputFormat() {
        LINE(N, M);
        LINES(Jaring) % SIZE(N);
    }

    void OutputFormat() {
        LINE(ans);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(256);
    }

    void Constraints() {
        CONS(0 < N && N <= NMAX);
        CONS(0 < M && M <= NMAX);
        CONS(JaringCons(Jaring));
    }
private:
    bool JaringCons(vector<vector<int>> Jaring){
        bool inbound = true;
        for(int i=0;i<Jaring.size();i++){
            for(int j=0;j<Jaring[0].size();j++){
                if(Jaring[i][j] > 1 || Jaring[i][j] < 0){
                    inbound = false;
                }
            }
        }
        return inbound;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "4 4",
            "1 0 1 0",
            "0 1 0 1",
            "1 0 1 0",
            "0 1 0 1"
        });
        Output({
            "8"
        });
    }
    
    void SampleTestCase2() {
        Input({
            "4 4",
            "1 0 1 0",
            "0 0 0 1",
            "0 0 1 0",
            "0 1 0 1"
        });
        Output({
            "5"
        });
    }

    void SampleTestCase3() {
        Input({
            "2 3",
            "1 0 1",
            "1 1 1"
        });
        Output({
            "5"
        });
    }

    void BeforeTestCase() {
        Jaring.clear();
    }

    void TestCases() {
        for(int i=0;i<10;i++){
            CASE(N = 10, M = 10, random_jaring(N,M,Jaring,10*i+5));
        }
        for (int i=0;i<10;i++){
            CASE(N = rnd.nextInt(1,NMAX), M = rnd.nextInt(1,NMAX), random_jaring(N,M,Jaring,0));
        }
        for (int i=0;i<10;i++){
            CASE(N = rnd.nextInt(1,NMAX), M = rnd.nextInt(1,NMAX), random_jaring(N,M,Jaring,(N*M)/2));
        }
        for (int i=0;i<5;i++){
            CASE(N = rnd.nextInt(1,NMAX), M = rnd.nextInt(1,NMAX), random_jaring(N,M,Jaring,rnd.nextInt(0,N*M)));
        }
        for (int i=0;i<5;i++){
            CASE(N = NMAX, M = NMAX, random_jaring(N,M,Jaring,rnd.nextInt(0,N*M)));
        }
        for (int i=0;i<5;i++){
            CASE(N = rnd.nextInt(1,NMAX), M = rnd.nextInt(1,NMAX), random_jaring(N,M,Jaring,N*M-i));
        }
    }

private:
    void random_jaring(int N, int M, vector<vector<int>>& Jaring, int Ncount){
        Jaring.assign(N, vector<int>(M));
        while(Ncount > 0){
            for(int i=0;i<N;i++){
                for(int j=0;j<M;j++){
                    int x = rnd.nextInt(0,1);
                    if(Ncount > 0 && x == 1 && Jaring[i][j] == 0){
                        Jaring[i][j] = 1;
                        Ncount--;
                    }
                }
            }
        }
    }
};