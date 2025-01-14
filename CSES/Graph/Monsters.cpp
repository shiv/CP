/**
 *    author:  Shivam Gupta
 *    created: 21.05.2021 01:32:02
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

#define FASTIO          ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
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
#define inf             LLONG_MAX
#define For(i, a, b)    for (int i = (a); i < (b); i++)
#define Rev(i, a, b)    for (int i = (b - 1); i >= (a); i--)
#define Fore(i, a, b)   for (int i = (a); i <= (b); i++)
#define Reve(i, a, b)   for (int i = (b); i >= (a); i--)

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

vii dx = {0 , 0, 1, -1};
vii dy = {1, -1, 0, 0};
string ds = "RLDU";

bool possible(int x,int y, int n, int m) {      // [n, m)
    return  0 <= x && x < n && 0 <= y && y < m;
}


void solve(int tc = 0) {
    int n, m;
    cin >> n >> m;
    vector<vector<char>> s(n, vector<char>(m));
    cin >> s;

    vpii A;
    vpii M;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (s[i][j] == 'A')
                A.pb({i, j});
            else if (s[i][j] == 'M')
                M.pb({i, j});

    viii min_A(n, vii(m, inf));
    viii min_M(n, vii(m, inf));
    vector<vector<char>> path(n, vector<char>(m, 'O'));

    auto bfs = [&] (vpii& a, viii& visited, int not_monster = 0) {
        queue<pii> q;
        for (auto& p : a) {
            q.push(p);
            visited[p.F][p.S] = 0;
        }

        while (!q.empty()) {
            auto curr = q.front();
            q.pop();
            int depth = visited[curr.F][curr.S];

            for (int i = 0; i < 4; i++) {
                int x = curr.F + dx[i];
                int y = curr.S + dy[i];
                if (possible(x, y, n, m) && visited[x][y] == inf && s[x][y] == '.') {
                    q.push({x, y});
                    visited[x][y] = depth + 1;
                    if (not_monster == 1)
                        path[x][y] = ds[i];
                }
            }
        }
    };

    bfs(A, min_A, 1);
    bfs(M, min_M, 0);

    for (int i = 0; i < n; i++) {
        for (int j = 0;j < m; j++) {
            if (i == 0 || j == 0 || i == n - 1 || j == m - 1) {
                if (min_A[i][j] < min_M[i][j]) {
                    string p;
                    while (path[i][j] != 'O') {
                        p += path[i][j];
                        for (int k = 0; k < 4; k++) {
                            if (path[i][j] == ds[k]) {
                                i -= dx[k];
                                j -= dy[k];
                                break;
                            }
                        }
                    }
                    reverse(all(p));
                    print("YES");
                    print(sz(p));
                    print(p);
                    return;
                }
            }
        }
    }

    print("NO");
}

signed main() {
    FASTIO;
    int t = 1;
    preSolve(t);
    for (int i = 1; i <= t; i++) {
        // cout << "Case #" << i << ": ";
        solve(i);
    }
    return 0;
}
