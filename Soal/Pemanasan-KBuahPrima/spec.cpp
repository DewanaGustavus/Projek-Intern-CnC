#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec {
protected:
    int Q;
    vector<int> K, L, R;
    const int QMAX = 1e5;
    const int NMAX = 1e5;
    const int KMAX = 1e9; 

    vector<int> ans;
    void InputFormat() {
        LINE(Q);
        LINES(K, L, R) % SIZE(Q);
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
        CONS(array_cons(K, L, R));
    }
private:
    bool array_cons(vector<int> K, vector<int> L, vector<int> R){
        int nk = K.size();
        int nl = L.size();
        int nr = R.size();
        if(nk != nl || nk != nr)return false;
        for(int i=0;i<nk;i++){
            if(K[i] < 1 || K[i] > KMAX)return false;
            if(L[i] > R[i])return false;
            if(R[i] > NMAX || L[i] < 2)return false;
        }
        return true;
    }

};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "2",
            "2 6 15",
            "1 2 8"
        });
        Output({
            "5",
            "6"
        });
    }
    
    void BeforeTestCase() {
        K.clear();
        L.clear();
        R.clear();
    }

    void TestCases() {
        for(int i=0;i<3;i++)CASE(Q = rnd.nextInt(10,100), random_case(Q, 2,100,K,L,R));
        for(int i=0;i<3;i++)CASE(Q = rnd.nextInt(100,1e3), random_case(Q, 100,1e4,K,L,R));
        for(int i=0;i<3;i++)CASE(Q = rnd.nextInt(1e3,1e4), random_case(Q, 1e3,NMAX,K,L,R));
        CASE(Q = QMAX, random_case(Q, 2,NMAX,K,L,R));
        CASE(Q = QMAX, nonsense_k(Q, K, L, R));
    }

private:
    void random_case(int q, int minl, int maxr, vector<int>& K, vector<int>& L, vector<int>& R){
        for(int i=0;i<q;i++){
            int k = rnd.nextInt(1, 7);
            int l = rnd.nextInt(minl, maxr);
            int r = rnd.nextInt(l, maxr);
            K.push_back(k);
            L.push_back(l);
            R.push_back(r);
        }
    }
    void nonsense_k(int q, vector<int>& K, vector<int>& L, vector<int>& R){
        for(int i=0;i<q;i++){
            K.push_back(rnd.nextInt(8, KMAX));
            L.push_back(rnd.nextInt(2,20));
            R.push_back(rnd.nextInt(100, NMAX));
        }
    }
};