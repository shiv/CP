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

int exp(int x, int y, int m = mod) { int res = 1; x = x % m; while (y > 0) { if (y & 1) res = (res * x) % m; y = y >> 1; x = (x * x) % m; } return res; }
int modinv(int x, int m = mod) { return exp(x, m - 2, m); }

void solve() {

    int n;
    scan(n);
    vector<int> a(n);
    scan(a);

    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        scan(x, y);
        g[x - 1].emplace_back(y - 1);
        g[y - 1].emplace_back(x - 1);
    }

    int sum = accumulate(a.begin(), a.end(), (int)0) % mod;

    vector<int> csum(n);
    int ans = 0;

    function<void (int, int)> dfs = [&] (int u, int w) {

        csum[u] = a[u];

        for(int &v: g[u]) {

            if(v == w) {
                continue;
            }

            dfs(v, u);
            ans += (sum - csum[v] - a[u] + mod + mod) % mod * csum[v] % mod * a[u] % mod;
            ans %= mod;
            csum[u] += csum[v];
            csum[u] %= mod;
        }

        ans += (sum - csum[u] + mod) % mod * (csum[u] - a[u] + mod) % mod * a[u] % mod;
        ans %= mod;
    };

    dfs(0, -1);

    ans = ans * modinv(2) % mod;
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