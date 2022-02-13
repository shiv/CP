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



vector<int> solve(int n, string s, vector<vector<int>> ar) {

    vector<int> idx;

    for (int i = 0; i < n; i++) {
        if (s[i] == 'F') {
            idx.push_back(i);
        }
    }

    if (idx.size() <= 1) {
        return vector<int>(ar.size(), 0);
    }

    int cnt = idx.size();
    int pos = -1;
    int cur = -1;
    for(int i = 0; i < n; i++)
    {
        if(s[i] == 'F')
        {
            cur++;
            if(cur == cnt / 2)
                pos = i;
        }
    }
    int cnt_x = 0, cnt_y = 0;
    cur = pos - cnt / 2;
    for(int i = 0; i < n; i++)
        if(s[i] == 'F')
        {
            cnt_x += abs(cur - i);
            cur++;
        }


    for (int i = idx.front(); i <= idx.back(); i++) {
        cnt_y += s[i] == 'D';
    }

    vector<int> ans;

    for (auto &v : ar) {
        int x = v[0], y = v[1];
        ans.push_back(x * cnt_x + y * cnt_y);
    }

    return ans;
}

int main() {

    cout << solve(10, "---F-FD-F-", {{2, 10}}) << endl;
    cout << solve(10, "---FFFFF--", {{2, 10}}) << endl;
    cout << solve(10, "---FFF--F-", {{2, 10}}) << endl;

    return 0;
}