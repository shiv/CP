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

#define int int64_t
const int inf = 1e18L + 5, mod = 1e9 + 7, N = 2e5 + 5, p = 31;

vector<bool> check(string s, string t) {
    int n = s.size();
    vector<bool> g(n + 1);
    vector<int> h(n + 1);
    {
        int val = 0;
        int p_pow = 1;
        for (int i = 0; i < n; i++) {
            val += p_pow * (t[i] - 'a' + 1);
            val %= mod;
            h[i + 1] = val;
            p_pow *= p;
            p_pow %= mod;
        }
    }
    {
        int val = 0;
        for (int i = n - 1; i >= 0; i--) {
            int len = n - i;
            val *= p;
            val %= mod;
            val += s[i] - 'a' + 1;
            val %= mod;
            g[len] = h[len] == val ? true : g[len];
        }
    }
    g[0] = true;
    return g;
}

void solve() {

    int n;
    scan(n);
    string s;
    scan(s);

    string t(s.rbegin(), s.rend());

    vector<int> v;

    if(s != t) {
        v.push_back(2 * n);
    }
    else {
        auto a = check(s, t);
        auto b = check(t, s);

        for (int i = 0; i <= 2 * n; i++) {
            if (!a[2 * n - i] && !b[i]) {
                if (i == 0 || i == 2 * n) {
                    v.push_back(2 * n);
                }
                else {
                    v.emplace_back(i);
                    v.emplace_back(2 * n - i);
                }
                break;
            }
        }
    }

    if (v.empty()) {
        print(-1);
    }
    else {
        print(v.size());
        print(v);
    }
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