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

template <typename T, typename Head, typename... Tail> T amax(T& a, Head b, Tail... c) { if (b > a) a = b; if constexpr (sizeof...(c) != 0) amax(a, c...); return a; }
template <typename T, typename Head, typename... Tail> T amin(T& a, Head b, Tail... c) { if (b < a) a = b; if constexpr (sizeof...(c) != 0) amin(a, c...); return a; }

#define int int64_t
const int inf = 1e18L + 5, mod = 1e9 + 7, N = 2e5 + 5;

void solve() {

    int n;
    scan(n);

    map<pair<int, int>, int> m;

    auto ask = [&] (int l, int r) {
        pair<int, int> p(l, r);
        if (l == r) {
            m[p] = 0;
        }
        if (m.find(p) == m.end()) {
            cout << "? " << l << ' ' << r << endl;
            cin >> m[p];
        }
        if (m[p] == -1) {
            exit(0);
        }
        return m[p];
    };

    auto good = [&] (int x) {
        int s = sqrt(x * 2);
        for (int sx = max<int>(0, s - 5); sx <= s + 5; sx++) {
            if ((sx + 1) * (sx + 1) > x * 2) {
                return sx * (sx + 1) == x * 2;
            }
        }
        assert(false);
    };

    int i, j, k;

    {
        j = -1;
        int l = 1, r = n;

        while (l <= r) {

            int mid = (l + r) / 2;
            int x = ask(1, mid);

            if (good(x)) {
                l = mid + 1;
                amax(j, mid);
            }
            else {
                r = mid - 1;
            }
        }
    }

    {
        i = j - sqrt(ask(1, j) * 2);
    }

    {
        k = j + sqrt(ask(j, n) * 2);
    }

    cout << "! " << i << ' ' << j << ' ' << k << endl;
}

signed main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
    scan(t);

    for (int tt = 1; tt <= t; tt++) {
        solve();
    }

    return 0;
}