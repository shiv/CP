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

#define int int64_t
const int inf = 1e18L + 5, mod = 1e9 + 7, N = 2e5 + 5;


class segnode {
public:

    int a;
    segnode(int _a = 0) : a(_a) {}

    segnode operator+(const segnode &other) const {
        segnode ans;
        // merging of two segnodes
        ans.a = a + other.a;
        return ans;
    }

    friend istream& operator>>(istream& in, segnode &n) {
        return in >> n.a;
    }
    friend ostream& operator<<(ostream& out, const segnode &n) {
        return out << n.a;
    }
};

template<typename input, typename node>
class segtree {
public:

    int size;
    vector<node> nodes;

    // neutral node
    node identity_element = node(0);

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

int solve(int q, vector<vector<int>> queries) {

    auto exp = [&](int x, int y, int m = mod) {
        int res = 1; x = x % m;
        while (y > 0) {
            if (y & 1) res = (res * x) % m;
            y = y >> 1;
            x = (x * x) % m;
        }
        return res;
    };

    const int N = 1e1 + 5;
    vector<int> v(N);
    for (int i = 0; i < N; i++) {
        v[i] = exp(2, i / 2);
    }

    segtree<int, int> st(v);

    int ans = 0;
    for (int i = 0; i < q; i++) {
        ans += st.query(queries[i][0], queries[i][1]);
    }

    return ans;
}

signed main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
    // cin >> t;

    for (int tt = 1; tt <= t; tt++) {
        print(solve(2, {{2, 4}, {3, 4}}));
        print(solve(2, {{2, 3}, {1, 3}}));
    }

    return 0;
}