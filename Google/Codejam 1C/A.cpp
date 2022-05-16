#include "bits/stdc++.h"
#include <algorithm>
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

#define END { print("IMPOSSIBLE"); return; }

void solve() {

    int n;
    scan(n);
    vector<string> a(n);
    scan(a);
    const int MAX = 256;
    vector<vector<int>> p(MAX), s(MAX), c(MAX);
    vector<bool> im(MAX);
    for (int i = 0; i < n; i++) {
        string &ss = a[i];
        int m = ss.size();
        if (set<int>(ss.begin(), ss.end()).size() != 1) {
            p[ss.front()].emplace_back(i);
            s[ss.back()].emplace_back(i);
            int l = 0, r = m - 1;
            while (r >= 0 && ss[r] == ss.back()) {
                r--;
            }
            while (l <= r && ss[l] == ss.front()) {
                l++;
            }
            // dbg(i, l, r);
            int j = l;
            while (j <= r) {
                int k = j;
                while (k <= r && ss[k] == ss[j]) {
                    k++;
                }
                if (im[ss[j]]) {
                    END;
                }
                im[ss[j]] = true;
                j = k;
            }
        }
        else {
            c[ss[0]].emplace_back(i);
        }
    }
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        // dbg(ch, p[ch], s[ch], c[ch], im[ch]);
        if (im[ch] && (p[ch].size() || s[ch].size() || c[ch].size())) END;
        if (p[ch].size() > 1) END;
        if (s[ch].size() > 1) END;
    }
    vector<bool> used(n);
    vector<bool> vis(MAX);
    string res = "";
    for (char cc = 'A'; cc <= 'Z'; cc++) {
        if (!vis[cc]) {
            char ch = cc;
            vector<int> v1;
            while (true) {
                vis[ch] = true;
                while (c[ch].size()) {
                    v1.push_back(c[ch].back());
                    used[c[ch].back()] = true;
                    c[ch].pop_back();
                }
                char nch = ch;
                while (p[ch].size()) {
                    if (used[p[ch].back()]) END;
                    used[p[ch].back()] = true;
                    v1.push_back(p[ch].back());
                    nch = a[p[ch].back()].back();
                    p[ch].pop_back();
                }
                if (nch == ch) {
                    break;
                }
                ch = nch;
            }
            vector<int> v2;
            ch = cc;
            while (true) {
                vis[ch] = true;
                while (c[ch].size()) {
                    v2.push_back(c[ch].back());
                    used[c[ch].back()] = true;
                    c[ch].pop_back();
                }
                char nch = ch;
                while (s[ch].size()) {
                    if (used[s[ch].back()]) END;
                    used[s[ch].back()] = true;
                    v2.push_back(s[ch].back());
                    nch = a[s[ch].back()].front();
                    s[ch].pop_back();
                }
                if (nch == ch) {
                    break;
                }
                ch = nch;
            }
            for (int i = int(v2.size()) - 1; i >= 0; i--) {
                res += a[v2[i]];
            }
            for (int &i : v1) {
                res += a[i];
            }
        }
    }
    if (count(used.begin(), used.end(), false) > 0) END;
    print(res);
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