#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec {
protected:
    int N;
    const int NMAX = 1e6;
    int ans;
    void InputFormat() {
        LINE(N);
    }

    void OutputFormat() {
        LINE(ans);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(256);
    }

    void Constraints() {
        CONS(0 <= N <= NMAX);
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "29"
        });
        Output({
            "5"
        });
    }
    
    void TestCases() {
        for(int i=0;i<3;i++)CASE(N = rnd.nextInt(1,50));
        for(int i=0;i<3;i++)CASE(N = rnd.nextInt(50,200));
        for(int i=0;i<3;i++)CASE(N = rnd.nextInt(200,3000));
        for(int i=0;i<3;i++)CASE(N = rnd.nextInt(3000,1e5));
        for(int i=0;i<3;i++)CASE(N = rnd.nextInt(1e5,1e6));
        CASE(N = 9722);
        CASE(N = 37882);
        CASE(N = 103330);
        CASE(N = 562167);
        CASE(N = 991919);
        CASE(N = 0);
    }
};