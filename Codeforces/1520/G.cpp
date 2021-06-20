/**
 *    author:  Shivam Gupta
 *    created: 02.06.2021 16:53:53
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

int dx[] = {0 , 0, 1, -1};
int dy[] = {1, -1, 0, 0};
string ds = "RLDU";

bool possible(int x,int y, int n, int m) {
    return  0 <= x && x < n && 0 <= y && y < m;
}

void solve(int tc = 0) {
    int n, m, w;
    cin >> n >> m >> w;
    viii d(n, vii(m));
    cin >> d;

    auto bfs = [&] (int i, int j, viii& vis) {
        int ans = inf;
        queue<pii> q;
        vis[i][j] = 0;
        q.emplace(i, j);

        while (!q.empty()) {
            auto [a, b] = q.front();
            q.pop();
            if (d[a][b] > 0)
                amin(ans, d[a][b] + w * vis[a][b]);

            for (int k = 0; k < 4; k++) {
                int x = a + dx[k];
                int y = b + dy[k];
                if (possible(x, y, n, m) && d[x][y] != -1 && vis[x][y] == -1) {
                    vis[x][y] = vis[a][b] + 1;
                    q.emplace(x, y);
                }
            }
        }
        return ans;
    };

    viii vis1(n, vii(m, -1));
    viii vis2(n, vii(m, -1));
    int ans1 = bfs(0, 0, vis1);
    int ans2 = bfs(n - 1, m - 1, vis2);

    int ans = inf;
    amin(ans, ans1 + ans2);
    if (vis2[0][0] != -1)
        amin(ans, w * vis2[0][0]);

    print(ans >= inf ? -1 : ans);
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
