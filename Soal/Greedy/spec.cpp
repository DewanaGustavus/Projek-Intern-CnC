#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec {
protected:

    int N;
    const int NMAX = 1e6;
    string duduk;

    long long ans;
    void InputFormat() {
        LINE(duduk);
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
        CONS(duduk.size() == N);
    }
private:

};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "....x..xx...x.."
        });
        Output({
            "5"
        });
    }
    
    void SampleTestCase2() {
        Input({
            "........ xxxxxxx.xxxxxx .......x.."
        });
        Output({
            "14"
        });
    }

    void BeforeTestCase() {
        duduk.clear();
    }

    void TestCases() {
        for(int i=0;i<10;i++){
            CASE(N = 10, random_duduk(N, duduk, i+1));
        }
        for(int i=0;i<10;i++){
            CASE(N = 10*(i+1), random_duduk(N, duduk, N/2));
        }
        for(int i=0;i<10;i++){
            CASE(N = 1000, random_duduk(N, duduk, rnd.nextInt(1,N)));;
        }
        for(int i=0;i<5;i++){
            CASE(N = NMAX, random_duduk(N, duduk, NMAX/2));
        }
        for(int i=0;i<5;i++){
            CASE(N = NMAX, random_duduk(N, duduk, sqrt(NMAX)));
        }
        for (int i=0;i<10;i++){
            CASE(N = rnd.nextInt(1,NMAX), random_duduk(N,duduk,rnd.nextInt(1,N)));
        }
        for (int i=0;i<10;i++){
            CASE(N = NMAX, random_duduk(N,duduk,rnd.nextInt(1,NMAX)));
        }
    }

private:
    void random_duduk(int N, string& duduk, int Ncount){
        duduk = string(N, '.');
        while(Ncount > 0){
            for(int i=0;i<N;i++){
                int x = rnd.nextInt(0,1);
                if(Ncount > 0 && x == 1 && duduk[i] == '.'){
                    duduk[i] = 'x';
                    Ncount--;
                }
            }
        }
    }
};