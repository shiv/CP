#include "bits/stdc++.h"
#include <algorithm>
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
const int inf = 1e18L + 5, mod = 998244353, N = 2e5 + 5;

int exp(int x, int y, int m = mod) { int res = 1; x = x % m; while (y > 0) { if (y & 1) res = (res * x) % m; y = y >> 1; x = (x * x) % m; } return res; }
int modinv(int x, int m = mod) { return exp(x, m - 2, m); }

vector<int> fact(N);

int nPr(int n, int r) {
    if (n < r) {
        return 0;
    }
    return fact[n] * modinv(fact[n - r]) % mod;
}

void solve() {

    int n;
    scan(n);
    vector<int> a(n);
    scan(a);

    vector<int> b = a;
    sort(b.begin(), b.end());

    if (b[n - 1] == b[n - 2]) {
        print(fact[n]);
        return;
    }

    int mx = b[n - 1];
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        cnt += b[i] == mx - 1;
    }

    if (cnt == 0) {
        print(0);
        return;
    }

    int num = n - 1 - cnt;
    int ans = fact[n];
    for (int i = 0; i <= n - 1 - cnt; i++) {
        ans -= fact[n - 1 - i] * nPr(num, i) % mod;
        ans += ans < 0 ? mod : 0;
    }

    print(ans);
}

signed main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
    cin >> t;

    fact[0] = 1;
    for (int i = 1; i < N; i++) {
        fact[i] = fact[i - 1] * i % mod;
    }

    for (int tt = 1; tt <= t; tt++) {
        solve();
    }

    return 0;
}