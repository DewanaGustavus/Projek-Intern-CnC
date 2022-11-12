#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec {
protected:
    int Q;
    vector<vector<int>> quers; // {{N,M}, {vector P}}
    const int QMAX = 1e4;
    const int NMAX = 1e3;

    vector<int> ans;
    void InputFormat() {
        LINE(Q);
        LINES(quers) % SIZE(2*Q);
    }

    void OutputFormat() {
        LINES(ans) % SIZE(Q);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(256);
    }

    void Constraints() {
        CONS(0 < Q && Q <= QMAX);
        CONS(queryCons(quers));
    }
private:
    bool queryCons(vector<vector<int>> quers){
        bool inbound = true;
        for(int i=0;i<2*Q;i+=2){
            int N = quers[i][0];
            int M = quers[i][1];
            vector<int> P = quers[i+1];
            if(P.size() != M)inbound = false;
            if(N > NMAX || M > N)inbound = false;

            int tot = 0;
            for(int num : P){
                if(num <= 0)inbound = false;
                tot += num;
            }
            // if(tot != N)inbound = false;
        }
        return inbound;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "1",
            "5 3",
            "3 1 1"
        });
        Output({
            "20"
        });
    }
    
    void BeforeTestCase() {
        quers.clear();
    }

    void TestCases(){
        for(int i=0;i<10;i++)CASE(Q = 5, random_filling(Q, 10, quers));
        for(int i=0;i<10;i++)CASE(Q = rnd.nextInt(1,QMAX), random_filling(Q, NMAX, quers));
        for(int i=0;i<10;i++)CASE(Q = QMAX, random_filling(Q, rnd.nextInt(1,NMAX), quers));
        for(int i=0;i<10;i++)CASE(Q = rnd.nextInt(1,QMAX), random_filling(Q, rnd.nextInt(1,NMAX), quers));
        for(int i=0;i<10;i++)CASE(Q = QMAX, random_filling(Q, NMAX, quers));
    }

private:
    void random_filling(int Q, int Nlim, vector<vector<int>>&quers){
        for(int i=0;i<Q;i++){
            int total = rnd.nextInt(1,Nlim);
            int length = rnd.nextInt(1,total);
            quers.push_back({total, length});
            vector<int> tmp(length, 1);
            int need = total - length;
            for(int i=0;i<length;i++){
                int add = rnd.nextInt(0, need/5);
                need -= add;
                tmp[i] += add;
            }
            for(int i=0;i<length;i++){
                int add = rnd.nextInt(0, need);
                need -= add;
                tmp[i] += add;
            }
            quers.push_back(tmp);
        }
    }

};