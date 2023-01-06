#include<bits/stdc++.h>
#define int long long

using namespace std;
const int MOD = 1e9 + 7;

int fastexp(int x, int e = MOD - 2) {
    if(!e) return 1;
    int ret = fastexp(x, e >> 1);
    ret = (ret * ret) % MOD;
    if(e&1) ret = (ret * x) % MOD;
    return ret;
}

class Matrix {
    public:
    vector<vector<int>> mat;
    Matrix(int sz): mat(vector<vector<int>>(sz, vector<int>(sz, 0))) {}
    Matrix(int n, int m): mat(vector<vector<int>>(n, vector<int>(m, 0))) {}
};

Matrix mul(Matrix a, Matrix b) {
    int n = a.mat.size();
    int m = b.mat[0].size();
    int p = b.mat.size();
    Matrix ret(n, m);

    for(int k = 0; k < p; k++) {
        for(int i = 0; i < n; i++) {
            int temp = a.mat[i][k];
            for(int j = 0; j < m; j++) {
                ret.mat[i][j] += temp * b.mat[k][j];
            }
        }
    }

    return ret;
}

Matrix ONE(int sz) {
    Matrix ret(sz);
    for(int i = 0; i < sz; i++) ret.mat[i][i] = 1;
    return ret;
}

Matrix fastexpmat(Matrix m, unsigned int e) {
    if(!e) return ONE(m.mat.size());
    Matrix ret = fastexpmat(m, e >> 1);
    ret = mul(ret, ret);
    if(e&1) ret = mul(ret, m);
    return ret;
}

void isiRandom(Matrix &a) {
    for(int i = 0; i < a.mat.size(); i++) {
        for(int j = 0; j < a.mat[i].size(); j++) {
            a.mat[i][j] = rand() % 2117;
        }
    }
}


int32_t main() {
    unsigned int n, m;
    cin >> n >> m;
    Matrix q(m, 1);
    Matrix p(m);
    
    for(int i = 0; i < m; i++) {
        int u; cin >> u;
        p.mat[0][i] = fastexp(u);
    }
    for(int i = 0; i < m; i++) {
        cin >> q.mat[i][0];
    }
    for(int i = 1; i < m; i++) {
        p.mat[i][i-1] = 1;
    }

    Matrix ans = mul(fastexpmat(p, n - m), q);
    cout << ans.mat[0][0] << '\n';
}