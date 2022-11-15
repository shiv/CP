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

// #define int int64_t
// const int inf = 1e18L + 5, mod = 1e9 + 7, N = 2e5 + 5;

long solve(vector<int> &a, vector<int> &b, int C) {
    #define int long
    a.insert(a.begin(),0);
    b.insert(b.begin(),0);
    int n = a.size();
    vector<int>ord(n);
    iota(ord.begin(),ord.end(),0);
    sort(ord.begin(),ord.end(),[&] (auto &x, auto &y){
        return a[x]<a[y];
    });
    {
        vector<int> aa(n),bb(n);
        for(int i=0;i<n;i++){
            aa[i] = a[ord[i]];
            bb[i] = b[ord[i]];
        }
        for(int i=0;i<n;i++){
            a[i] = aa[i];
            b[i] = bb[i];
        }
    }
    const int inf = 1e18L + 5;
    vector<vector<int>> cst(n,vector<int>(n,inf));
    for(int i=0;i<n;i++){
        int cost =0;
        int cnt = 0;
        cst[i][i] = 0;
        for(int j=i+1;j<n;j++){
            cost+=cnt*(a[j]-a[j-1]);
            cst[i][j] = cost;
            cnt+=b[j];
        }
    }
    vector<int>dp(n,inf);
    dp[0]=0;
    for(int it =0;it<C;it++){
        vector<int> new_dp(n,inf);
        new_dp[0]=0;
        for(int i=1;i<n;i++){
            for(int j=0;j<i;j++){
                new_dp[i] = min(new_dp[i],dp[j] + cst[j][i]);
            }
        }
        swap(dp,new_dp);
    }
    #undef int
    return dp.back();
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