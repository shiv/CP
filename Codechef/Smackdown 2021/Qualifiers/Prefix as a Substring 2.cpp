/**
 *    author:  Shivam Gupta
 *    created: 24.10.2021 18:59:45
**/

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

template <typename T, typename Head, typename... Tail> T amax(T& a, Head b, Tail... c) { if (b > a) a = b; if constexpr (sizeof...(c) != 0) amax(a, c...); return a; }
template <typename T, typename Head, typename... Tail> T amin(T& a, Head b, Tail... c) { if (b < a) a = b; if constexpr (sizeof...(c) != 0) amin(a, c...); return a; }

void solve() {

    int i, j; string a, b, s;
        cin >> a >> b >> s;
        s = '#' + s + '$';

        auto pi = [](const string& s) {
            int n = s.size();
            vector<int> pi(n);
            for(int z = 1; z < n; z++) {
                int p = pi[z - 1];
                while(p and s[z] != s[p]) p = pi[p-1];
                pi[z] = p + (s[z] == s[p]);
            } return pi;
        }(a + s);

        auto z = [](const string& s) {
            int n = s.size();
            vector<int> z(n);
            for(int k = 1, l = 0, r = 0; k < n; ++k) {
                if(k <= r)
                    z[k] = min(r - k + 1, z[k - l]);
                while(k + z[k] < n and s[z[k]] == s[k + z[k]])
                    ++z[k];
                if(k + z[k] - 1 > r)
                    l = k, r = k + z[k] - 1;
            }
            return z;
        }(b + s);

        int n = a.size(), m = b.size();
        vector<int> p(n + 1, -1);
        p[0] = 0;
        for(i = 1; i < s.size(); i++) {
            int pa = pi[n + i - 1], zb = z[m + i];
            amax(p[pa], zb);
        }

        for(i = n; i; i--)
            amax(p[pi[i - 1]], p[i]);

        int64_t ans = 0;
        for(i = 0; i <= n; i++)
            ans += p[i] + 1;

        cout << ans << '\n';

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