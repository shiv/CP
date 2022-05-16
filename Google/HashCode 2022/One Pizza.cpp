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

void solve() {

    int c;
    scan(c);

    unordered_map<string, int> umap;
    int counter = 0;

    vector<set<int>> likes(c), dislikes(c);
    vector<set<int>> liked_by(N), disliked_by(N);

    for (int i = 0; i < c; i++) {
        int sz;
        scan(sz);
        vector<string> likes_i(sz);
        scan(likes_i);
        for (auto &like : likes_i) {
            if (umap.find(like) == umap.end()) {
                umap[like] = counter++;
            }
            likes[i].emplace(umap[like]);
            liked_by[umap[like]].emplace(i);
        }
        scan(sz);
        vector<string> dislikes_i(sz);
        scan(dislikes_i);
        for (auto &dislike : dislikes_i) {
            if (umap.find(dislike) == umap.end()) {
                umap[dislike] = counter++;
            }
            dislikes[i].emplace(umap[dislike]);
            disliked_by[umap[dislike]].emplace(i);
        }
    }

    priority_queue<pair<int, int>> pq;
    vector<bool> vis(counter, false);

    for (int i = 0; i < counter; i++) {
        pq.emplace(liked_by[i].size(), i);
    }

    while (!pq.empty()) {
        auto [cnt, curr] = pq.top();
        pq.pop();
        if (vis[curr] && cnt != liked_by[curr].size()) {
            continue;
        }
        vis[curr] = false;
        for (auto &person : disliked_by[curr]) {
            for (auto &item : likes[person]) {
                if (!vis[item]) {
                    liked_by[item].erase(person);
                    pq.emplace(liked_by[item].size(), item);
                }
            }
        }
    }


}

signed main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
    // cin >> t;

    for (int tt = 1; tt <= t; tt++) {
        solve();
    }

    return 0;
}