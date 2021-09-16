#include "bits/stdc++.h"
using namespace std;

bool debug;
template <typename T, typename U> istream& operator>>(istream &is, pair<T, U> &p) { return is >> p.first >> p.second;}
template <typename T, typename U> ostream& operator<<(ostream &os, const pair<T, U> &p) { return debug ? os << "(" << p.first << ", " << p.second << ")" : os << p.first << " " << p.second; }
template <typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> istream &operator>>(istream &is, T_container &v) { for (T &x : v) is >> x; return is; }
template <typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream &operator<<(ostream &os, const T_container &v) { bool f = false; if(debug) { os << "{"; for (const T &x : v) { if (f) os << ", "; os << x; f = true; } os << "}"; } else { for (const T &x : v) { if (f) os << " "; os << x; f = true; } } return os; }
void out(bool ok, bool cap = true) { cap ? cout << (ok ? "YES" : "NO") : cout << (ok ? "Yes" : "No"); cout << "\n"; }
void print() { cout << "\n"; } template <typename Head> void print(Head H) { cout << H << "\n"; } template <typename Head, typename... Tail> void print(Head H, Tail... T) { cout << H << " "; print(T...); }
void dbg_out() { cerr << "\n"; } template <typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << " " << H; dbg_out(T...); }
#ifndef ONLINE_JUDGE
#define dbg(...) cerr << "[" << #__VA_ARGS__ << "]:", debug = true, dbg_out(__VA_ARGS__), debug = false
#else
#define dbg(...)
#endif

template <typename T, typename Head, typename... Tail> T amax(T& a, Head b, Tail... c) { if (b > a) a = b; if constexpr (sizeof...(c) != 0) amax(a, c...); return a; }
template <typename T, typename Head, typename... Tail> T amin(T& a, Head b, Tail... c) { if (b < a) a = b; if constexpr (sizeof...(c) != 0) amin(a, c...); return a; }

#define int int64_t
const int inf = 1e18L + 5, mod = 1e9 + 7, N = 3e5 + 5;

void preSolve(int &t) {
    cin >> t;
}

void solve() {

    int n;
    cin >> n;
    vector<int> c(n);
    cin >> c;
    vector<pair<int, int>> tunnels(n - 1);
    cin >> tunnels;

    vector<vector<int>> g(n);
    for (auto &[u, v] : tunnels) {
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> gold = c;
    gold[0] = 0;

    vector<int> can;

    function<void (int, int, bool)> dfs = [&] (int u, int w, bool yes) {

        int ok = true;

        for (auto &v : g[u]) {

            if (v == w) {
                continue;
            }

            ok = false;

            yes ? gold[v] += gold[u] : 0;

            dfs(v, u, yes);

            yes ? 0 : amax(gold[u], gold[v]);
        }

        if (ok) {
            can.push_back(gold[u]);
        }
    };

    dfs(0, -1, true);
    dfs(0, -1, false);

    sort(g[0].begin(), g[0].end(), [&] (int a, int b) {
        return gold[a] > gold[b];
    });

    int ans = c[0];
    ans += g[0].size() >= 1 ? gold[g[0][0]] : 0;
    ans += g[0].size() >= 2 ? gold[g[0][1]] : 0;

    print(ans);
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    #ifdef LOCAL
        auto f1 = freopen("C1.in", "r", stdin);
        auto f2 = freopen("C1.ou", "w", stdout);
    #endif
    int t = 1;
    preSolve(t);
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }
    return 0;
}