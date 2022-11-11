#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec {
protected:
    int Q;
    vector<long long> N;
    const int QMAX = 1e5;
    const long long NMAX = 1e18;

    vector<long long> ans;
    void InputFormat() {
        LINE(Q);
        LINES(N) % SIZE(Q);
    }

    void OutputFormat() {
        LINES(ans);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(256);
    }

    void Constraints() {
        CONS(0 < Q && Q <= QMAX);
        CONS(array_cons(N));
    }
private:
    bool array_cons(vector<long long> N){
        bool inbound = true;
        for(long long num : N){
            if(num <= 0 || num > NMAX){
                inbound = false;
            }
        }
        return inbound;
    }

};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "3",
            "8",
            "3",
            "4"
        });
        Output({
            "24",
            "12",
            "14"
        });
    }
    
    void BeforeTestCase() {
        N.clear();
        ans.clear();
    }

    void TestCases() {
        CASE(Q = QMAX, onetomax(N));
        for(int i = 0;i<20;i++)CASE(Q = rnd.nextInt(1, QMAX), random_array(N, Q, QMAX, 1e9));
        for(int i = 0;i<20;i++)CASE(Q = QMAX, random_array(N, Q, QMAX, NMAX));
    }

private:
    void onetomax(vector<long long> &N){
        for(int i=1;i<=QMAX;i++){
            N.push_back(i);
        }
    }

    void random_array(vector<long long> &N, int size, long long lower, long long upper){
        for(int i=0;i<size;i++){
            long long x = rnd.nextLongLong(lower, upper);
            N.push_back(x);
        }
    }
};