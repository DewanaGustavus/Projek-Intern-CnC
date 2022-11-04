#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec {
protected:
    int Q;
    vector<int> A,B,C,D;
    vector<int> FN;
    vector<int> ans;

    const int QMAX = 1e5;
    const int NMAX = 50;
    const int FMAX = 1e9;
    
    void InputFormat() {
        LINE(Q);
        LINES(A,B,C,D,FN) % SIZE(Q);
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
        CONS(polynomCONS(A));
        CONS(polynomCONS(B));
        CONS(polynomCONS(C));
        CONS(polynomCONS(D));
        CONS(functionCONS(FN));
    }
private:
    bool polynomCONS(vector<int> constants){
        for(int constant : constants){
            if(constant < 0 || constant > NMAX)return false;
        }
        return true;
    }
    bool functionCONS(vector<int> values){
        for(int value : values){
            if(value < 0 || value > FMAX)return false;
        }
        return true;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "1",
            "1 2 3 5 27"
        });
        Output({
            "2"
        });
    }
    
    void SampleTestCase2() {
        Input({
            "3",
            "0 0 1 5 7",
            "1 0 0 3 30",
            "12 23 34 0 0"
        });
        Output({
            "2",
            "3",
            "0"
        });
    }

    void BeforeTestCase() {
        A.clear();
        B.clear();
        C.clear();
        D.clear();
        FN.clear();
    }

    void TestCases() {
        CASE(Q = 3, A = {0,0,1}, B = {0,1,0}, C = {1,0,0}, D = {0,0,0}, FN = {0,0,0});
        for (int i=0;i<3;i++){ // linear
            CASE(Q = rnd.nextInt(1, QMAX), make_linear_query(Q,A,B,C,D,FN));
        }
        for (int i=0;i<3;i++){ // quadratic
            CASE(Q = rnd.nextInt(1, QMAX), make_quadratic_query(Q,A,B,C,D,FN));
        }
        for (int i=0;i<3;i++){ // cubic
            CASE(Q = rnd.nextInt(1, QMAX), make_cubic_query(Q,A,B,C,D,FN));
        }
        for (int i=0;i<3;i++){
            CASE(Q = QMAX, make_random_query(Q,A,B,C,D,FN));
        }
    }

private:
    long long func(int a, int b, int c, int d, long long x){ // f(x)
        long long ret = a*x*x*x;
        ret += b*x*x;
        ret += c*x;
        ret += d;
        return ret;
    }

    int linMAX = 1e9;
    int quadMAX = 1e5;
    int cubMAX = 1e3;

    void make_linear(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D, vector<int>& FN){
        int a = 0;
        int b = 0;
        int c = rnd.nextInt(1,NMAX);
        int d = rnd.nextInt(0,NMAX);

        long long n;
        long long fn;
        do{
            n = rnd.nextInt(0, linMAX);
            fn = func(a,b,c,d,n);
        }while(fn > FMAX);
        A.push_back(a);
        B.push_back(b);
        C.push_back(c);
        D.push_back(d);
        FN.push_back(fn);
    }

    void make_quadratic(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D, vector<int>& FN){
        int a = 0;
        int b = rnd.nextInt(1,NMAX);
        int c = rnd.nextInt(0,NMAX);
        int d = rnd.nextInt(0,NMAX);

        long long n;
        long long fn;
        do{
            n = rnd.nextInt(0, quadMAX);
            fn = func(a,b,c,d,n);
        }while(fn > FMAX);
        A.push_back(a);
        B.push_back(b);
        C.push_back(c);
        D.push_back(d);
        FN.push_back(fn);
    }

    void make_cubic(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D, vector<int>& FN){
        int a = rnd.nextInt(1,NMAX);
        int b = rnd.nextInt(0,NMAX);
        int c = rnd.nextInt(0,NMAX);
        int d = rnd.nextInt(0,NMAX);

        long long n;
        long long fn;
        do{
            n = rnd.nextInt(0, cubMAX);
            fn = func(a,b,c,d,n);
        }while(fn > FMAX);
        A.push_back(a);
        B.push_back(b);
        C.push_back(c);
        D.push_back(d);
        FN.push_back(fn);
    }

    void make_linear_query(int Q, vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D, vector<int>& FN){
        for(int i=0;i<Q;i++){
            make_linear(A,B,C,D,FN);
        }
    }

    void make_quadratic_query(int Q, vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D, vector<int>& FN){
        for(int i=0;i<Q;i++){
            make_quadratic(A,B,C,D,FN);
        }
    }

    void make_cubic_query(int Q, vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D, vector<int>& FN){
        for(int i=0;i<Q;i++){
            make_cubic(A,B,C,D,FN);
        }
    }

    void make_random_query(int Q, vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D, vector<int>& FN){
        for(int i=0;i<Q;i++){
            int r = rnd.nextInt(1,3);
            if(r == 1)make_linear(A,B,C,D,FN);
            if(r == 2)make_quadratic(A,B,C,D,FN);
            if(r == 3)make_cubic(A,B,C,D,FN);
        }
    }
};