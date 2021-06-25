/**
 *    author:  Shivam Gupta
 *    created: 23.06.2021 12:57:43
**/

#include "bits/stdc++.h"
#include <algorithm>
using namespace std;

template <typename T, typename U> istream& operator>>(istream &is, pair<T, U> &p) { return is >> p.first >> p.second;} bool debug; template <typename T, typename U> ostream& operator<<(ostream &os, const pair<T, U> &p) { return debug ? os << "(" << p.first << ", " << p.second << ")" : os << p.first << " " << p.second; }
template <typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> istream &operator>>(istream &is, T_container &v) { for (T &x : v) is >> x; return is; } template <typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream &operator<<(ostream &os, const T_container &v) { bool f = false; if(debug) { os << "{"; for (const T &x : v) { if (f) os << ", "; os << x; f = true; } os << "}"; } else { for (const T &x : v) { if (f) os << " "; os << x; f = true; } } return os; }
void out(bool ok, bool cap = true) { cap ? cout << (ok ? "YES" : "NO") : cout << (ok ? "Yes" : "No"); cout << "\n"; }
void print() { cout << "\n"; } template <typename Head, typename... Tail> void print(Head H, Tail... T) { cout << H << " "; print(T...); }
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

struct segnode {
    int a;
    segnode(int _a = 0) : a(_a) {}
    segnode operator+ (const segnode &other) const {
        segnode ans;
        // merging of two segnodes
        ans.a = a + other.a;
        return ans;
    }
};

istream& operator>>(istream& in, segnode node) {
    in >> node.a;
    return in;
}

ostream& operator<<(ostream& out, segnode node) {
    out << node.a;
    return out;
}

template<typename input, typename node>
struct segtree {

    int size;
    vector<node> nodes;

    // neutral node
    node identity_element = {0};

    node merge(node &a, node &b) {
        // merging of two nodes
        return a + b;
    }

    node make_node(input &v) {
        // conversion of input to node
        node m = {v};
        return m;
    }

    segtree(int n) {
        size = 1;
        while (size < n) size <<= 1;
        nodes.resize(2 * size);
    }

    segtree(vector<input> &a) {
        int n = a.size();
        size = 1;
        while (size < n) size <<= 1;
        nodes.resize(2 * size);
        build(a);
    }

    void build(vector<input> &a, int x, int lx, int rx) {
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

    void build(vector<input> &a) {
        build(a, 1, 0, size);
    }

    void update(int i, input v, int x, int lx, int rx) {
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

    void update(int i, input v) {
        update(i, v, 1, 0, size);
    }

    node query(int l, int r, int x, int lx, int rx) {
        if (lx >= r || l >= rx)
            return identity_element;
        if (lx >= l && rx <= r)
            return nodes[x];
        int m = (lx + rx) >> 1;
        node s1 = query(l, r, x << 1 | 0, lx, m);
        node s2 = query(l, r, x << 1 | 1, m, rx);
        return merge(s1, s2);
    }

    node query(int l, int r) {          // [l, r)
        return query(l, r, 1, 0, size);
    }
};

void solve(int tc = 0) {
    int n, q;
    cin >> n >> q;
    vector<int> x(n);
    cin >> x;

    segtree<int, int> seg(x);

    while (q--) {
        int type;
        cin >> type;

        if (type == 1) {
            int k, u;
            cin >> k >> u;

            seg.update(k - 1, u);
        }
        if (type == 2) {
            int a, b;
            cin >> a >> b;

            print(seg.query(a - 1, b));
        }
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