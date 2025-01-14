/**
 *    author:  Shivam Gupta
 *    created: 01.07.2021 09:25:05
**/

#include "bits/stdc++.h"
using namespace std;

template <typename T, typename U> istream& operator>>(istream &is, pair<T, U> &p) { return is >> p.first >> p.second;} bool debug; template <typename T, typename U> ostream& operator<<(ostream &os, const pair<T, U> &p) { return debug ? os << "(" << p.first << ", " << p.second << ")" : os << p.first << " " << p.second; }
template <typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> istream &operator>>(istream &is, T_container &v) { for (T &x : v) is >> x; return is; } template <typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream &operator<<(ostream &os, const T_container &v) { bool f = false; if(debug) { os << "{"; for (const T &x : v) { if (f) os << ", "; os << x; f = true; } os << "}"; } else { for (const T &x : v) { if (f) os << " "; os << x; f = true; } } return os; }
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
}

class fenwick {
public:
    int n;
    vector<int> tree;
    vector<int> temp;
    // original array should follow 0 based indexing

    fenwick() {}

    fenwick(int _n) : n(_n) {
        tree.resize(n + 1);
        temp.resize(n);
        for(int i = 0; i < n; i++)
            modify(i, 1);
    }

    fenwick(vector<int>& arr) {
        n = arr.size();
        tree.resize(n + 1, 0);
        temp = arr;
        for(int i = 0; i < n; i++) {
            modify(i, temp[i]);
        }
    }

    void modify(int idx, int val) {
        temp[idx] += val;
        idx += 1;
        while(idx <= n) {
            tree[idx] += val;
            idx += idx & (-idx);
        }
    }

    int query(int idx) {
        idx += 1;
        int ret = 0;
        while(idx > 0) {
            ret += tree[idx];
            idx -= idx & (-idx);
        }
        return ret;
    }

    int lower_bound(int v) {
        int sum = 0;
        int pos = 0;
        int _n = n + 1;
        int logn = log2(_n);

        for(int i = logn; i >= 0; i--) {
            if(pos + (1 << i) < _n and sum + tree[pos + (1 << i)] < v) {
                sum += tree[pos + (1 << i)];
                pos += (1 << i);
            }
        }
        return pos;
    }
};


void solve(int tc = 0) {
    int n;
    cin >> n;
    vector<int> x(n);
    cin >> x;

    fenwick fw(n);

    for (int i = 0; i < n; i++) {
        int p;
        cin >> p;

        int index = fw.lower_bound(p);

        cout << x[index] << ' ';
        fw.modify(index, -1);
    }
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t = 1;
    preSolve(t);
    for (int i = 1; i <= t; i++) {
        solve(i);
    }
    return 0;
}