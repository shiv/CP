#include "bits/stdc++.h"
using namespace std;

bool debug;
template <typename T, typename U> istream& operator>>(istream &is, pair<T, U> &p) { return is >> p.first >> p.second;}
template <typename T, typename U> ostream& operator<<(ostream &os, const pair<T, U> &p) { return debug ? os << "(" << p.first << ", " << p.second << ")" : os << p.first << " " << p.second; }
template <typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> istream &operator>>(istream &is, T_container &v) { for (T &x : v) is >> x; return is; }
template <typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream &operator<<(ostream &os, const T_container &v) { bool f = false; if(debug) { os << "{"; for (const T &x : v) { if (f) os << ", "; os << x; f = true; } os << "}"; } else { for (const T &x : v) { if (f) os << " "; os << x; f = true; } } return os; }
void scan() {} template <typename Head, typename ...Tail> void scan(Head &H, Tail &...T) { cin >> H; scan(T...); }
void print() { cout << "\n"; } template <typename Head> void print(const Head &H) { cout << H << "\n"; } template <typename Head, typename ...Tail> void print(const Head &H, const Tail &...T) { cout << H << " "; print(T...); }
void dbg_out() { cerr << "\n"; } template <typename Head, typename ...Tail> void dbg_out(const Head &H, const Tail &...T) { cerr << " " << H; dbg_out(T...); }
#ifndef ONLINE_JUDGE
#define dbg(...) cerr << "[" << #__VA_ARGS__ << "]:", debug = true, dbg_out(__VA_ARGS__), debug = false
#else
#define dbg(...)
#endif

template <typename T, typename Head, typename... Tail> T amax(T& a, Head b, Tail... c) { if (b > a) a = b; if constexpr (sizeof...(c) != 0) amax(a, c...); return a; }
template <typename T, typename Head, typename... Tail> T amin(T& a, Head b, Tail... c) { if (b < a) a = b; if constexpr (sizeof...(c) != 0) amin(a, c...); return a; }

#define int int64_t
const int inf = 1e18L + 5, mod = 1e9 + 7, N = 2e5 + 5;

class dsu {
public:
    vector<int> p;
    int n;

    dsu(int _n) : n(_n) {
        p.resize(n);
        iota(p.begin(), p.end(), 0);
    }

    inline int get(int x) {
        return (x == p[x] ? x : (p[x] = get(p[x])));
    }

    inline bool unite(int x, int y) {
        x = get(x);
        y = get(y);
        if (x != y) {
            p[x] = y;
            return true;
        }
        return false;
    }
};

int dx[] = {0 , 0, 1, -1};
int dy[] = {1, -1, 0, 0};

bool possible(int x, int y, int n = 4, int m = 4) {
    return  0 <= x && x < n && 0 <= y && y < m;
}

void solve() {

    int n = 4, m = n * n;
    vector<vector<int>> a(n, vector<int>(n));
    scan(a);

    int tot = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            tot += a[i][j];
        }
    }

    int ans = 0;

    for (int z = 1; z < 1 << m; z++) {

        bool verdict = true;

        vector<vector<int>> b(n, vector<int>(n));
        vector<vector<bool>> vis(n, vector<bool>(n, false));
        int cnt = 0;

        for (int mask = 0; mask < m; mask++) {
            if (z >> mask & 1) {
                b[mask / n][mask % n] = 1;
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (!vis[i][j] && b[i][j]) {
                    cnt += 1;
                    queue<pair<int, int>> q;
                    q.emplace(i, j);
                    while (!q.empty()) {
                        auto [x, y] = q.front();
                        q.pop();
                        if (vis[x][y]) {
                            continue;
                        }
                        vis[x][y] = true;
                        for (int j = 0; j < n; j++) {
                            int nx = x + dx[j];
                            int ny = y + dy[j];
                            if (possible(nx, ny, n, n) && b[nx][ny]) {
                                q.emplace(nx, ny);
                            }
                        }
                    }
                }
            }
        }

        verdict &= cnt == 1;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (a[i][j]) {
                    verdict &= b[i][j];
                }
            }
        }

        auto isbet = [&] (int x, int y) {
            return 1 <= x && x <= 2 && 1 <= y && y <= 2;
        };

        dsu d(17);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (!b[i][j]) {
                    if (!isbet(i, j)) {
                        d.unite(i * n + j, 16);
                    }
                    for (int k = 0; k < n; k++) {
                        int nx = i + dx[k];
                        int ny = j + dy[k];
                        if (possible(nx, ny) && !b[nx][ny]) {
                            d.unite(i * n + j, nx * n + ny);
                        }
                    }
                }
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (!b[i][j]) {
                    verdict &= d.get(16) == d.get(i * n + j);
                }
            }
        }

        ans += verdict;
    }

    print(ans);
}

signed main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t = 1;

    for (int tt = 1; tt <= t; tt++) {
        solve();
    }

    return 0;
}