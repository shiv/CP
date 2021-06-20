#include <bits/stdc++.h>
using namespace std;

string to_string(const char& ch) { return "'" + string(1, ch) + "'"; }
string to_string(const string& s) { return '"' + s + '"'; }
string to_string(const char* s) { return to_string((string) s); }
string to_string(bool b) { return (b ? "true" : "false"); }
string to_string(vector<bool> v) { bool first = true; string res = "{"; for (int i = 0; i < static_cast<int>(v.size()); i++) { if (!first) { res += ", "; } first = false; res += to_string(v[i]); } res += "}"; return res; }
template <typename A, typename B> string to_string(pair<A, B> p) { return "(" + to_string(p.first) + ", " + to_string(p.second) + ")"; }
template <typename A> string to_string(A v) { bool first = true; string res = "{"; for (const auto &x : v) { if (!first) { res += ", "; } first = false; res += to_string(x); } res += "}"; return res; }
#define output cout
void debug_out() { output << endl; }
template <typename Head, typename... Tail> void debug_out(Head H, Tail... T) { output << " " << to_string(H); debug_out(T...); }
#ifndef ONLINE_JUDGE
#define dbg(...) output << "[" << #__VA_ARGS__ << "] :", debug_out(__VA_ARGS__)
#else
#define dbg(...) 42
#endif

#define int             long long
#define vii             vector<int>
#define viii            vector<vector<int>>
#define pii             pair<int, int>
#define all(v)          (v).begin(), (v).end()
#define sz(v)           (int)(v).size()
#define pb              push_back
#define F               first
#define S               second
#define For(i, a, b)    for (int i = a; i < b; i++)
#define inf             LLONG_MAX

const int mod = 1000000007;

void presolve(int &t) {
    cin >> t;
}

void solve() {
    int n;
    cin >> n;
    
    viii g(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u - 1].pb(v - 1);
        g[v - 1].pb(u - 1);
    }

    vii ans;
    int k = 0, t = 0;

    vii parent(n, -1);
    vii depth(n, 0);
    vii dead(n, 0);

    viii ass(n);
    vii leaves;
    vii curfew(n, 0);

    function<void (int, int)> dfs;
    dfs = [&] (int v, int w) {

        auto it = find(all(g[v]), w);
        if (it != g[v].end())
            g[v].erase(it);

        for (auto& u : g[v]) {
            depth[u] = depth[v] + 1;
            parent[u] = v;
            dfs(u, v);
        }

        if (g[v].empty()) {
            ass[v].pb(v);
            leaves.pb(v);
        }

    };
    dfs(0, -1);

    function<void (int, int)> dfs_leaf;
    dfs_leaf = [&] (int v, int home) {
        bool ok = true;

        for (auto& u : g[v]) {
            if (dead[u])
                continue;
            dfs_leaf(u, home);
            ok = false;
        }

        if (ok)
            ass[home].pb(v);

        if (v != home)
            dead[v] = 1;
    };

    auto sort_leaves = [&] () {
        unordered_set<int> tem(all(leaves));
        leaves.assign(all(tem));
        sort(all(leaves), [&] (const int& a, const int& b) {
            return depth[a] < depth[b];
        });
    };
    sort_leaves();

    while (true) {
        t += 1;
        vii curr_leaves;
        curr_leaves.swap(leaves);

        for (auto& leaf : curr_leaves) {
            if (dead[leaf])
                continue;
            if (curfew[leaf]) {
                curfew[leaf] = 0;
                leaves.pb(leaf);
                continue;
            }
            int parent_leaf = parent[leaf];
            ass[parent_leaf].pb(leaf);
            dead[leaf] = 1;
            leaves.pb(parent_leaf);
        }
        sort_leaves();

        if (leaves.front() == 0)
            break;

        for (auto& jun : leaves) {
            if (dead[jun])
                continue;
            bool ok = true;
            for (auto& leaf : g[jun])
                if (!dead[leaf])
                    ok = false;
            if (ok)
                continue;
            ass[jun].clear();
            curfew[jun] = 1;
            dfs_leaf(jun, jun);
        }
    }

    function<void (int)> collect;
    collect = [&] (int i) {
        if (ass[i][0] == i) {
            ans.pb(i);
            return;
        }
        for (auto& j : ass[i])
            collect(j);
    };
    for (auto& i: ass[0])
        collect(i);
    sort(all(ans));
    k = sz(ans);

    cout << k << ' ' << t << '\n';
    for (auto& i : ans)
        cout << i + 1 << ' ';
    cout << '\n';
}


signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t = 1;
    presolve(t);
    for (int i = 1; i <= t; i++)
        solve();
    return 0;
}