#include "bits/stdc++.h"
#include <algorithm>
using namespace std;

bool debug;
template <typename T, typename U> istream& operator>>(istream &is, pair<T, U> &p) { return is >> p.first >> p.second;}
template <typename T, typename U> ostream& operator<<(ostream &os, const pair<T, U> &p) { return debug ? os << "(" << p.first << ", " << p.second << ")" : os << p.first << " " << p.second; }
template <typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> istream &operator>>(istream &is, T_container &v) { for (T &x : v) is >> x; return is; }
template <typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream &operator<<(ostream &os, const T_container &v) { bool f = false; if(debug) { os << "{"; for (const T &x : v) { if (f) os << ", "; os << x; f = true; } os << "}"; } else { for (const T &x : v) { if (f) os << " "; os << x; f = true; } } return os; }
void scan() {} template <typename Head, typename ...Tail> void scan(Head &H, Tail &...T) { cin >> H; scan(T...); }
void print() { cout << "\n"; } template <typename Head> void print(const Head &H) { cout << H << "\n"; } template <typename Head, typename ...Tail> void print(const Head &H, const Tail &...T) { cout << H << " "; print(T...); }
void dbg_out() { cerr << "\n"; } template <typename Head, typename ...Tail> void dbg_out(const Head &H, const Tail &...T) { cerr << " " << H; dbg_out(T...); }
#ifndef ONLINE_JUDGE
#define dbg(...) cerr << "[" << #__VA_ARGS__ << "]:", debug = true, dbg_out(__VA_ARGS__), debug = false
#else
#define dbg(...)
#endif

#define int int64_t
const int inf = 1e18L + 5, mod = 1e9 + 7, N = 2e5 + 5;

class graph {
public:
    int n, e;
    vector<set<int>> g;
    vector<int> depth, parent;
    vector<bool> visited;
    int index;

    graph(int _n, int _index = 0) { // index = 1 for 1-based indexing
        index = _index;
        n = _n + index;
        g.resize(n);
        visited.assign(n, false);
        parent.assign(n, -1);
        depth.assign(n, -1);
    }

    graph(int _n, vector<set<int>> edge) : graph(_n) {
        g = edge;
    }

    void readGraph(int m) {
        for (int i = 0, u, v; i < m; i++) {
            cin >> u >> v;
            u -= 1 - index; v -= 1 - index;
            uadd(u, v);
        }
        // dbg(g);
    }

    // undirected edge
    void uadd(int u, int v) {
        g[u].emplace(v);
        g[v].emplace(u);
    }

    // directed edge
    void dadd(int u, int v) {
        g[u].emplace(v);
    }

    void bfs(vector<int> src) {             // multi-source bfs
        queue<int> q;
        for (auto ele : src) {
            q.push(ele);
            depth[ele] = 0;
            visited[ele] = true;
        }

        while(!q.empty()) {
            int u = q.front();
            q.pop();

            for(int v: g[u]){
                if (visited[v])
                    continue;
                visited[v] = true;

                depth[v] = depth[u] + 1;
                parent[v] = v;
                q.push(v);
            }
        }
    }

    void dfs(int u, int w = -1) {
        if (w == -1)
            depth[u] = 0;
        visited[u] = true;

        for(int v: g[u]) {
            if(visited[v])
                continue;

            depth[v] = depth[u] + 1;
            parent[v] = u;
            dfs(v, u);
        }
    }
};

void solve() {

    int n, m;
    scan(n, m);
    vector<pair<int, int>> p(m);
    scan(p);

    vector<set<int>> g(n);
    for (auto &[u, v] : p) {
        g[u - 1].emplace(v - 1);
    }

    for (auto &[u, v] : p) {
        g[u - 1].erase(v - 1);
        graph gr(n, g);
        gr.bfs({0});
        print(gr.depth[n - 1]);
        g[u - 1].emplace(v - 1);
    }
}

signed main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t = 1;

    for (int tt = 1; tt <= t; tt++) {
        solve();
    }

    return 0;
}