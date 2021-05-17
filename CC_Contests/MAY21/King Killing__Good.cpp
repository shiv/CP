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

const int mod = 1000000007;

void presolve(int &t) {
    cin >> t;
}

int power(int x, int y) {
    int res = 1;
    while (y) {
        if (y & 1)
            res = res * x % mod;
        x = x * x % mod;
        y >>= 1;
    }
    return res;
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

    vii parent(n);
    viii ass(n);
    map<int, int> pos;
    function<void (int, int)> dfs;
    dfs = [&] (int v, int w) {
        bool ok = true;
        for (auto& u : g[v]) {
            if (u == w)
                continue;
            parent[u] = v;
            ok = false;
            dfs(u, v);
        }
        if (ok) {
            ass[v].pb(v);
            pos[v] = v;
        }
    };
    dfs(0, -1);

    vii go(n);
    vii des;
    auto check = [&] (int i) {
        int curr = pos[i];
        go[i] = parent[curr];
        int j = curr;
        while (parent[j] != 0) {
            j = parent[j];
            if (!ass[j].empty()) {
                des.pb(j);
                go[i] = j;
            }
        }
    };

    int t = 0;
    while (ass[0].empty()) {
        des.clear();
        for (auto& [i, j] : pos)
            check(i);
        for (auto& i : des) {
            for (auto& j : ass[i])
                pos.erase(j);
            ass[i].clear();
        }
        for (auto& [i, j] : pos) {
            j = go[i];
            ass[j].pb(i);
        }
        t += 1;
    }
    sort(all(ass[0]));

    cout << sz(ass[0]) << ' ' << t << '\n';
    for (auto& i : ass[0])
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