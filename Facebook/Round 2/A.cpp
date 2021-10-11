#include "bits/stdc++.h"
#include <algorithm>
#include <type_traits>
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
    vector<vector<int>> v(n + 1, vector<int>(m));
    scan(v);

    map<int, pair<int, int>> mp;
    for(int i = 0; i < m; i++) {
        mp[v[0][i]].first++;
    }
    int used = m;

    int ans = 0;

    for (int i = 1; i <= n; i++) {

        map<int, pair<int, int>> mb;
        int not_used = used;
        vector<int> extra;

        for (int x : v[i]) {
            if(mp[x].second > 0) {
                mp[x].second--;
                mb[x].second++;
            }
            else if(mp[x].first > 0) {
                mp[x].first--;
                mb[x].first++;
                not_used--;
            }
            else {
                extra.push_back(x);
            }
        }

        int used_for_free = min<int>(extra.size(), not_used);
        used -= min<int>(extra.size(), not_used);
        ans += extra.size() - min<int>(extra.size(), not_used);

        for(auto& x : extra) {
            mb[x].second++;
        }

        mp = mb;
    }

    print(ans);
}

signed main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    #ifdef LOCAL
        auto f1 = freopen("A.in.txt", "r", stdin);
        auto f2 = freopen("A.ou", "w", stdout);
    #endif

    int t = 1;
    cin >> t;

    for (int tt = 1; tt <= t; tt++) {
        cout << "Case #" << tt << ": ";
        solve();
    }

    return 0;
}