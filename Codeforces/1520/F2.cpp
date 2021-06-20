/**
 *    author:  Shivam Gupta
 *    created: 02.06.2021 12:25:20
**/

#include <bits/stdc++.h>
using namespace std;

template <typename A, typename B> string to_string(pair<A, B> p);
string to_string(const char& ch) { return "'" + string(1, ch) + "'"; }
string to_string(const string& s) { return '"' + s + '"'; }
string to_string(const char* s) { return to_string((string) s); }
string to_string(bool b) { return (b ? "true" : "false"); }
string to_string(vector<bool> v) { bool first = true; string res = "{"; for (int i = 0; i < static_cast<int>(v.size()); i++) { if (!first) { res += ", "; } first = false; res += to_string(v[i]); } res += "}"; return res; }
template <typename A> string to_string(A v) { bool first = true; string res = "{"; for (const auto &x : v) { if (!first) { res += ", "; } first = false; res += to_string(x); } res += "}"; return res; }
template <typename A, typename B> string to_string(pair<A, B> p) { return "(" + to_string(p.first) + ", " + to_string(p.second) + ")"; }
#define output cout
void debug_out() { output << endl; }
template <typename Head, typename... Tail> void debug_out(Head H, Tail... T) { output << " " << to_string(H); debug_out(T...); }
#ifndef ONLINE_JUDGE
#define dbg(...) output << "[" << #__VA_ARGS__ << "] :", debug_out(__VA_ARGS__)
#else
#define dbg(...) 42
#endif

#define int             int64_t
#define vii             vector<int>
#define viii            vector<vector<int>>
#define pii             pair<int, int>
#define vpii            vector<pair<int, int>>
#define all(v)          (v).begin(), (v).end()
#define sz(v)           (int)(v).size()
#define pb              push_back
#define in              insert
#define F               first
#define S               second
#define inf             1e18

template <typename T, typename U> istream& operator>>(istream& in, pair<T, U>& a) { in >> a.F >> a.S; return in; }
template <typename T, typename U> ostream& operator<<(ostream& out, pair<T, U>& a) { out << a.F << " " << a.S; return out; }
template <typename T> istream& operator>>(istream& in, vector<T>& a) { for (T& x : a) in >> x; return in; }
template <typename T> ostream& operator<<(ostream& out, vector<T>& a) { bool f = false; for (T& x : a) { if (f) out << " "; out << x; f = true; } return out; }
template <typename T> ostream& operator<<(ostream& out, vector<vector<T>>& a) { bool f = false; for (vector<T>& x : a) { if (f) out << "\n"; out << x; f = true; } return out; }

void out(bool ok, bool cap = true) { if (cap) cout << (ok ? "YES" : "NO") << '\n'; else cout << (ok ? "Yes" : "No") << '\n'; }

void print() { cout << '\n'; }
template <typename Head> void print(Head H) { cout << H; print(); }
template <typename Head, typename... Tail> void print(Head H, Tail... T) { cout << H << " "; print(T...); }

template <typename T, typename U> T amax(T& a, U b) { if (b > a) a = b; return a; }
template <typename T, typename U> T amin(T& a, U b) { if (b < a) a = b; return a; }

const int mod = 1000000007;
const int N = 3e5 + 5;

void preSolve(int &t) {
}
struct segnode {
    int a;
    segnode(int _a = 0) : a(_a) {}
    segnode operator+ (const segnode& other) const {
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
        nodes.assign(2 * size, -1);
    }

    segtree(int n, vector<input> &a) {
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

    void updater(int a, int b) {
        int i = size / (b - a) + a / (b - a);
        nodes[i] = 1;
        int change = -1;
        while (i) {
            if (nodes[i] != -1)
                nodes[i] += change;
            i >>= 1;
        }
    }

    int& show(int a, int b) {
        return nodes[size / (b - a) + a / (b - a)];
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
    int n, t;
    cin >> n >> t;

    int verdict;
    auto ask = [&] (int x) {
        cout << "! " << x + 1 << endl;
    };

    segtree<int, int> sg(n);

    auto query = [&] (int a, int b) {
        if (sg.show(a, b) != -1)
            verdict = sg.show(a, b);
        else if (a >= n)
            verdict = 0;
        else {
            cout << "? " << a + 1 << ' ' << min(b, n) << endl;
            cin >> verdict;
            if (verdict == -1)
                exit(0);
            verdict = b - a - verdict;
            sg.show(a, b) = verdict;
        }
        dbg(a, b, verdict);
        return verdict;
    };


    while (t--) {
        int k;
        cin >> k;
        if (k == -1)
            exit(0);

        function<void (int, int, int)> find;
        find = [&] (int k_, int a, int b) {
            dbg(sg.nodes);
            if (b - a == 1) {
                ask(a);
                sg.updater(a, b);
                return;
            }
            int m = (a + b) / 2;
            if (k_ <= query(a, m))
                find(k_, a, m);
            else {
                find(k_ - verdict, m, b);
            }
        };

        find(k, 0, 1 << (64 - __builtin_clzll(n)));
    }
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t = 1;
    preSolve(t);
    for (int i = 1; i <= t; i++) {
        // cout << "Case #" << i << ": ";
        solve(i);
    }
    return 0;
}
