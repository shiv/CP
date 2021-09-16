#include "bits/stdc++.h"
using namespace std;

bool debug;
template <typename T, typename U> istream& operator>>(istream &is, pair<T, U> &p) { return is >> p.first >> p.second;}
template <typename T, typename U> ostream& operator<<(ostream &os, const pair<T, U> &p) { return debug ? os << "(" << p.first << ", " << p.second << ")" : os << p.first << " " << p.second; }
template <typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> istream &operator>>(istream &is, T_container &v) { for (T &x : v) is >> x; return is; }
template <typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream &operator<<(ostream &os, const T_container &v) { bool f = false; if(debug) { os << "{"; for (const T &x : v) { if (f) os << ", "; os << x; f = true; } os << "}"; } else { for (const T &x : v) { if (f) os << " "; os << x; f = true; } } return os; }
void out(bool ok, bool cap = true) { cap ? cout << (ok ? "YES" : "NO") : cout << (ok ? "Yes" : "No"); cout << "\n"; }
void print() { cout << "\n"; } template <typename Head> void print(Head H) { cout << H << "\n"; } template <typename Head, typename... Tail> void print(Head H, Tail... T) { cout << H << " "; print(T...); }
void dbg_out() { cerr << "\n"; } template <typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << " " << H; dbg_out(T...); }
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

void solve() {

    string s;
    cin >> s;
    int k;
    cin >> k;
    vector<string> ops(k);
    cin >> ops;

    map<char, int> mp;

    vector<vector<int>> mpos(26, vector<int>(26, 50));
    for (auto &op : ops) {
        mpos[op[0] - 'A'][op[1] - 'A'] = 1;
    }

    for (char ch = 'A'; ch <= 'Z'; ch++) {
        mpos[ch - 'A'][ch - 'A'] = 0;
    }

    for (int i = 0; i < 26; i++) {
        for (int a = 'A'; a <= 'Z'; a++) {
            for (char b = 'A'; b <= 'Z'; b++) {
                for (char c = 'A'; c <= 'Z'; c++) {
                    amin(mpos[a - 'A'][c - 'A'], mpos[a - 'A'][b - 'A'] + mpos[b - 'A'][c - 'A']);
                }
            }
        }
    }


    int ans = inf;

    for (char to = 'A'; to <= 'Z'; to++) {
        int res = 0;
        bool ok = false;
        for (char &from : s) {
            ok |= mpos[from - 'A'][to - 'A'] == 50;
            res += mpos[from - 'A'][to - 'A'];
        }
        if (!ok) {
            amin(ans, res);
        }
    }

    ans = ans == inf ? -1 : ans;
    print(ans);
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    #ifdef LOCAL
        auto f1 = freopen("A2.in", "r", stdin);
        auto f2 = freopen("A2.ou", "w", stdout);
    #endif
    int t = 1;
    preSolve(t);
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }
    return 0;
}