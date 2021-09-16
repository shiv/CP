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
const int inf = 1e18L + 5, mod = 1e9 + 7, N = 2e5 + 5;

void solve() {

    int n;
    scan(n);
    string s;
    cin >> s;

    int ans = 0;

    char ch = 'F';
    int idx = 0;
    int curr = 0;
    int tot = 0;
    int changes = 0;
    pair<int, int> track(0, 0);
    char b = 'F';

    for (int i = 0; i < n; i++) {

        if (s[i] == '.') {

            int curr_changes = max<int>(0, changes - (b == ch));

            // ans = ans * 2 % mod;
            ans <<= 1;
            ans += curr * tot;
            ans += idx * (ch != b);
            // ans += (track - (ch != b)) * tot;
            // track.second *= 2;
            // track *= 2;

            curr <<= 1;
            curr += idx * (ch != b);
            curr += max<int>(0, curr_changes - (ch != b)) * tot;
            idx += idx > 0 ? tot : 0;
            changes += curr_changes;
        }
        else {
            if (s[i] == 'X' || s[i] == 'O') {
                if (ch != s[i]) {
                    // track.second += 1;
                    if (ch != 'F') {
                        curr = (curr + idx) % mod;
                    }
                    else {
                        b = s[i];
                    }
                    changes += 1;
                }
                ch = s[i];
                idx = tot + 1;
            }
            // track.first += track.second;
            ans = (ans + curr) % mod;
        }
        tot = s[i] == '.' ? tot << 1 : tot + 1;
        dbg(i, s[i], curr, ans);
    }

    print(ans);
}

signed main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    #ifdef LOCAL
        auto f1 = freopen("A2.in", "r", stdin);
        auto f2 = freopen("A2.ou", "w", stdout);
    #endif

    int t = 1;
    cin >> t;

    for (int tt = 1; tt <= t; tt++) {
        cout << "Case #" << tt << ": ";
        solve();
    }

    return 0;
}