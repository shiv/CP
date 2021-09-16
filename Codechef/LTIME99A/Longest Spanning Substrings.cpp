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

const int INF = 1000000000; // weight INF means there is no edge

struct Edge {
    int w = INF, to = -1;
};

int LCSuff[5000 + 1][5000 + 1];
void solve() {

    int n;
    cin >> n;
    vector<string> st(n);
    cin >> st;

    vector<vector<int>> adj(n, vector<int>(n));

    auto lcs = [&] (string &X, string &Y) {
        int m = X.size(), n = Y.size();

        int result = 0;
        for (int i = 0; i <= m; i++)
        {
            for (int j = 0; j <= n; j++)
            {
                if (i == 0 || j == 0)
                    LCSuff[i][j] = 0;

                else if (X[i - 1] == Y[j - 1]) {
                    LCSuff[i][j] = LCSuff[i - 1][j - 1] + 1;
                    result = max(result, LCSuff[i][j]);
                }
                else
                    LCSuff[i][j] = 0;
            }
        }
        return result;
    };

    auto prim = [&] () {
        int total_weight = 0;
        vector<bool> selected(n, false);
        vector<Edge> min_e(n);
        min_e[0].w = 0;

        for (int i=0; i<n; ++i) {
            int v = -1;
            for (int j = 0; j < n; ++j) {
                if (!selected[j] && (v == -1 || min_e[j].w < min_e[v].w))
                    v = j;
            }

            selected[v] = true;
            total_weight += min_e[v].w;
            // if (min_e[v].to != -1)
            //     cout << v << " " << min_e[v].to << endl;

            for (int to = 0; to < n; ++to) {
                if (adj[v][to] < min_e[to].w)
                    min_e[to] = {adj[v][to], v};
            }
        }

        return total_weight;
    };

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            adj[i][j] = -lcs(st[i], st[j]);
        }
    }

    int ans = -prim();

    print(ans);
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t = 1;
    preSolve(t);
    for (int i = 1; i <= t; i++) {
        solve();
    }
    return 0;
}