#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec
{
protected:
    int N, M, a, b;
    int w, Q;
    vector<int> U, V, W;
    vector<int> P;
    vector<int> ans;

    int NMAX = 2000, MMAX = 100000, WMAX = 100000, QMAX = 2000;

    void InputFormat()
    {
        LINE(N, M, a, b);
        LINES(U, V, W) % SIZE(M);
        LINE(Q);
        LINE(P);
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
        CONS(1 <= N && N <= NMAX);
        CONS(1 <= M && M <= MMAX && M <= N * (N - 1) / 2);
        CONS(1 <= Q && Q <= QMAX);

        CONS(U.size() == M);
        CONS(edgeConstraint(U));
        CONS(V.size() == M);
        CONS(edgeConstraint(V));
        CONS(P.size() == Q);
        CONS(edgeConstraint(P));

        CONS(W.size() == M);
        CONS(weightConstraint(W));
    }

private:
    bool edgeConstraint(vector<int> &v)
    {
        for (auto &x : v)
        {
            if (x < 1 || x > N)
                return false;
        }
        return true;
    }
    bool weightConstraint(vector<int> &w)
    {
        for (auto &x : w)
        {
            if (x < 1 || x > WMAX)
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
        Input({"5 6 1 5",
               "1 2 1",
               "2 3 3",
               "2 5 100",
               "3 4 3",
               "3 5 5",
               "4 5 3",
               "4",
               "1 2 3 5"});
        Output({"-1",
                "101",
                "10"});
    }

    void BeforeTestCase()
    {
        U.clear();
        V.clear();
        W.clear();
        P.clear();
    }

    void TestCases()
    {
        /* Kasus uji memiliki start dan endpoint yang relatif dekat (karena metode random kurang tepat)
           Ide 1 : Buat tree dengan edge maksimum T, lalu tambahkan edge sehingga jadi graph dengan weight minimum 2*T + 1.
                   Start dan endpoint pilih dengan mencari diameter tree awal */
        for (int i = 0; i < 10; i++)
        {
            CASE(
                N = 100, M = 99,
                randomGraph(N, M, U, V, W),
                randomStartEnd(N, a, b),
                shortestPath(N, Q, a, b, U, V, W, P));
        }

        for (int i = 0; i < 10; i++)
        {
            CASE(
                N = 100, M = 105,
                randomGraph(N, M, U, V, W),
                randomStartEnd(N, a, b),
                shortestPath(N, Q, a, b, U, V, W, P));
        }

        for (int i = 0; i < 10; i++)
        {
            CASE(
                N = 100, M = 200,
                randomGraph(N, M, U, V, W),
                randomStartEnd(N, a, b),
                shortestPath(N, Q, a, b, U, V, W, P));
        }

        for (int i = 0; i < 10; i++)
        {
            CASE(
                N = 1000, M = 20000,
                randomGraph(N, M, U, V, W),
                randomStartEnd(N, a, b),
                shortestPath(N, Q, a, b, U, V, W, P));
        }

        for (int i = 0; i < 10; i++)
        {
            CASE(
                N = 2000, M = 20000,
                randomGraph(N, M, U, V, W),
                randomStartEnd(N, a, b),
                shortestPath(N, Q, a, b, U, V, W, P));
        }

        for (int i = 0; i < 10; i++)
        {
            CASE(
                N = 2000, M = 100000,
                randomGraph(N, M, U, V, W),
                randomStartEnd(N, a, b),
                shortestPath(N, Q, a, b, U, V, W, P));
        }
    }

private:
    int randomEdgeCount(int N)
    {
        return rnd.nextInt(1, N * (N + 1) / 2);
    }
    void randomStartEnd(int N, int &a, int &b)
    {
        if (N == 1)
        {
            a = b = 1;
        }
        else
        {
            a = rnd.nextInt(1, N);
            b = rnd.nextInt(1, N - 1);
            if (b >= a)
                b++;
        }
    }
    void randomTree(int N, vector<int> &u, vector<int> &v, vector<int> &w)
    {
        vector<int> pruf(N - 2);
        vector<int> cnt(N + 5, 0);
        for (int i = 0; i < N - 2; i++)
        {
            pruf[i] = rnd.nextInt(1, N);
            cnt[pruf[i]]++;
        }

        priority_queue<int, vector<int>, greater<int>> pq;
        for (int i = 1; i <= N; i++)
        {
            if (!cnt[i])
                pq.push(i);
        }

        for (int i = 0; i < N - 2; i++)
        {
            u.push_back(pq.top());
            v.push_back(pruf[i]);
            w.push_back(rnd.nextInt(1, WMAX));
            pq.pop();
            cnt[pruf[i]]--;
            if (!cnt[pruf[i]])
                pq.push(pruf[i]);
        }

        u.push_back(pq.top());
        pq.pop();
        v.push_back(pq.top());
        w.push_back(rnd.nextInt(1, WMAX));
    }
    void randomGraph(int N, int M, vector<int> &u, vector<int> &v, vector<int> &w)
    {
        randomTree(N, u, v, w);
        set<pair<int, int>> edges;

        for (int i = 0; i < u.size(); i++)
        {
            edges.insert({u[i], v[i]});
        }

        for (int i = 0; i < M - N + 1; i++)
        {
            int new_u, new_v;
            while (true)
            {
                randomStartEnd(N, new_u, new_v);
                if (edges.find({new_u, new_v}) == edges.end())
                {
                    edges.insert({new_u, new_v});
                    u.push_back(new_u);
                    v.push_back(new_v);
                    w.push_back(rnd.nextInt(1, WMAX));
                    break;
                }
            }
        }
    }
    void shortestPath(int N, int &Q, int a, int b, vector<int> &u, vector<int> &v, vector<int> &w, vector<int> &p)
    {
        typedef pair<int, pair<int, int>> pair3;

        // Convert representasi graph
        vector<vector<pair<int, int>>> adj(N);
        for (int i = 0; i < u.size(); i++)
        {
            adj[u[i] - 1].emplace_back(v[i] - 1, w[i]);
            adj[v[i] - 1].emplace_back(u[i] - 1, w[i]);
        }

        // Dijkstra, catat previous node untuk backtrack
        priority_queue<pair3, vector<pair3>, greater<pair3>> pq;
        vector<int> prev(N, -1);
        pq.push({0, {a - 1, -2}});

        while (!pq.empty())
        {
            int dist = pq.top().first;
            int pos = pq.top().second.first;
            int pr = pq.top().second.second;
            pq.pop();

            if (prev[pos] != -1)
                continue;
            prev[pos] = pr;

            if (pos == b - 1)
                break;

            for (pair<int, int> nxt : adj[pos])
            {
                if (prev[nxt.first] != -1)
                    continue;
                pq.push({nxt.second + dist, {nxt.first, pos}});
            }
        }

        int posNow = b - 1;
        p.push_back(posNow + 1);
        while (posNow != a - 1)
        {
            posNow = prev[posNow];
            p.push_back(posNow + 1);
        }
        reverse(p.begin(), p.end());

        Q = p.size();
    }
};