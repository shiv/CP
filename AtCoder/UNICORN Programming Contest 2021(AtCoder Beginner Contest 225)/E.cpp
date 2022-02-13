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

struct Point {
    int x, y;
    Point() {}
    Point(int x, int y) : x(x), y(y) {};
    bool operator<(const Point &other) {
        return x * other.y < other.x * y;
    }
    bool operator<=(const Point &other) {
        return x * other.y <= other.x * y;
    }
};

void solve() {

    int n;
    scan(n);

    vector<Point> a(n), b(n);
    for (int i = 0; i < n; i++) {
        int x, y;
        scan(x, y);
        a[i] = Point(x - 1, y);
        b[i] = Point(x, y - 1);
    }

    // vector<int> idx(n);
    // iota(idx.begin(), idx.end(), 0);
    // sort(idx.begin(), idx.end(), [&] (int i, int j) {
    //     return b[i] < b[j];
    // });

    // int ans = 0;
    // Point curr;
    // for (int i = 0; i < n; i++) {
    //     int j = idx[i];
    //     if (i == 0) {
    //         ans += 1;
    //         curr = b[j];
    //     }
    //     else if (curr <= a[j]) {
    //         ans += 1;
    //         curr = b[j];
    //     }
    // }

    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&] (int i, int j) {
        return a[i] < a[j];
    });

    int ans = 0;
    Point curr;
    for (int i = 0; i < n; i++) {
        int j = idx[i];
        if (i == 0) {
            ans += 1;
            curr = b[j];
        }
        else {
            if (curr <= a[j]) {
                ans += 1;
                curr = b[j];
            }
            else if (b[j] < curr) {
                curr = b[j];
            }
        }
    }

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