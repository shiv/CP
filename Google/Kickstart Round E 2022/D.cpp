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
const pair<int, int> init = {-1, -1};

const int dx[] = {-1, 0, 0, 1};
const int dy[] = {0, 1, -1, 0};

bool possible (int r, int c, int n) {
    return 0 <= r && r < n && 0 <= c && c < n;
};

void solve() {

    int n, p, m, ar, ac;
    scan(n, p, m, ar, ac);
    ar--, ac--;

    if (p != 0) {
        print(0);
        return;
    }

    vector<vector<vector<int>>> dp(22, (vector<vector<int>> (11, vector<int>(11, -inf))));

    vector<pair<char, int>> cost(4);
    for (auto &[ch, d] : cost) {
        scan(ch, d);
    }

    auto div = [&] (int x, int y) {
        int res = x / y;
        if (res * y > x) {
            return res - 1;
        }
        return res;
    };

    vector<vector<pair<int, int>>> price(n, vector<pair<int, int>>(n, init));
    for (int i = 0; i < p; i++) {
        int x, y, c;
        scan(x, y, c);
        --x, --y;
        price[x][y] = {c, i};
    }

    dp[0][ar][ac] = 0;

    queue<array<int, 4>> q;
    q.push({ar, ac, 0, 0});

    while (!q.empty()) {
        auto [row, col, dis, c] = q.front(); q.pop();

        if (dp[dis][row][col] > c) {
            continue;
        }

        for (int dir = 0; dir < 4; dir++) {
            int nr = row + dx[dir], nc = col + dy[dir];

            if (!possible(nr, nc, n)) {
                continue;
            }
            int pizza_coins = 0;
            auto [ch, add] = cost[dir];
            int cc = 0;
            switch (ch) {
                case '+':
                    cc = c + add;
                    break;
                case '-':
                    cc = c - add;
                    break;
                case '*':
                    cc = c * add;
                    break;
                case '/':
                    cc = div(c, add);
                    break;
            }

            cc += pizza_coins;

            if (dis + 1 <= m && cc > dp[dis + 1][nr][nc]) {
                dp[dis + 1][nr][nc] = cc;
                q.push({nr, nc, dis + 1, cc});
            }
        }
    }

    int ans = -inf;
    for (int dis = 0; dis <= m; dis++) {
        for (int row = 0; row < n; row++) {
            for (int col = 0; col < n; col++) {
                ans = max(ans, dp[dis][row][col]);
            }
        }
    }

    print(ans);
}


signed main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
    cin >> t;

    for (int tt = 1; tt <= t; tt++) {
        cout << "Case #" << tt << ": ";
        solve();
    }

    return 0;
}