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

    int n, m;
    scan(n, m);
    vector<vector<char>> mat(n, vector<char>(m));
    scan(mat);

    vector<vector<int>> d(n + 1, vector<int>(m + 1));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            d[i][j] = d[i][j - 1] + d[i - 1][j] - d[i - 1][j - 1] + mat[i - 1][j - 1] - '0';
        }
    }

    auto dquery = [&] (int r1, int c1, int r2, int c2) {
        return d[r2][c2] - d[r2][c1 - 1] - d[r1 - 1][c2] + d[r1 - 1][c1 - 1];
    };

    auto iquery = [&] (int r1, int c1, int r2, int c2) {
        return (r2 - r1 + 1) * (c2 - c1 + 1) - dquery(r1, c1, r2, c2);
    };

    int ans = inf;

    for (int r1 = 1; r1 <= n; r1++) {
        for (int c1 = 1; c1 <= m; c1++) {
            for (int r2 = r1 + 4; r2 <= n; r2++) {
                for (int c2 = c1 + 3; c2 <= m; c2++) {

                    int res = dquery(r1 + 1, c1 + 1, r2 - 1, c2 - 1);
                    if (res >= ans) {
                        break;
                    }

                    res += iquery(r1, c1 + 1, r1, c2 - 1);
                    res += iquery(r2, c1 + 1, r2, c2 - 1);
                    res += iquery(r1 + 1, c1, r2 - 1, c1);
                    if (res >= ans) {
                        break;
                    }

                    res += iquery(r1 + 1, c2, r2 - 1, c2);

                    ans = min(ans, res);
                }
            }
        }
    }

    print(ans);
}

signed main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
    cin >> t;

    for (int tt = 1; tt <= t; tt++) {
        solve();
    }

    return 0;
}