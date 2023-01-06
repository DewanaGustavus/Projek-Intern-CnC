#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;
// typedef long long ll;
#define ll long long

class ProblemSpec : public BaseProblemSpec {
protected:
    ll Q;
    vector<ll> A,B,C,D;
    vector<ll> FN;
    vector<ll> ans;

    const ll QMAX = 1e5;
    const ll NMAX = 100;
    const ll FMAX = 1e15;
    
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
    bool polynomCONS(vector<ll> constants){
        for(ll constant : constants){
            if(constant < 0 || constant > NMAX)return false;
        }
        return true;
    }
    bool functionCONS(vector<ll> values){
        for(ll value : values){
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
        // linear
        for (int i=0;i<3;i++)CASE(Q = rnd.nextInt(1, QMAX), make_linear_query(Q,A,B,C,D,FN));
        CASE(Q=QMAX, make_linear_query(Q,A,B,C,D,FN));

        // quadratic
        for (int i=0;i<3;i++)CASE(Q = rnd.nextInt(1, QMAX), make_quadratic_query(Q,A,B,C,D,FN));
        CASE(Q=QMAX, make_quadratic_query(Q,A,B,C,D,FN));
        
        // cubic
        for (int i=0;i<3;i++)CASE(Q = rnd.nextInt(1, QMAX), make_cubic_query(Q,A,B,C,D,FN));
        CASE(Q=QMAX, make_cubic_query(Q,A,B,C,D,FN));

        // random and edge case
        for (int i=0;i<3;i++)CASE(Q = QMAX, make_random_query(Q,A,B,C,D,FN));
        CASE(Q=QMAX, make_random_query(Q,A,B,C,D,FN));
        CASE(Q=9e4, edge_case(Q,A,B,C,D,FN));
    }

private:
    long long func(ll a, ll b, ll c, ll d, long long x){ // f(x)
        long long ret = a*x*x*x;
        ret += b*x*x;
        ret += c*x;
        ret += d;
        return ret;
    }

    ll linMAX = 1e11;
    ll quadMAX = 1e6;
    ll cubMAX = 1e4;

    void make_linear(vector<ll>& A, vector<ll>& B, vector<ll>& C, vector<ll>& D, vector<ll>& FN){
        ll a = 0;
        ll b = 0;
        ll c = rnd.nextLongLong(1,NMAX);
        ll d = rnd.nextLongLong(0,NMAX);

        long long n;
        long long fn;
        do{
            n = rnd.nextLongLong(0, linMAX);
            fn = func(a,b,c,d,n);
        }while(fn > FMAX);
        A.push_back(a);
        B.push_back(b);
        C.push_back(c);
        D.push_back(d);
        FN.push_back(fn);
    }

    void make_quadratic(vector<ll>& A, vector<ll>& B, vector<ll>& C, vector<ll>& D, vector<ll>& FN){
        ll a = 0;
        ll b = rnd.nextLongLong(1,NMAX);
        ll c = rnd.nextLongLong(0,NMAX);
        ll d = rnd.nextLongLong(0,NMAX);

        long long n;
        long long fn;
        do{
            n = rnd.nextLongLong(0, quadMAX);
            fn = func(a,b,c,d,n);
        }while(fn > FMAX);
        A.push_back(a);
        B.push_back(b);
        C.push_back(c);
        D.push_back(d);
        FN.push_back(fn);
    }

    void make_cubic(vector<ll>& A, vector<ll>& B, vector<ll>& C, vector<ll>& D, vector<ll>& FN){
        ll a = rnd.nextLongLong(1,NMAX);
        ll b = rnd.nextLongLong(0,NMAX);
        ll c = rnd.nextLongLong(0,NMAX);
        ll d = rnd.nextLongLong(0,NMAX);

        long long n;
        long long fn;
        do{
            n = rnd.nextLongLong(0, cubMAX);
            fn = func(a,b,c,d,n);
        }while(fn > FMAX);
        A.push_back(a);
        B.push_back(b);
        C.push_back(c);
        D.push_back(d);
        FN.push_back(fn);
    }

    void make_linear_query(ll Q, vector<ll>& A, vector<ll>& B, vector<ll>& C, vector<ll>& D, vector<ll>& FN){
        for(ll i=0;i<Q;i++){
            make_linear(A,B,C,D,FN);
        }
    }

    void make_quadratic_query(ll Q, vector<ll>& A, vector<ll>& B, vector<ll>& C, vector<ll>& D, vector<ll>& FN){
        for(ll i=0;i<Q;i++){
            make_quadratic(A,B,C,D,FN);
        }
    }

    void make_cubic_query(ll Q, vector<ll>& A, vector<ll>& B, vector<ll>& C, vector<ll>& D, vector<ll>& FN){
        for(ll i=0;i<Q;i++){
            make_cubic(A,B,C,D,FN);
        }
    }

    void make_random_query(ll Q, vector<ll>& A, vector<ll>& B, vector<ll>& C, vector<ll>& D, vector<ll>& FN){
        for(ll i=0;i<Q;i++){
            ll r = rnd.nextLongLong(1,3);
            if(r == 1)make_linear(A,B,C,D,FN);
            if(r == 2)make_quadratic(A,B,C,D,FN);
            if(r == 3)make_cubic(A,B,C,D,FN);
        }
    }

    void edge_case(ll Q, vector<ll>& A, vector<ll>& B, vector<ll>& C, vector<ll>& D, vector<ll>& FN){
        int Qq = 3e4;
        ll a,b,c,d,n,fn;

        // linear
        a=0;b=0;c=1;
        ll linmax1 = 1e13, linmax2 = 5e14;
        for(int i=0;i<Qq;i++){
            d = rnd.nextLongLong(0,NMAX);
            n = rnd.nextLongLong(linmax1, linmax2);
            fn = func(a,b,c,d,n);
            A.push_back(a);
            B.push_back(b);
            C.push_back(c);
            D.push_back(d);
            FN.push_back(fn);
        }

        // quadratic
        a=0;b=1;c=0;
        ll quadmax1 = 1e5, quadmax2 = 3e6;
        for(int i=0;i<Qq;i++){
            d = rnd.nextLongLong(0,NMAX);
            n = rnd.nextLongLong(quadmax1, quadmax2);
            fn = func(a,b,c,d,n);
            A.push_back(a);
            B.push_back(b);
            C.push_back(c);
            D.push_back(d);
            FN.push_back(fn);
        }

        // cubic
        a=1;b=0;c=0;
        ll cubmax1 = 3e3, cubmax2 = 1e4;
        for(int i=0;i<Qq;i++){
            d = rnd.nextLongLong(0,NMAX);
            n = rnd.nextLongLong(cubmax1, cubmax2);
            fn = func(a,b,c,d,n);
            A.push_back(a);
            B.push_back(b);
            C.push_back(c);
            D.push_back(d);
            FN.push_back(fn);
        }
    }
};