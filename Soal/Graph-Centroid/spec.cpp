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

    int ans;
    void InputFormat() {
        LINE(N, M);
        LINES(edges);
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
    bool EdgesCons(const vector<vector<int>> &edges) {
        if(edges.size() + 1 != N) return false;
        for(vector<int> &x: edges) {
            if(! (1 <= x[0] && x[0] <= N && 1 <= x[1] && x[1] <= N) ) return false;
            if(x[0] == x[1]) return false;
        }
        // TODO : CHECK IF TREE/NOT
        return true;
    }
    bool QueriesCons(const vector<vector<int>> &queries) {
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
            "5 4",
            "1 2",
            "2 3",
            "2 4",
            "4 5",
            "2 1",
            "2 5",
            "1 2",
            "2 5"
        });
        Output({
            "6"
        });
    }

    void BeforeTestCase() {
        edges.clear();
        queries.clear();
    }

    void TestCases(){
        for(int i = 0; i < 5; i++) CASE(N = 100, M = 200, P = 2, randomTC(N, M, edges, queries));
        for(int i = 0; i < 5; i++) CASE(N = 1e5, M = 1e5, P = 4, randomTC(N, M, edges, queries));
    }

private:
    void randomTC(int N, int M, int P
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
            if(type == 1) {
                queries.emplace_back(1, queryQueue[itrQuery++]);
            }
            else {
                queries.emplace_back(2, rnd.nextInt(1, N));
            }
            
        }
    }

    void randomTree(int N, vector<vector<int>> &edges) {
        for(int i = 2; i <= N; i++) {
            edges.emplace_back(i, rnd.NextInt(1, i-1));
        }
    }
};