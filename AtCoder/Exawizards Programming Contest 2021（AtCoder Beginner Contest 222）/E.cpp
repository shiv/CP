#include "bits/stdc++.h"
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

template <typename T, typename Head, typename... Tail> T amax(T& a, Head b, Tail... c) { if (b > a) a = b; if constexpr (sizeof...(c) != 0) amax(a, c...); return a; }
template <typename T, typename Head, typename... Tail> T amin(T& a, Head b, Tail... c) { if (b < a) a = b; if constexpr (sizeof...(c) != 0) amin(a, c...); return a; }

#define int int64_t
const int inf = 1e18L + 5, mod = 998244353, N = 2e5 + 5;

void solve() {

    int n, m, k;
    scan(n, m, k);
    vector<int> a(m);
    scan(a);
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scan(u, v);
        g[u - 1].emplace_back(v - 1);
        g[v - 1].emplace_back(u - 1);
    }

    int lvl = 19;
    vector<int> depth(n);
    vector<vector<int>> p(lvl, vector<int>(n, -1));
    map<pair<int, int>, int> cnt;
    int sum = 0;

    function<void (int, int)> dfs = [&] (int u, int par) {
        p[0][u] = par;
        depth[u] = par == -1 ? 0 : depth[par] + 1;
        for (int &v : g[u]) {
            if (v != par) {
                cnt[{v, u}] = 0;
                dfs(v, u);
            }
        }
    };

    dfs(0, -1);

    for (int i = 1; i < lvl; i++) {
        for (int node = 0; node < n; node++) {
            if (p[i - 1][node] != -1) {
                p[i][node] = p[i - 1][p[i - 1][node]];
            }
        }
    }

    auto getp = [&] (int node, int dis) {
        for (int i = lvl - 1; i >= 0; i--) {
            if (dis >> i & 1) {
                node = p[i][node];
            }
        }
        return node;
    };

    auto find_lca = [&] (int u, int v) -> int {
        if (depth[u] > depth[v]) {
            swap(u, v);
        }
        v = getp(v, depth[v] - depth[u]);
        if(u == v) {
            return u;
        }
        for (int i = lvl - 1; i >= 0; i--) {
            if (p[i][u] != p[i][v]) {
                u = p[i][u];
                v = p[i][v];
            }
        }
        return p[0][u];
    };

    for (int i = 1; i < m; i++) {
        int x = a[i - 1] - 1;
        int y = a[i] - 1;
        int z = find_lca(x, y);
        while (x != z) {
            cnt[{x, p[0][x]}] += 1;
            x = p[0][x];
            sum += 1;
        }
        while (y != z) {
            cnt[{y, p[0][y]}] += 1;
            y = p[0][y];
            sum += 1;
        }
    }

    int target = sum - abs(k);
    if (target < 0 || (target & 1)) {
        print(0);
        return;
    }
    target >>= 1;

    vector<int> dp(target + 1);
    dp[0] = 1;

    for (auto &[edge, wt] : cnt) {
        for (int i = target; i - wt >= 0; i--) {
            dp[i] += dp[i - wt];
            dp[i] -= dp[i] >= mod ? mod : 0;
        }
    }

    print(dp[target]);
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