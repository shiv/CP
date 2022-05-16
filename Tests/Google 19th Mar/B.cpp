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

#define int int64_t
struct segtree {
    int N=0;
    vector<int> seg, a;

    void init(int n) {
      N=pow(2,ceil(log2(n)));
      seg.resize(2*N);
      a.resize(N);
    }

    void Set(int pos, int val, int i=0, int l=0, int r=0) {
        if(i==0) i=1, l=0, r=N;
        if(r-l==1) {
            seg[i]+=val;
            return;
        }
        int m=(l+r)/2;
        if(pos<m) Set(pos, val, i*2, l, m);
        else Set(pos, val, i*2+1, m, r);
        seg[i]=seg[i*2]+seg[i*2+1];
    }

    void add(int l, int r, int v) {
        Set(l,v);
        Set(r,-v);
    }

    int calc(int lx, int rx, int i=0, int l=0, int r=0) {
        if(i==0) i=1, l=0, r=N;
        if(min(r,rx)<=max(l,lx)) return 0;
        if(lx<=l&&r<=rx) return seg[i];
        int m=(l+r)/2;
        return calc(lx, rx, i*2, l, m) + calc(lx, rx, i*2+1, m, r);
    }
};

void solve(int n, vector<int> s, int q, vector<vector<int>> w) {

    segtree st;
    st.init(n + 5);
    vector<int> done(n);
    for (auto &ew : w) {
        st.add(ew[0] - 1, ew[1], ew[2]);
    }

    vector<int> res(n);
    for (int i = 0; i < n; i++) {
        res[i] = st.calc(0, i + 1);
    }

    dbg(res);
}


#undef int

int main() {

    print(solve())

    return 0;
}