#include <tcframe/spec.hpp>
#include <bits/stdc++.h>
using namespace tcframe;
using namespace std;

class ProblemSpec : public BaseProblemSpec {
protected:

    int N, M;
    const int NMAX = 1e5;
    vector<vector<int>> edges;
    vector<vector<int>> queries;

    long long ans;
    void InputFormat() {
        LINE(N, M);
        LINES(edges) % SIZE(N-1);
        LINES(queries);
    }

    void OutputFormat() {
        LINE(ans);
    }

    void GradingConfig() {
        TimeLimit(5);
        MemoryLimit(256);
    }

    void Constraints() {
        CONS(1 < N && N <= NMAX);
        CONS(1 <= M && M <= NMAX);
        CONS(EdgesCons(edges));
        CONS(QueriesCons(queries));
    }
private:
    vector<bool> vis;
    int cnt;
    bool poss;
    vector<vector<int>> adj;
    void dfs(int pos, int prev) {
        if(vis[pos]) return;
        vis[pos] = 1;
        cnt++;
        for(int &nxt: adj[pos]) {
            if(nxt == prev) continue;
            if(vis[nxt]) poss = 0;
            dfs(nxt, pos);
        }
    }
    bool EdgesCons(vector<vector<int>> &edges) {
        if(edges.size() + 1 != N) return false;
        cnt = 0;
        poss = 1;
        vis = vector<bool>(N+1, false);
        adj = vector<vector<int>>(N+1, vector<int>(0));
        for(vector<int> &x: edges) {
            if(! (1 <= x[0] && x[0] <= N && 1 <= x[1] && x[1] <= N) ) return false;
            if(x[0] == x[1]) return false;
            adj[x[0]].push_back(x[1]);
            adj[x[1]].push_back(x[0]);
        }
        dfs(1, -1);
        if(cnt < N) poss = 0;
        return poss;
    }
    bool QueriesCons(vector<vector<int>> &queries) {
        if(queries.size() != M) return false;
        vector<bool> done(N+1, false);
        done[1] = true;
        for(vector<int> &x: queries) {
            if(x[0] < 1 || x[0] > 2) return false;
            if(x[1] < 1 || x[1] > N) return false;
            if(x[0] == 1) {
                if(done[x[1]]) return false;
                done[x[1]] = true;
            }
        }
        return true;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "3 5",
            "1 2",
            "1 3",
            "2 1",
            "2 2",
            "2 3",
            "1 2",
            "2 3"
        });
        Output({
            "4"
        });
    }

    void BeforeTestCase() {
        edges.clear();
        queries.clear();
    }

    void TestCases(){
        for(int i = 0; i < 5; i++) CASE(N = 100, M = 200, randomTC(N, M, 2, edges, queries));
        for(int i = 0; i < 5; i++) CASE(N = 1000, M = 2000, randomTC(N, M, 100, edges, queries));
        for(int i = 0; i < 5; i++) CASE(N = 1000, M = 2000, randomTC(N, M, 3, edges, queries));
        for(int i = 0; i < 5; i++) CASE(N = 1e5, M = 1e5, randomTC(N, M, 4, edges, queries));
    }

private:
    void randomTC(int N, int M, int P,
                  vector<vector<int>> &edges, 
                  vector<vector<int>> &queries) 
    {
        randomTree(N, edges);
        vector<int> queryQueue(N-1);
        for(int i = 0; i < queryQueue.size(); i++) {
            queryQueue[i] = i + 2;
        }
        rnd.shuffle(queryQueue.begin(), queryQueue.end());

        int itrQuery = 0;
        for(int i = 0; i < M; i++) {
            int type = rnd.nextInt(1, P);
            if(type == 1 && itrQuery < N-1) {
                vector<int> pb = {1, queryQueue[itrQuery++]};
                queries.emplace_back(pb);
            }
            else {
                vector<int> pb = {2, rnd.nextInt(1, N)};
                queries.emplace_back(pb);
            }
            
        }
    }

    void randomTree(int N, vector<vector<int>> &edges) {
        for(int i = 2; i <= N; i++) {
            vector<int> pb = {i, rnd.nextInt(1, i-1)};
            edges.emplace_back(pb);
        }
    }
};