#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec
{
protected:
    int N, M;
    const int NMAX = 100, XMAX = 1e9;
    vector<int> a;
    vector<int> I, J;

    int ans;
    void InputFormat()
    {
        LINE(N, M);
        LINE(a);
        LINES(I, J);
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
        CONS(1 < N && N <= NMAX);
        CONS(1 <= M && M <= NMAX);
        CONS(M <= (N / 2) * ((N + 1) / 2));
        CONS(arrConstraints(a));
        CONS(pairConstraints(I, J));
    }

private:
    bool arrConstraints(vector<int> &A)
    {
        if (A.size() != N)
            return false;
        for (int &x : A)
        {
            if (x < 1 || x > XMAX)
                return false;
        }
        return true;
    }
    bool pairConstraints(vector<int> &I, vector<int> &J)
    {
        if (I.size() != M || J.size() != M)
            return false;
        set<pair<int, int>> s;
        for (int i = 0; i < I.size(); i++)
        {
            if (s.count({I[i], J[i]}) || s.count({J[i], I[i]}))
                return false;
            s.insert({I[i], J[i]});
        }
        return true;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec>
{
protected:
    void SampleTestCase1()
    {
        Input({"3 2",
               "8 12 8",
               "1 2",
               "2 3"});
        Output({"2"});
    }

    void BeforeTestCase()
    {
        a.clear();
        I.clear();
        J.clear();
    }

    void TestCases()
    {
        for (int i = 0; i < 5; i++)
            CASE(N = 3, M = 2, randomTC(N, M, a, I, J));
        for (int i = 0; i < 5; i++)
            CASE(N = 10, M = 5, randomTC(N, M, a, I, J));
        for (int i = 0; i < 5; i++)
            CASE(N = 10, M = 25, randomTC(N, M, a, I, J));
        for (int i = 0; i < 5; i++)
            CASE(N = 20, M = 50, randomTC(N, M, a, I, J));
        for (int i = 0; i < 5; i++)
            CASE(N = 40, M = 50, randomTC(N, M, a, I, J));
        for (int i = 0; i < 3; i++)
            CASE(N = 50, M = 3, randomTC(N, M, a, I, J));
        for (int i = 0; i < 4; i++)
            CASE(N = 50, M = 100, randomTC(N, M, a, I, J));
        for (int i = 0; i < 3; i++)
            CASE(N = 100, M = 100, randomTC(N, M, a, I, J));
    }

private:
    void randomTC(int N, int M, vector<int> &A, vector<int> &I, vector<int> &J)
    {
        A.resize(N);
        for (int &x : A)
            x = rnd.nextInt(1, XMAX);
        I.resize(M);
        J.resize(M);

        vector<pair<int, int>> shuffler;
        shuffler.clear();
        for (int i = 1; i <= N; i++)
            for (int j = i + 1; j <= N; j++)
            {
                if ((i + j) % 2)
                    shuffler.emplace_back(i, j);
            }
        rnd.shuffle(shuffler.begin(), shuffler.end());

        for (int i = 0; i < M; i++)
        {
            I[i] = shuffler[i].first;
            J[i] = shuffler[i].second;
        }
    }
};