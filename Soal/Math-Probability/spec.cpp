#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec
{
protected:
    int K;
    string S, T;
    double ans;

    int KMax = 1e5;

    void InputFormat()
    {
        LINE(K);
        LINE(S);
        LINE(T);
    }

    void StyleConfig()
    {
        CustomScorer();
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
        CONS(2 <= K && K <= KMax);
        CONS(strConstraint(S));
        CONS(strConstraint(T));
    }

private:
    bool strConstraint(string s)
    {
        if (s.length() != 5)
            return false;
        for (int i = 0; i < 4; i++)
        {
            if (s[i] < '1' || s[i] > '9')
                return false;
        }
        if (s[4] != '#')
            return false;

        vector<int> cnt(10, 0);
        for (int i = 0; i < 4; i++)
        {
            cnt[s[i] - '0']++;
        }
        for (int i = 0; i < 10; i++)
        {
            if (cnt[i] > K)
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
        Input({"2",
               "1144#",
               "2233#"});
        Output({"0.4444444444"});
    }

    void BeforeTestCase()
    {
        S = "";
        T = "";
    }

    void TestCases()
    {
        CASE(K = 4, S = "1111#", T = "2222#");
        CASE(K = 5, S = "1111#", T = "2222#");
        CASE(K = 4, S = "1111#", T = "2345#");
        CASE(K = 4, S = "1234#", T = "5554#");
        CASE(K = 1000, S = "1111#", T = "2345#");
        CASE(K = 100000, S = "1234#", T = "5554#");

        for (int i = 0; i < 5; i++)
            CASE(K = 2, smallRandomCard(K, S, T));
        for (int i = 0; i < 5; i++)
            CASE(K = 3, smallRandomCard(K, S, T));
        for (int i = 0; i < 5; i++)
            CASE(K = 4, smallRandomCard(K, S, T));
        for (int i = 0; i < 5; i++)
            CASE(K = 5, smallRandomCard(K, S, T));
        for (int i = 0; i < 5; i++)
            CASE(K = 6, smallRandomCard(K, S, T));
        for (int i = 0; i < 5; i++)
            CASE(K = 7, smallRandomCard(K, S, T));

        for (int i = 0; i < 5; i++)
            CASE(K = 8, S = randomCard(), T = randomCard());
        for (int i = 0; i < 5; i++)
            CASE(K = 50, S = randomCard(), T = randomCard());
        for (int i = 0; i < 5; i++)
            CASE(K = 500, S = randomCard(), T = randomCard());
        for (int i = 0; i < 5; i++)
            CASE(K = 5000, S = randomCard(), T = randomCard());
        for (int i = 0; i < 5; i++)
            CASE(K = 100000, S = randomCard(), T = randomCard());
    }

private:
    string randomCard()
    {
        string s = "aaaa#";
        for (int i = 0; i < 4; i++)
        {
            s[i] = rnd.nextInt(1, 9) + '0';
        }
        return s;
    }

    void smallRandomCard(int K, string &s, string &t)
    {
        s = "aaaa#";
        t = "aaaa#";

        vector<char> vec;
        for (int i = 1; i <= 9; i++)
        {
            for (int j = 0; j < K; j++)
            {
                vec.push_back(i + '0');
            }
        }
        rnd.shuffle(vec.begin(), vec.end());
        for (int i = 0; i < 4; i++)
        {
            s[i] = vec[i];
            t[i] = vec[i + 4];
        }
    }
};