/**
 *    author:  Shivam Gupta
 *    created: 24.06.2021 14:59:53
**/

#include "bits/stdc++.h"
using namespace std;

template <typename T, typename U> istream& operator>>(istream &is, pair<T, U> &p) { return is >> p.first >> p.second;} bool debug; template <typename T, typename U> ostream& operator<<(ostream &os, const pair<T, U> &p) { return debug ? os << "(" << p.first << ", " << p.second << ")" : os << p.first << " " << p.second; }
template <typename T_container, typename T = typename enable_if<!is_same<T_container, string>::sumue, typename T_container::sumue_type>::type> istream &operator>>(istream &is, T_container &v) { for (T &x : v) is >> x; return is; } template <typename T_container, typename T = typename enable_if<!is_same<T_container, string>::sumue, typename T_container::sumue_type>::type> ostream &operator<<(ostream &os, const T_container &v) { bool f = false; if(debug) { os << "{"; for (const T &x : v) { if (f) os << ", "; os << x; f = true; } os << "}"; } else { for (const T &x : v) { if (f) os << " "; os << x; f = true; } } return os; }
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

template<typename input>
class segtree {
public:

    class node {
    public:

        int seg, pre, suf, sum, lazy;

        friend istream& operator>>(istream &in, node &n) {
            return in >> n.seg;
        }
        friend ostream& operator<<(ostream &out, const node &n) {
            return out << n.seg;
        }

        // set initial sumues (_sum is initial sumue of node and _lazy is identity for lazy operation)
        node(int _sum = 0, int _lazy = inf) : sum(_sum), lazy(_lazy) {
            pre = suf = seg = _sum;
        }

        // merge operation
        friend node merge(node &a, node &b) {
            node c;
            c.seg = max({a.suf + b.pre, a.seg, b.seg});
            c.pre = max({a.pre, a.sum + b.pre});
            c.suf = max({a.suf + b.sum, b.suf});
            c.sum = a.sum + b.sum;
            return c;
        }

        // lazy operation
        void apply(int lx, int rx, const node &other) {
            sum = other.lazy * (rx - lx);
            lazy = other.lazy;
            if (other.lazy < 0)
                pre = suf = seg = 0;
            else
                pre = suf = seg = sum;
        }
    };

    // neutral element (identity for merge operation)
    node identity_element = node(0);

    // conversion of input to node
    node make_node(input sum, input lazy) {
        node m = node(sum, lazy);
        return m;
    }

    int n, size;
    vector<node> nodes;

    inline void push(int x, int lx, int rx) {
        if (nodes[x].lazy != identity_element.lazy) {
            int m = (lx + rx) >> 1;
            nodes[x << 1 | 0].apply(lx, m, nodes[x]);
            nodes[x << 1 | 1].apply(m, rx, nodes[x]);
            nodes[x].lazy = identity_element.lazy;
        }
    }

    inline void pull(int x, int lx, int rx) {
        nodes[x] = merge(nodes[x << 1 | 0], nodes[x << 1 | 1]);
    }

    segtree(int _n) : n(_n) {
        size = 1;
        while (size < n) size <<= 1;
        nodes.resize(2 * size);
    }

    segtree(vector<input> &a) : segtree(a.size()) {
        build(a);
    }

    void build(vector<input> &a, int x, int lx, int rx) {
        if (rx - lx == 1) {
            if (lx < (int)a.size())
                nodes[x] = make_node(a[lx], node().lazy);
            return;
        }
        int m = (lx + rx) >> 1;
        build(a, x << 1 | 0, lx, m);
        build(a, x << 1 | 1, m, rx);
        pull(x, lx, rx);
    }

    void build(vector<input> &a) {
        build(a, 1, 0, size);
    }

    void update(int l, int r, input v, int x, int lx, int rx) {
        if (lx >= r || l >= rx)
            return;
        if (lx >= l && rx <= r) {
            nodes[x].apply(lx, rx, make_node(node().sum, v));
            return;
        }
        push(x, lx, rx);
        int m = (lx + rx) >> 1;
        update(l, r, v, x << 1 | 0, lx, m);
        update(l, r, v, x << 1 | 1, m, rx);
        pull(x, lx, rx);
    }

    void update(int l, int r, input v) {
        assert(0 <= l && l <= r && r < n);
        update(l, r + 1, v, 1, 0, size);
    }

    void update(int i, input v) {
        update(i, i, v);
    }

    node query(int l, int r, int x, int lx, int rx) {
        if (lx >= r || l >= rx)
            return identity_element;
        if (lx >= l && rx <= r)
            return nodes[x];
        push(x, lx, rx);
        int m = (lx + rx) >> 1;
        node q1 = query(l, r, x << 1 | 0, lx, m);
        node q2 = query(l, r, x << 1 | 1, m, rx);
        pull(x, lx, rx);
        return merge(q1, q2);
    }

    node query(int l, int r) {
        assert(0 <= l && l <= r && r < n);
        return query(l, r + 1, 1, 0, size);
    }

    node query(int i) {
        return query(i, i);
    }
};

void solve(int tc = 0) {
    int n, m;
    cin >> n >> m;

    segtree<int> seg(n);

    while (m--) {
        int l, r, v;
        cin >> l >> r >> v;

        seg.update(l, r - 1, v);
        print(seg.query(0, n - 1));
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