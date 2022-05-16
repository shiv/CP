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


class dsu {
public:
    vector<int> p, sz;
    int cc;
    int n;
    vector<bool> vis;
    dsu(int _n) : n(_n) {
        cc = n;
        vis.assign(n, false);
        p.resize(n);
        iota(p.begin(), p.end(), 0);
        sz.resize(n, 1);
    }
    inline int get(int x) {
        return (x == p[x] ? x : (p[x] = get(p[x])));
    }
    inline bool unite(int x, int y) {
        if (!vis[x] || !vis[y]) {
            return false;
        }
        x = get(x), y = get(y);
        if (x == y)
            return false;
        if (sz[x] < sz[y])
            swap(x, y);
        p[y] = x;
        sz[x] += sz[y];
        sz[y] = 0;
        cc--;
        return true;
    }


    void unite(const vector<int> &U, const vector<int> &V) {
        int m = U.size();
        assert(int(V.size()) == m);
        for (int i = 0; i < m; i++)
            unite(U[i], V[i]);
    }

};

int solve(int n, int k, vector<int> arr) {

    vector<int> idx(n);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&] (int a, int b) {
        return arr[a] < arr[b];
    });

    dsu d(n);
    for (int i = 0; i < n; i++) {
        int num = idx[i];
        d.vis[num] = true;
        if (num > 0) d.unite(num, num - 1);
        if (num < n - 1) d.unite(num, num + 1);
        if (d.cc <= k) {
            return arr[num];
        }
    }

    assert(false);
}

int main() {

    print(solve(5, 3, {1, 7, 3, 2, 2}));
    print(solve(6, 2, {1, 1, 10, 3, 5, 8}));

    return 0;
}