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

#define int int64_t
const int inf = 1e18L + 5, mod = 1e9 + 7, N = 1e5 + 5;

vector<int> spf(N, 0);
vector<bool> prime(N, true);
vector<int> primes;
void sieve() {
    prime[0] = prime[1] = false;
    for(int i = 2; i < N; i++) {
        if(prime[i]) {
            spf[i] = i;
            primes.push_back(i);
        }
        int prod;
        for(int j = 0; j < (int) primes.size() && primes[j] <= spf[i] && (prod = primes[j] * i) < N; j++) {
            spf[prod] = primes[j];
            prime[prod] = false;
        }
    }
}

vector<pair<int, int>> factorise(int num) {
    vector<pair<int, int>> factors;
    while(num > 1) {
        int factor = spf[num];
        int cnt = 0;
        while(spf[num] == factor) {
            num /= spf[num];
            cnt++;
        }
        factors.emplace_back(factor, cnt);
    }
    return factors;
};



void solve() {

    int n;
    cin >> n;
    vector<int> a(n);
    for (int &i : a) {
        cin >> i;
    }


    print(factorise(48));

}

signed main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    sieve();

    int t = 1;
    cin >> t;

    for (int tt = 1; tt <= t; tt++) {
        solve();
    }

    return 0;
}