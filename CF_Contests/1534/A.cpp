/**
 *    author:  Shivam Gupta
 *    created: 13.06.2021 21:06:28
**/

#include "bits/stdc++.h"
#include <vector>
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
    cin >> t;
}

int dx[] = {0 , 0, 1, -1};
int dy[] = {1, -1, 0, 0};
string ds = "RLDU";

bool possible(int x, int y, int n, int m) {
    return  0 <= x && x < n && 0 <= y && y < m;
}

void solve(int tc = 0) {
    int n, m;
    cin >> n >> m;
    vector<string> g(n);
    cin >> g;

    bool ok = false;
    function<void (int, int)> dfs = [&] (int x, int y) {
        if (g[x][y] == '.')
            return;
        for (int i = 0; i < 4; i++) {
            int a = x + dx[i];
            int b = y + dy[i];
            if (possible(a, b, n, m)) {
                if (g[a][b] == g[x][y]) {
                    ok = true;
                    return;
                }
                if (g[a][b] == '.') {
                    g[a][b] = 'R' + 'W' - g[x][y];
                    dfs(a, b);
                }
            }
        }
    };

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            dfs(i, j);

    if (g[0][0] == '.') {
        g[0][0] = 'R';
        dfs(0, 0);
    }

    if (ok) {
        print("NO");
    }
    else {
        print("YES");
        for (auto& v : g)
            print(v);
    }
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