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


int interval(vector<int> first, vector<int> last) {
#define int int64_t
    int n = first.size();
    vector<vector<int>> intervals(n);
    for (int i = 0; i < n; i++) {
        intervals[i].emplace_back(first[i]);
        intervals[i].emplace_back(last[i]);
    }
    sort(intervals.begin(), intervals.end(), [](const vector<int>& lhs, const vector<int>& rhs) {
        if (lhs[1] == rhs[1]) return lhs[0] > rhs[0];
        return lhs[1] < rhs[1];
    });

    int res = 0, first_ = -1, second = -1;
    for (auto interval : intervals) {
        int left = interval[0], right = interval[1];
        if (left > first_) {
            res += 2;
            first_ = right, second = right - 1;
        } else if (left > second) {
            res += 1;
            if (right > first_) {
                second = first_, first_ = right;
            } else {
                second = right;
            }
        }
    }
    return res;
#undef int
}

signed main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
// ÷    cin >> t;

    for (int tt = 1; tt <= t; tt++) {
        cout << interval({0, 1, 2}, {2, 3, 3}) << endl;
        cout << interval({1, 2, 1}, {3, 5, 4}) << endl;
        cout << interval({3, 2, 0, 4}, {6, 4, 2, 7}) << endl;
    }

    return 0;
}