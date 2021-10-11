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

template <typename T, typename Head, typename... Tail> T amax(T& a, Head b, Tail... c) { if (b > a) a = b; if constexpr (sizeof...(c) != 0) amax(a, c...); return a; }
template <typename T, typename Head, typename... Tail> T amin(T& a, Head b, Tail... c) { if (b < a) a = b; if constexpr (sizeof...(c) != 0) amin(a, c...); return a; }

vector<int> lis(vector<int> arr) {

    int n = arr.size();
    vector<int> lis(n);

    lis[0] = 1;

    for (int i = 1; i < n; i++) {
        lis[i] = 1;
        for (int j = 0; j < i; j++) {
            if (arr[i] >= arr[j] && lis[i] < lis[j] + 1) {
                lis[i] = lis[j] + 1;
            }
        }
    }

    return lis;
}
vector<int> lds(vector<int> arr) {

    int n = arr.size();
    vector<int> lis(n);

    lis[0] = 1;

    for (int i = 1; i < n; i++) {
        lis[i] = 1;
        for (int j = 0; j < i; j++) {
            if (arr[i] <= arr[j] && lis[i] < lis[j] + 1) {
                lis[i] = lis[j] + 1;
            }
        }
    }

    return lis;
}

void solve() {

    int n;
    scan(n);
    vector<int> a(n);
    scan(a);

    vector<int> lis1 = lis(a);
    vector<int> lds1 = lds(a);
    reverse(a.begin(), a.end());
    vector<int> lis2 = lis(a);
    reverse(lis2.begin(), lis2.end());
    vector<int> lds2 = lds(a);
    reverse(lds2.begin(), lds2.end());
    reverse(a.begin(), a.end());

    int lis = 0;
    for (int i = 0; i < n; i++) {
        amax(lis, lis1[i]);
    }
    int lds = 0;
    for (int i = 0; i < n; i++) {
        amax(lds, lds1[i]);
    }

    for (int i = 0; i < n; i++) {
        if (lis1[i] + lds2[i] - 1 == lis && lds1[i] + lis2[i] - 1 == lds) {
            print(1);
            return;
        }
    }

    print(0);
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