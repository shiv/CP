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

    set<vii> s;
    vii vec;

    auto doit = [&] () {
        for (int i = 0; i < (1 << sz(vec)); i++) {
            vii v;
            for (int j = 0; j < sz(vec); j++)
                if (i & (1 << j))
                    v.pb(vec[j] + 1);
            if (!v.empty()) {
                sort(all(v));
                s.insert(v);
            }
        }
    };

    vii parent(n, -1);
    function<void (int, int)> dfs;
    dfs = [&] (int v, int w) {
        vec.pb(v);
        doit();
        for (auto& u : g[v]) {
            if (u == w)
                continue;
            dfs(u, v);
        }
        vec.pop_back();
    };

    for (int i = 0; i < n; i++) {
        fill(all(parent), -1);
        dfs(i, -1);
    }

    // dbg(s);
    cout << sz(s) << '\n';
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