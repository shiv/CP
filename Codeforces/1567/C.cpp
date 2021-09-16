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

    int n;
    cin >> n;

    int ans = 0;

    if (n < 10) {
        ans = n - 1;
    }
    else if (n == 10) {
        ans = 0;
    }
    else {
        vector<int> v;
        while (n > 0) {
            v.push_back(n % 10);
            n /= 10;
        }
        reverse(v.begin(), v.end());

        function<int (vector<int> &, int, vector<bool> )> calc = [&] (vector<int> vec, int idx, vector<bool> ok) {

            if (idx == vec.size()) {
                return (int)1;
            }

            int a1 = 0, a2 = 0;

            if (ok[idx]) {
                a1 = (vec[idx] + 1) * calc(vec, idx + 1, ok);
            }
            else {
                a1 = (9 - vec[idx]) * calc(vec, idx + 1, ok);
            }

            if (idx + 2 < vec.size()) {
                ok[idx + 2] = false;
                if (ok[idx]) {
                    a2 = (vec[idx]) * calc(vec, idx + 1, ok);
                }
                else {
                    a2 = (10 - vec[idx]) * calc(vec, idx + 1, ok);
                }
            }
            return a1 + a2;
        };

        ans = calc(v, 0, vector<bool>(v.size(), true)) - 2;
    }

    print(ans);
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t = 1;
    preSolve(t);
    for (int i = 1; i <= t; i++) {
        solve();
    }
    return 0;
}