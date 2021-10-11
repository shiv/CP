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

#define int int64_t
const int inf = 1e18L + 5, mod = 1e9 + 7, N = 2e5 + 5;

void solve() {

    int n;
    scan(n);
    vector<pair<int, int>> edges(n - 1);
    cin >> edges;
    vector<int> f(n);
    scan(f);

    vector<vector<int>> g(n);
    for(auto& [u, v] : edges) {
        g[u - 1].emplace_back(v - 1);
        g[v - 1].emplace_back(u - 1);
    }

    vector<int> freq(n);
    for (int &i : f) {
        i -= 1;
        freq[i] += 1;
    }

    vector<map<int, int>> upd(n);
    int ans = 0;

    function<void (int, int)> dfs = [&](int u, int oz) {

        upd[u][f[u]]++;

        for(auto &v : g[u]) {

            if (v == oz) {
                continue;
            }

            dfs(v, u);

            if (upd[u].size() < upd[v].size()) {
                swap(upd[u], upd[v]);
            }

            for (auto& [x, y] : upd[v]) {
                upd[u][x] += y;
            }
        }

        if (oz == -1) {
            return;
        }

        for (auto &p : upd[u]) {
            if (freq[p.first] != p.second) {
                return;
            }
        }

        ans++;
        upd[u].clear();
    };

    dfs(0, -1);

    print(ans);
}

signed main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    #ifdef LOCAL
        auto f1 = freopen("B.txt", "r", stdin);
        auto f2 = freopen("B.ou", "w", stdout);
    #endif
    int t = 1;
    cin >> t;

    for (int tt = 1; tt <= t; tt++) {
        cout << "Case #" << tt << ": ";
        solve();
    }

    return 0;
}