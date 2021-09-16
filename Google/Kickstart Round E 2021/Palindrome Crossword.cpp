/**
 *    author:  Shivam Gupta
 *    created: 22.08.2021 09:58:10
**/

#include "bits/stdc++.h"
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

void preSolve(int &t) {
    cin >> t;
}
void solve() {

    int n, m;
    cin >> n >> m;
    vector<string> s(n);
    for(int i = 0; i < n; i++) {
        cin >> s[i];
    }

    vector<vector<pair<int, int>>> Rw(n), col(m);

    for(int j = 0; j < m; j++) {
        for(int i = 0; i < n; i++) {
            if(s[i][j] != '#') {
                if(i == 0 || s[i - 1][j] == '#') {
                    col[j].push_back({i, i});
                }
                else {
                    col[j].back().second = i;
                }
            }
        }
    }

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(s[i][j] != '#') {
                if(j == 0 || s[i][j - 1] == '#') {
                    Rw[i].push_back({j, j});
                }
                else {
                    Rw[i].back().second = j;
                }
            }
        }

    }

    vector<pair<int, int>> vec;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if('A' <= s[i][j] && s[i][j] <= 'Z') {
                vec.push_back({i, j});
            }
        }
    }

    int changes = 0;

    for(int i = 0; i < vec.size(); i++) {


        int r = vec[i].first;
        int c = vec[i].second;


        auto it = upper_bound(Rw[r].begin(), Rw[r].end(), pair(c + 1, int(0))) - 1;
        auto C = it->second + it->first - c;


        if(s[r][C] == s[r][c] || s[r][C] == '#') {
        }
        else {
            s[r][C] = s[r][c];
            changes++;
            vec.push_back({r, C});
        }

        it = upper_bound(col[c].begin(), col[c].end(), pair(r + 1, int(0))) - 1;
        auto R = it->second + it->first - r;

        if(s[r][c] == s[R][c] || s[R][c] == '#') {
        }
        else {
            s[R][c] = s[r][c];
            changes++;
            vec.push_back({R, c});
        }


    }

    print(changes);
    for(auto &s : s)  {
        print(s);
    }
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int testcases = 1;
    preSolve(testcases);
    for (int caseno = 1; caseno <= testcases; ++caseno) {
        cout << "Case #" << caseno << ": ";
        solve();
    }
    return 0;
}