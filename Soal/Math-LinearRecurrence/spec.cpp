#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec
{
protected:
    unsigned long long N;
    int M;
    vector<long long> F, K;
    long long ans;

    unsigned long long NMax = 1e19;
    int MMax = 100;
    int FMax = 1e9;

    void InputFormat()
    {
        LINE(N);
        LINE(M);
        LINE(F);
        LINE(K);
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
        CONS(1 <= N && N <= NMax);
        CONS(1 <= M && M <= MMax);
        CONS(vectorConstraint(F));
        CONS(vectorConstraint(K));
    }

private:
    bool vectorConstraint(vector<long long> &vec)
    {
        for (auto x : vec)
        {
            if (x < 1 || x > FMax)
                return false;
        }
        return true;
    }
};
class TestSpec : public BaseTestSpec<ProblemSpec>
{
protected:
    void SampleTestCase1()
    {
        Input({"4",
               "3",
               "8 4 4",
               "2 2 1"});
        Output({"12"});
    }

    void BeforeTestCase()
    {
        F.clear();
        K.clear();
    }

    void TestCases()
    {
        CASE(N = 4, M = 2, F = {2, 1}, K = {1, 1});
        CASE(N = 1, M = 3, F = {305, 205, 105}, K = {105, 205, 305});
        CASE(N = 3, M = 3, F = {305, 205, 105}, K = {105, 205, 305});
        for (int i = 0; i < 10; i++)
        {
            CASE(N = 50, M = 10, randomFill(M, F), randomFill(M, K));
        }
        for (int i = 0; i < 10; i++)
        {
            CASE(N = 1e5, M = 100, randomFill(M, F), randomFill(M, K));
        }
        for (int i = 0; i < 10; i++)
        {
            CASE(N = 1e18, M = 10, randomFill(M, F), randomFill(M, K));
        }
        for (int i = 0; i < 10; i++)
        {
            CASE(N = 1e18, M = 100, randomFill(M, F), randomFill(M, K));
        }
        for (int i = 0; i < 15; i++)
        {
            CASE(N = 1e19, M = 100, randomFill(M, F), randomFill(M, K));
        }
    }

private:
    void randomFill(int sz, vector<long long> &vec)
    {
        vec.resize(sz);
        for (long long &x : vec)
        {
            x = rnd.nextLongLong(1, FMax);
        }
    }
};