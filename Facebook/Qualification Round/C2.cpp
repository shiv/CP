#include "bits/stdc++.h"
#include <iterator>
using namespace std;

bool debug;
template <typename T, typename U> istream& operator>>(istream &is, pair<T, U> &p) { return is >> p.first >> p.second;}
template <typename T, typename U> ostream& operator<<(ostream &os, const pair<T, U> &p) { return debug ? os << "(" << p.first << ", " << p.second << ")" : os << p.first << " " << p.second; }
template <typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> istream &operator>>(istream &is, T_container &v) { for (T &x : v) is >> x; return is; }
template <typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream &operator<<(ostream &os, const T_container &v) { bool f = false; if(debug) { os << "{"; for (const T &x : v) { if (f) os << ", "; os << x; f = true; } os << "}"; } else { for (const T &x : v) { if (f) os << " "; os << x; f = true; } } return os; }
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

int n, k;

void preSolve(int &t) {
    cin >> t;
}

set<int> find_leaves (const vector<set<int>> &g) {
    set<int> leaves;
    for (int i = 1; i < n; i++) {
        if (g[i].size() == 1) {
            leaves.insert(i);
        }
    }
    return leaves;
}

void remove (int u, int v, vector<set<int>> &g) {
    if (u == -1 || v == -1) {
        return;
    }
    g[u].erase(v);
    g[v].erase(u);
}

int empty_the_gold (int leaf, vector<int> &gold, const vector<int> &parent, vector<set<int>> &g) {
    int res = 0;
    while (leaf != -1) {
        remove(leaf, parent[leaf], g);
        res += gold[leaf];
        gold[leaf] = 0;
        leaf = parent[leaf];
    }
    return res;
};


void find_parents (int u, int w, vector<int> &parent, bool ok, const vector<set<int>> &g) {
    for (auto &v : g[u]) {
        if (v != w) {
            parent[v] = ok ? u : (w == -1 ? v : parent[u]);
            find_parents(v, u, parent, ok, g);
        }
    }
}

void gold_rush (int u, int w, vector<int> &gold, const vector<set<int>> &g, int &leaf) {
    if (leaf == -1 || gold[u] > gold[leaf]) {
        leaf = u;
    }
    for (auto &v : g[u]) {
        if (v != w) {
            gold[v] += gold[u];
            gold_rush(v, u, gold, g, leaf);
        }
    }
}

pair<int, int> check_all (int leaf, const vector<set<int>> &g, vector<int> gold) {
    pair<int, int> p = {-1, -1};
    gold_rush(leaf, -1, gold, g, p.second);
    p.first = gold[p.second];
    return p;
};

int go_for_it (int leaf, vector<set<int>> g, vector<int> gold, vector<int> parent, bool ok) {
    int res = empty_the_gold(leaf, gold, parent, g);
    if (ok) {
        int curr = 0;
        for (auto leaf_ : find_leaves(g)) {
            vector<int> parent(n, -1);
            vector<int> s_parent(n, -1);
            find_parents(0, -1, parent, true, g);
            find_parents(0, -1, s_parent, false, g);
            if (g[0].find(s_parent[leaf_]) != g[0].end()) {
                amax(curr, go_for_it(leaf_, g, gold, parent, false));
            }
        }
        amax(curr, go_for_it(0, g, gold, parent, false));
        res += curr;
    }
    else {
        for (int i = 0; i < k - 1; i++) {
            int res_ = 0;
            int mx = 0, cave_from = -1, cave_to = -1;
            for (auto leaf_ : find_leaves(g)) {
                pair<int, int> curr = check_all(leaf_, g, gold);
                if (mx < curr.first) {
                    mx = curr.first;
                    cave_to = curr.second;
                    cave_from = leaf_;
                }
            }
            if (cave_from != -1) {
                vector<int> parent(n, -1);
                find_parents(cave_from, -1, parent, true, g);
                res_ = empty_the_gold(cave_to, gold, parent, g);
            }
            res += res_;
        }
    }
    return res;
}

void solve() {

    cin >> n >> k;
    vector<int> c(n);
    cin >> c;
    vector<pair<int, int>> tunnels(n - 1);
    cin >> tunnels;

    vector<set<int>> g(n);
    for (auto &[u, v] : tunnels) {
        u--, v--;
        g[u].insert(v);
        g[v].insert(u);
    }

    if (k == 0 || n == 1) {
        print(c[0]);
        return;
    }

    int ans = 0;

    vector<int> parent(n, -1);
    find_parents(0, -1, parent, true, g);
    for (auto leaf : find_leaves(g)) {
        amax(ans, go_for_it(leaf, g, c, parent, true));
    }

    print(ans);
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    #ifdef LOCAL
        auto f1 = freopen("C2.in", "r", stdin);
        auto f2 = freopen("C2.ou", "w", stdout);
    #endif
    int t = 1;
    preSolve(t);
    for (int i = 1; i <= t; i++) {
        cout << "Case #" << i << ": ";
        solve();
    }
    return 0;
}