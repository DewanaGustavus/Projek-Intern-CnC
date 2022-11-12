#include<bits/stdc++.h>
#define int long long
#define forn(i, n) for(int i = 0; i < (int)n; ++i)

using namespace std;
const int NMAX = 1e5 + 5;
int sz[NMAX];
bool vis[NMAX];
int red[NMAX];
int seg[1 << 18];
int centroidIdx;
vector<vector<int>> queries;
vector<vector<int>> adj;
int ans[NMAX];
const int MOD = 1e9 + 7;

void upd(int idx, int l, int r, int x, int val) {
    if(x < l || r < x) return;
    if(l == r && l == x) {
        seg[idx] = val;
        return;
    }
    int mid = (l + r) >> 1, lc = idx << 1, rc = (idx << 1) + 1;
    upd(lc, l, mid, x, val);
    upd(rc, mid+1, r, x, val);
    seg[idx] = max(seg[lc], seg[rc]);
}

int getmax(int idx, int l, int r, int x, int y) {
    if(x > r || l > y) return LLONG_MIN;
    if(x <= l && r <= y) return seg[idx];
    int mid = (l + r) >> 1, lc = idx << 1, rc = (idx << 1) + 1;
    return max(getmax(lc, l, mid, x, y), getmax(rc, mid+1, r, x, y));
}

void dfssz(int pos, int prev = -1) {
    sz[pos] = 1;
    bool poss = 1;
    for(int &nxt : adj[pos]) {
        if(nxt == prev || vis[nxt]) continue;
        dfssz(nxt, pos);
        sz[pos] += sz[nxt];
    }
}

void dfs(int root, int pos, int prev = -1) {
    if(centroidIdx != -1) return;
    bool poss = 1;
    for(int &nxt : adj[pos]) {
        if(nxt == prev || vis[nxt]) continue;
        dfs(root, nxt, pos);
        if(sz[nxt] * 2 > sz[root]) poss = 0;
    }
    if(sz[pos] * 2 < sz[root]) poss = 0;
    if(poss) {
        //bisa jadi centroid
        centroidIdx = pos;
    }
}

int cariCentroid(int root) {
    centroidIdx = -1;
    dfssz(root);
    dfs(root, root);
    return centroidIdx;
}

void dfsInsert(int pos, int prev = -1, bool del = 0, int depth = 1) {
    if(vis[pos]) return;
    //insert nilai
    if(red[pos] < NMAX) {
        if(del) upd(1, 0, NMAX, red[pos], -MOD);
        else upd(1, 0, NMAX, red[pos], depth);
    }
    for(int &nxt: adj[pos]) {
        if(nxt == prev) continue;
        dfsInsert(nxt, pos, del, depth+1);
    }
}

void dfsProses(int pos, int prev = -1, int depth = 1) {
    if(vis[pos]) return;
    //coba queries
    for(int &q : queries[pos]) {
        //cout << q << ' ' << pos << ' ' << depth << endl;
        ans[q] = max(ans[q], getmax(1, 0, NMAX, 0, q) + depth);
    }

    for(int &nxt: adj[pos]) {
        if(nxt == prev) continue;
        dfsProses(nxt, pos, depth+1);
    }
}

void dfsMain(int pos) {
    int cen = cariCentroid(pos);
    //cout << "  " << cen << '\n';
    // sekarang coba proses nilai-nilai
    // pakai segtree(?)
    // masukkan semua ke segtree -> hapus satu cabang -> proses -> kembalikan
    // -> hapus semua dari segtree
    // complexity : O(n log n) per layer -> O(n log^2 n) total
    
    // masukkan semua ke segtree
    dfsInsert(cen, -1, 0, 0);

    // proses untuk centroid
    for(int &q : queries[cen]) {
        //cout << cen << ' ' << q << ' ' << cen << ' ' << getmax(1, 0, NMAX, 0, q) << '\n';
        ans[q] = max(ans[q], getmax(1, 0, NMAX, 0, q));
    }

    // hapus untuk satu cabang & proses
    for(int &nxt : adj[cen]) {
        // delete
        dfsInsert(nxt, cen, 1);
        // proses
        dfsProses(nxt, cen);
        // return
        dfsInsert(nxt, cen);
    }
    // hapus untuk semua cabang
    dfsInsert(cen, -1, 1);

    vis[cen] = 1;
    for(int &nxt : adj[cen]) {
        //cout << cen << ' ' << nxt << ' ' << vis[nxt] << '\n';
        if(vis[nxt]) continue;
        dfsMain(nxt);
    }
}


int32_t main() {
    int n, m; cin >> n >> m;
    adj.resize(n);
    queries.resize(n);
    forn(i, NMAX) {
        red[i] = LLONG_MIN;
        ans[i] = LLONG_MIN;
        upd(1, 0, NMAX, i, -MOD);
    } 
    memset(vis, 0, sizeof(vis));
    forn(i, n-1) {
        int u, v; cin >> u >> v;
        u--;v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    red[0] = 0; //initially paint first node red
    forn(i, m) {
        int u, v; cin >> u >> v;
        v--;
        if(u == 1) {
            // paint
            red[v] = i + 1;
        }
        else {
            // add query to node
            queries[v].push_back(i+1);
        }
    }

    dfsMain(0);

    int ansTotal = 0;
    forn(i, NMAX) {
        if(ans[i] < -MOD) continue;
        ansTotal += ans[i];
    }

    cout << ansTotal << '\n';
}