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

template <typename T, typename Head, typename... Tail> T amax(T& a, Head b, Tail... c) { if (b > a) a = b; if constexpr (sizeof...(c) != 0) amax(a, c...); return a; }
template <typename T, typename Head, typename... Tail> T amin(T& a, Head b, Tail... c) { if (b < a) a = b; if constexpr (sizeof...(c) != 0) amin(a, c...); return a; }

class segtree {
public:

    int size;
    vector<int> nodes;

    // neutral int
    int identity_element = int(0);

    int merge(int &a, int &b) {
        // merging of two nodes
        return a + b;
    }

    int make_node(int &v) {
        // conversion of int to int
        int m = {v};
        return m;
    }

    segtree(int n) {
        size = 1;
        while (size < n) size <<= 1;
        nodes.resize(2 * size);
    }

    segtree(vector<int> &a) {
        int n = a.size();
        size = 1;
        while (size < n) size <<= 1;
        nodes.resize(2 * size);
        build(a);
    }

    void build(vector<int> &a, int x, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < (int)a.size())
                nodes[x] = make_node(a[lx]);
            return;
        }
        int m = (lx + rx) >> 1;
        build(a, x << 1 | 0, lx, m);
        build(a, x << 1 | 1, m, rx);
        nodes[x] = merge(nodes[x << 1 | 0], nodes[x << 1 | 1]);
    }

    void build(vector<int> &a) {
        build(a, 1, 0, size);
    }

    void update(int i, int v, int x, int lx, int rx) {
        if (rx - lx == 1) {
            nodes[x] = make_node(v);
            return;
        }
        int m = (lx + rx) >> 1;
        if (i < m)
            update(i, v, x << 1 | 0, lx, m);
        else
            update(i, v, x << 1 | 1, m, rx);
        nodes[x] = merge(nodes[x << 1 | 0], nodes[x << 1 | 1]);
    }

    void update(int i, int v) {
        update(i, v, 1, 0, size);
    }

    int query(int l, int r, int x, int lx, int rx) {
        if (lx >= r || l >= rx)
            return identity_element;
        if (lx >= l && rx <= r)
            return nodes[x];
        int m = (lx + rx) >> 1;
        int s1 = query(l, r, x << 1 | 0, lx, m);
        int s2 = query(l, r, x << 1 | 1, m, rx);
        return merge(s1, s2);
    }

    int query(int l, int r) {          // [l, r)
        return query(l, r, 1, 0, size);
    }
};

int goodString(int N, int Q, string S, vector<int> arr, vector<vector<int>> ranges) {

    int itr = 0;

    for (int i = 0; i < 26; i++) {
        char ch = 'a' + i;
        vector<int> v(N);
        for (int i = 0; i < N; i++) {
            v[i] = S[i] == ch;
        }
        segtree s(v);
        // print(ch, s.query(0, N));
        for (auto &range : ranges) {
            int u = range[0] - 1, v = range[1];
            // dbg(u + 1, v);
            while (s.query(u, v) > 1) {
                // dbg(itr);
                S[arr[itr] - 1] = '_';
                s.update(arr[itr] - 1, 0);
                itr += 1;
            }
        }
    }

    return itr;
}

signed main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
    // cin >> t;

    for (int tt = 1; tt <= t; tt++) {
        print(goodString(5, 2, "aaaaa", {2, 4, 1, 3, 5}, {{1, 2}, {4, 5}}));
        print(goodString(8, 4, "abbabaab", {6, 3, 5, 1, 4, 2, 7, 8}, {{1, 3}, {4, 7}, {3, 5}}));
    }

    return 0;
}