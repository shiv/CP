/**
 *    author:  Shivam Gupta
 *    created: 13.06.2021 22:37:03
**/

#include "bits/stdc++.h"
using namespace std;

bool debug;
template <typename T, typename U> istream& operator>>(istream &is, const pair<T, U> &p) { return is >> p.first >> p.second;}
template <typename T, typename U> ostream& operator<<(ostream &os, const pair<T, U> &p) { return debug ? os << "(" << p.first << ", " << p.second << ")" : os << p.first << " " << p.second; }
template <typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> istream &operator>>(istream &is, T_container &v) { for (T &x : v) is >> x; return is; }
template <typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream &operator<<(ostream &os, const T_container &v) { bool f = false; if(debug) { os << "{"; for (const T &x : v) { if (f) os << ", "; os << x; f = true; } os << "}"; } else { for (const T &x : v) { if (f) os << " "; os << x; f = true; } } return os; }

void out(bool ok, bool cap = true) { cap ? cout << (ok ? "YES" : "NO") : cout << (ok ? "Yes" : "No"); cout << "\n"; }
void print() { cout << "\n"; }
template <typename Head, typename... Tail> void print(Head H, Tail... T) { cout << H << " "; print(T...); }
void dbg_out() { cerr << "\n"; }
template <typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << " " << H; dbg_out(T...); }
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
}

void solve(int tc = 0) {
    int n;
    cin >> n;

    set<pair<int, int>> edge;
    vector<bool> vis(n, false);
    vector<vector<int>> v(n, vector<int>(n));

    auto query = [&] (int i) {
        cout << "? " << i + 1 << endl;
        cin >> v[i];
    };

    function<void (int, int)> dfs = [&] (int i, int p) {
        if (vis[i])
            return;
        vis[i] = true;
        query(i);
        for (int j = 0; j < n; j++) {
            if (v[i][j] == 1) {
                vis[j] = true;
                edge.emplace(min(i, j), max(i, j));
            }
        }
        for (int j = 0; j < n; j++) {
            if (v[i][j] == 2) {
                dfs(j, i);
                int x;
                vector<int> two_dis;
                for (int k = 0; k < n; k++) {
                    if (v[i][k] * v[j][k] == 1)
                        x = k;
                    if (v[i][k] == 2 && v[j][k] == 2)
                        two_dis.push_back(k);
                }
                for (int& y : two_dis) {
                    vis[y] = true;
                    edge.emplace(min(x, y), max(x, y));
                }
            }
        }
    };

    for (int i = 0; i < n; i++) {
        dfs(i, -1);
    }

    cout << "!" << endl;
    for (auto &[a, b] : edge)
        cout << a + 1 << " " << b + 1 << endl;
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t = 1;
    preSolve(t);
    for (int i = 1; i <= t; i++) {
        solve(i);
    }
    return 0;
}