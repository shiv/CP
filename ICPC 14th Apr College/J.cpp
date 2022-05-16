#include "bits/stdc++.h"
#include <cstdarg>
#include <functional>
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

void solve() {
    int n,p;
    cin >> n >> p;
    --p;
    map<int, string> mp;
    for(int i=0;i<n;i++) {
        string s; cin >>s;
        mp[i]=s;
    }
    vector<int> adj[n];
    for(int i=0;i<n;i++) {
        int x; cin >> x;
        while(x--){
            int k; cin >> k;
            --k;
            adj[i].push_back(k);
        }
    }
    vector<bool> vis(n, false);
    function<void(int)> dfs = [&](int node) {
        vis[node]=1;
        for(int & u : adj[node]) {
            if(vis[u]) continue;
            dfs(u);
        }
    };
    dfs(p);
    vector<int> nds;
    for(int i=0;i<n;i++) {
        if(vis[i]){
            nds.push_back(i);
        }
    }
    // dbg(nds);
    int get = -1;
    function<bool(int)> chk = [&](int node) {
        vis[node]=1;
        // dbg(node);
        if(node == get) {
            return true;
        }
        for(int u : adj[node]) {
            if(vis[u]) continue;
            bool f = chk(u);
            if(f) {
                return true;
            }
        }
        return false;
    };
    vector<int> ans;
    for(int u : nds) {
        // dbg(u);
        get=u;
        bool flg = false;
        vis = vector<bool>(n, false);
        for(int & v : adj[u]) {
            // dbg(v);
            flg |= chk(v);
        }
        if(flg) {
            ans.push_back(u);
        }
    }
    if(ans.empty()) {
        cout << "Safe chain email!\n\n";
    }
    else{
        set<int> st;
        vis=vector<bool>(n, false);
        function<void(int)> d = [&](int node) {
            vis[node]=1;
            st.insert(node);
            for(int u : adj[node]) {
                if(vis[u]) continue;
                d(u);
            }
        };
        for(int u : ans){
            d(u);
        }
        for(int u : st) {
            cout << mp[u] << ' ';
        }
        cout << "\n\n";
    }
}

signed main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
    cin >> t;

    for (int tt = 1; tt <= t; tt++) {
        cout << "Chain Email #" << tt << ":\n";
        solve();
    }

    return 0;
}