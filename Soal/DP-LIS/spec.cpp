#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec {
protected:

    int N;
    const int NMAX = 1e4;
    vector<int> lenX, lenY, lenZ;

    int ans;
    void InputFormat() {
        LINE(N);
        LINES(lenX, lenY, lenZ);
    }

    void OutputFormat() {
        LINE(ans);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(256);
    }

    void Constraints() {
        CONS(1 < N && N <= NMAX);
        CONS(LenCons(lenX));
        CONS(LenCons(lenY));
        CONS(LenCons(lenZ));
    }
private:
    bool LenCons(vector<int> len) {
        const int LIM_SZ = 1e5;
        for(int &x : len) {
            if(! (1 <= x && x <= LIM_SZ)) return false;
        }
        return true;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "6",
            "1 5 4",
            "1 2 2",
            "2 3 2",
            "2 4 1",
            "3 6 2",
            "4 5 3"
        });
        Output({
            "7"
        });
    }
    
    void SampleTestCase2() {
        Input({
            "5",
            "5 12 13",
            "5 10 6",
            "5 11 8",
            "5 6 7",
            "5 8 10"
        });
        Output({
            "13"
        });
    }

    void BeforeTestCase() {
        lenX.clear();
        lenY.clear();
        lenZ.clear();
    }

    void TestCases(){
        for(int i = 0; i < 5; i++) CASE(N = 5, random_size(N, lenX, lenY, lenZ));    
        for(int i = 0; i < 2; i++) CASE(N = 10, random_size(N, lenX, lenY, lenZ));
        for(int i = 0; i < 5; i++) CASE(N = 100, random_size(N, lenX, lenY, lenZ));
        for(int i = 0; i < 5; i++) CASE(N = 1e3, random_size(N, lenX, lenY, lenZ));
        for(int i = 0; i < 5; i++) CASE(N = 1e4, random_size(N, lenX, lenY, lenZ));    
    }

private:
    void random_size(int N, vector<int> &lenX, vector<int> &lenY, vector<int> &lenZ) {
        const int LIM_SZ = 1e5;
        lenX.resize(N);
        lenY.resize(N);
        lenZ.resize(N);
        for(int i = 0; i < N; i++) {
            lenX[i] = rnd.nextInt(1, LIM_SZ);
            lenY[i] = rnd.nextInt(1, LIM_SZ);
            lenZ[i] = rnd.nextInt(1, LIM_SZ);
        }
    }
};