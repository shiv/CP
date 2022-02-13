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

    int n;
    scan(n);
    string s;
    scan(s);

    auto modit = [&] (int &x) {
        x += x < 0 ? mod : 0;
        x -= x >= mod ? mod : 0;
    };

    vector<vector<vector<int>>> dp(1024, vector<vector<int>>(1024, vector<int>(10, 0)));

    for (int i = 1; i <= n; i++) {
        int x = s[i - 1] - 'A';
        for (int j = 0; j < 1024; j++) {
            for (int k = 0; k < 10; k++) {
                dp[i][j][k] = dp[i - 1][j][k];
                if (k == x) {
                    dp[i][j][k] += dp[i - 1][j][k];
                    modit(dp[i][j][k]);
                }
            }
        }
        for (int j = 0; j < 1024; j++) {
            if ((1 << x) & j) {
                continue;
            }
            for (int k = 0; k < 10; k++) {
                dp[i][j|(1<<x)][x] += dp[i - 1][j][k];
                modit(dp[i][j|(1<<x)][x]);
            }
        }
        dp[i][1<<x][x] += 1;
        modit(dp[i][1<<x][x]);
    }

    int ans = 0;
    for (int j = 0; j < 1024; j++) {
        for (int k = 0; k < 10; k++) {
            ans += dp[n][j][k];
            modit(ans);
        }
    }

    print(ans);
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