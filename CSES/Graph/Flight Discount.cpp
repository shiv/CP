/**
 *    author:  Shivam Gupta
 *    created: 27.05.2021 23:47:34
**/

#include <bits/stdc++.h>
using namespace std;

template <typename A, typename B> string to_string(pair<A, B> p);
string to_string(const char& ch) { return "'" + string(1, ch) + "'"; }
string to_string(const string& s) { return '"' + s + '"'; }
string to_string(const char* s) { return to_string((string) s); }
string to_string(bool b) { return (b ? "true" : "false"); }
string to_string(vector<bool> v) { bool first = true; string res = "{"; for (int i = 0; i < static_cast<int>(v.size()); i++) { if (!first) { res += ", "; } first = false; res += to_string(v[i]); } res += "}"; return res; }
template <typename A> string to_string(A v) { bool first = true; string res = "{"; for (const auto &x : v) { if (!first) { res += ", "; } first = false; res += to_string(x); } res += "}"; return res; }
template <typename A, typename B> string to_string(pair<A, B> p) { return "(" + to_string(p.first) + ", " + to_string(p.second) + ")"; }
#define output cout
void debug_out() { output << endl; }
template <typename Head, typename... Tail> void debug_out(Head H, Tail... T) { output << " " << to_string(H); debug_out(T...); }
#ifndef ONLINE_JUDGE
#define dbg(...) output << "[" << #__VA_ARGS__ << "] :", debug_out(__VA_ARGS__)
#else
#define dbg(...) 42
#endif

#define int             int64_t
#define vii             vector<int>
#define viii            vector<vector<int>>
#define pii             pair<int, int>
#define vpii            vector<pair<int, int>>
#define all(v)          (v).begin(), (v).end()
#define sz(v)           (int)(v).size()
#define pb              push_back
#define in              insert
#define F               first
#define S               second
#define inf             1e18

template <typename T, typename U> istream& operator>>(istream& in, pair<T, U>& a) { in >> a.F >> a.S; return in; }
template <typename T, typename U> ostream& operator<<(ostream& out, pair<T, U>& a) { out << a.F << " " << a.S; return out; }
template <typename T> istream& operator>>(istream& in, vector<T>& a) { for (T& x : a) in >> x; return in; }
template <typename T> ostream& operator<<(ostream& out, vector<T>& a) { bool f = false; for (T& x : a) { if (f) out << " "; out << x; f = true; } return out; }
template <typename T> ostream& operator<<(ostream& out, vector<vector<T>>& a) { bool f = false; for (vector<T>& x : a) { if (f) out << "\n"; out << x; f = true; } return out; }

void out(bool ok, bool cap = true) { if (cap) cout << (ok ? "YES" : "NO") << '\n'; else cout << (ok ? "Yes" : "No") << '\n'; }

void print() { cout << '\n'; }
template <typename Head> void print(Head H) { cout << H; print(); }
template <typename Head, typename... Tail> void print(Head H, Tail... T) { cout << H << " "; print(T...); }

template <typename T, typename U> T amax(T& a, U b) { if (b > a) a = b; return a; }
template <typename T, typename U> T amin(T& a, U b) { if (b < a) a = b; return a; }

const int mod = 1000000007;
const int N = 3e5 + 5;

void preSolve(int &t) {
    // cin >> t;
}

class graph_shortest_path {
public:
    int n, e;
    vector<vector<pii>> g;
    vector<int> djikstra_dist, bf_dist;
    vector<vector<int>> fw_dist;
    int index;

    graph_shortest_path(int _n, int _index = 0) { // index = 1 for 1-based indexing
        index = _index;
        n = _n + index;
        g.resize(n);
        djikstra_dist.assign(n, 1e18);
    }

    graph_shortest_path(int _n, vector<vector<pii>> edge) : graph_shortest_path(_n) {
        g = edge;
    }

    void readGraph(int m) {
        for (int i = 0, u, v, w; i < m; i++) {
            cin >> u >> v >> w;
            u -= 1 - index; v -= 1 - index;
            dadd(u, v, w);
        }
    }

    // undirected edge
    void uadd(int u, int v, int w) {
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    }

    // directed edge
    void dadd(int u, int v, int w) {
        g[u].push_back({v, w});
    }

    void djikstra(vii src) {
        // mnpq<pair<int, int>> pq;
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        for (int ele : src) {
            pq.push({0, ele});
            djikstra_dist[ele] = 0;
        }

        while (!pq.empty()) {
            auto [dist, u] = pq.top();
            pq.pop();
            if (dist > djikstra_dist[u])
                continue;

            for (auto& [v, weight] : g[u]) {
                if (djikstra_dist[v] > djikstra_dist[u] + weight) {
                    djikstra_dist[v] = djikstra_dist[u] + weight;
                    pq.push({djikstra_dist[v], v});
                }
            }
        }
    }

    void flyod_warshall() {
        fw_dist.assign(n, vector<int>(n, 1e18));

        for (int i = index; i < n; i++)
            fw_dist[i][i] = 0;
        for (int i = index; i < n; i++)
            for (auto& [j, w] : g[i])
                fw_dist[i][j] = min(fw_dist[i][j], w);

        for (int k = index; k < n; k++)
            for (int i = index; i < n; i++)
                for (int j = index; j < n; j++)
                    fw_dist[i][j] = min(fw_dist[i][j], fw_dist[i][k] + fw_dist[k][j]);
    }

    bool bellman_ford(int src) {
        bf_dist.assign(n, inf);
        bf_dist[src] = 0;
        for (int i = 0; i < n; i++) {
            for (int u = 0; u < n; u++) {
                for (auto& [v, w] : g[u]) {
                    if (bf_dist[v] > bf_dist[u] + w) {
                        bf_dist[v] = bf_dist[u] + w;
                        if (i == n - 1)
                            return true;    // negative cycle
                    }
                }
            }
        }
        return false;
    }
};

void solve(int tc = 0) {
    int n, m;
    cin >> n >> m;

    graph_shortest_path gr(n);
    gr.readGraph(m);
    

}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t = 1;
    preSolve(t);
    for (int i = 1; i <= t; i++) {
        // cout << "Case #" << i << ": ";
        solve(i);
    }
    return 0;
}
