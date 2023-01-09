#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec
{
protected:
    int T;
    vector<int> X, N;
    vector<string> op;

    vector<vector<int>> ans;

    int TMAX = 1000, NMAX = 1000, XMAX = 1e9;

    void InputFormat()
    {
        LINE(T);
        LINES(X, N, op) % SIZE(T);
    }

    void StyleConfig()
    {
        CustomScorer();
    }

    void OutputFormat()
    {
        LINES(ans);
    }

    void GradingConfig()
    {
        TimeLimit(1);
        MemoryLimit(256);
    }

    void Constraints()
    {
        CONS(1 <= T && T <= TMAX);
        CONS(X.size() == T);
        CONS(N.size() == T);
        CONS(op.size() == T);
        CONS(vectorConstraint(X, 1, XMAX));
        CONS(vectorConstraint(N, 1, NMAX));
        CONS(opConstraint(op));
    }

private:
    bool vectorConstraint(const vector<int> &vec, int lb, int ub)
    {
        for (int x : vec)
        {
            if (x < lb || x > ub)
                return false;
        }
        return true;
    }
    bool opConstraint(const vector<string> &op)
    {
        for (string x : op)
        {
            if (x != "AND" && x != "OR" && x != "XOR")
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
        Input({"3",
               "4 2 AND",
               "11 3 OR",
               "2 3 XOR"});
        Output({"12 4",
                "1 2 8",
                "2 2 2"});
    }

    void BeforeTestCase()
    {
        X.clear();
        N.clear();
        op.clear();
    }

    void TestCases()
    {
        CASE(T = 5, X = {6, 2141, 10, 1, 805306367}, N = {1, 1, 1, 2, 4}, op = {"AND", "OR", "XOR", "XOR", "XOR"});
        CASE(T = 4, X = {1, 1000000000, 536870911, 536870912}, N = {2, 4, 6, 8}, op = {"XOR", "XOR", "XOR", "XOR"});
        for (int i = 0; i < 5; i++)
            CASE(T = 10, randomTC(T, X, N, op));
        for (int i = 0; i < 5; i++)
            CASE(T = 10, randomEvenXOR(T, X, N, op));
        for (int i = 0; i < 5; i++)
            CASE(T = 1000, randomTC(T, X, N, op));
        for (int i = 0; i < 5; i++)
            CASE(T = 1000, randomEvenXOR(T, X, N, op));
        for (int i = 0; i < 10; i++)
            CASE(T = 1000, randomTC(T, X, N, op));
        for (int i = 0; i < 20; i++)
            CASE(T = 1000, randomEvenXOR(T, X, N, op));
    }

private:
    void randomTC(int T, vector<int> &x, vector<int> &n, vector<string> &op)
    {
        string operators[] = {"AND", "OR", "XOR"};
        for (int i = 0; i < T; i++)
        {
            x.push_back(rnd.nextInt(1, XMAX));
            n.push_back(rnd.nextInt(1, NMAX));
            op.push_back(operators[rnd.nextInt(3)]);
        }
    }

    void randomEvenXOR(int T, vector<int> &x, vector<int> &n, vector<string> &op)
    {
        for (int i = 0; i < T; i++)
        {
            x.push_back(rnd.nextInt(1, XMAX));
            n.push_back(rnd.nextInt(1, NMAX / 2) * 2);
            op.push_back("XOR");
        }
    }
};