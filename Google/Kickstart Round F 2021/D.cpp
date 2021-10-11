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
    int n, m, k;
    scan(n, m, k);
    vector<int> L(n), R(n), a(n);
    for(int i = 0; i < n; i++) {
        scan(L[i], R[i], a[i]);
    }
    vector<vector<int>> g(n);
    for(int i = 0; i < m; i++) {
        int u, v;
        scan(u, v);
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    int ans = 0;
    vector<vector<pair<int, int>>> dp(n, vector<pair<int, int>>(1 << n, pair(0, 0)));
    for(int i = 0; i < n; i++) {
        dp[i][1 << i] = {a[i], 1};
    }
    for(int mask = 0; mask < 1 << n; mask++) {
        vector<int> pre, abse;
        for(int i = 0; i < n; i++) {
            if(mask >> i & 1) {
                pre.emplace_back(i);
                auto [magic, ways] = dp[i][mask];
                if(magic == k)
                    ans += ways;
            }
            else {
                abse.emplace_back(i);
            }
        }
        
        for(auto& i : pre) {
            auto& [magic, ways] = dp[i][mask];
            queue<int> q;
            q.emplace(i);
            vector<int> taken(n);
            taken[i] = 1;
            vector<int> vec;
            // dbg(i, mask);
            while(!q.empty()) {
                int x = q.front();
                // dbg(x);
                q.pop();
                for(auto& y : g[x]) {
                    // dbg(y);
                    if(taken[y]) continue;
                    taken[y] = 1;
                    if(mask >> y & 1) {
                        q.emplace(y);
                    }
                    else if(L[y] <= magic && magic <= R[y]) {
                        vec.emplace_back(y);
                    }
                }
            }
            // dbg(i, mask, vec);
            for(auto& j : vec) {
                // dbg(i, mask, "->", j, mask | (1 << j), dp[j][mask | 1 << j].second + ways);
                if(magic + a[j] > k) continue;
                dp[j][mask | 1 << j].first = magic + a[j];
                dp[j][mask | 1 << j].second += ways;
            }
        }
    }
    cout << ans << '\n';
}

signed main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
    cin >> t;

    for (int tt = 1; tt <= t; tt++) {
        cout << "Case #" << tt << ": ";
        solve();
    }

    return 0;
}