#include "bits/stdc++.h"
using namespace std;

bool debug;
template <typename T, typename U> istream& operator>>(istream &is, pair<T, U> &p) { return is >> p.first >> p.second; }
template <typename T, typename U> ostream& operator<<(ostream &os, const pair<T, U> &p) { return debug ? os << "(" << p.first << ", " << p.second << ")" : os << p.first << " " << p.second; }
template <typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> istream &operator>>(istream &is, T_container &v) { for (T &x : v) is >> x; return is; }
template <typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream &operator<<(ostream &os, const T_container &v) { bool f = false; if(debug) { os << "["; for (const T &x : v) { if (f) os << ", "; os << x; f = true; } os << "]"; } else { for (const T &x : v) { if (f) os << " "; os << x; f = true; } } return os; }
void scan() {} template <typename Head, typename ...Tail> void scan(Head &H, Tail &...T) { cin >> H; scan(T...); }
void print() { cout << "\n"; } template <typename Head> void print(const Head &H) { cout << H << "\n"; } template <typename Head, typename ...Tail> void print(const Head &H, const Tail &...T) { cout << H << " "; print(T...); }
template <typename Head> void dbg_out(string var, const Head &H) { cerr << var << " = " << H << endl; } template <typename Head, typename ...Tail> void dbg_out(string var, const Head &H, const Tail &...T) { for (int i = 0, b = 0; i < (int)var.size(); i++) { if (var[i] == '(' || var[i] == '{') b++; else if (var[i] == ')' || var[i] == '}') b--; else if (var[i] == ',' && b == 0) { cerr << var.substr(0, i) << " = " << H << " | "; dbg_out(var.substr(var.find_first_not_of(' ', i + 1)), T...); break; } } }
#ifndef ONLINE_JUDGE
#define dbg(...) debug = true, dbg_out(#__VA_ARGS__, __VA_ARGS__), debug = false
#else
#define dbg(...)
#endif

template <typename T, typename Head, typename... Tail> T amax(T& a, Head b, Tail... c) { if (b > a) a = b; if constexpr (sizeof...(c) != 0) amax(a, c...); return a; }
template <typename T, typename Head, typename... Tail> T amin(T& a, Head b, Tail... c) { if (b < a) a = b; if constexpr (sizeof...(c) != 0) amin(a, c...); return a; }

#define int int64_t
const int inf = 1e18L + 5, mod = 1e9 + 7, N = 2e5 + 5;

void solve() {

    int n;
    scan(n);
    vector<vector<int>> a(2, vector<int>(n));
    scan(a);

    auto b = a;
    auto c = a, d = a;

    {
        int i = 0;
        for (int j = 1; j < n; j++) {
            c[i][j] = max(c[i][j] + 1, c[i][j - 1] + 1);
        }
        c[1][n - 1] = max(c[1][n - 1] + 1, c[0][n - 1] + 1);
        i = 1;
        for (int j = n - 2; j >= 0; j--) {
            c[i][j] = max(c[i][j] + 1, c[i][j + 1] + 1);
        }
    }
    {
        d[1][0] = max(d[1][0] + 1, d[0][0] + 1);
        int i = 1;
        for (int j = 1; j < n; j++) {
            d[i][j] = max(d[i][j] + 1, d[i][j - 1] + 1);
        }
        d[0][n - 1] = max(d[0][n - 1] + 1, d[1][n - 1] + 1);
        i = 0;
        for (int j = n - 2; j >= 1; j--) {
            d[i][j] = max(d[i][j] + 1, d[i][j + 1] + 1);
        }
    }

    int ans = inf;
    int curr = 0;
    int i_, j_;
    for (int i = 0, j = 0, curr = 1; curr <= 2 * n; curr++) {
        if (i || j) {
            b[i][j] = max(a[i][j] + 1, b[i_][j_] + 1);
            if (curr == 2 * n) {
                amin(ans, b[i][j]);
            }
        }
        if (curr & 1) {
            if (i == 0) {
                amin(ans, max(b[i][j] + 2 * n - curr, c[1][j]));
                // dbg(i, j, ans);
            }
            if (i == 1) {
                amin(ans, max(b[i][j] + 2 * n - curr, d[0][j]));
                // dbg(i, j, ans);
            }
        }
        i_ = i;
        j_ = j;
        i ^= curr & 1;
        j += curr & 1 ^ 1;
    }
    // dbg(b);
    // dbg(c);
    // dbg(d);
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