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

vector<vector<int>> alternatingParityPermutations(int n) {

    vector<vector<int>> res;

    int n1 = (n + 1) / 2, n2 = n / 2;
    vector<int> v1(n1), v2(n2);
    for (int i = 0, j = 1; i < n1; i += 1, j += 2) {
        v1[i] = j;
    }
    for (int i = 0, j = 2; i < n2; i += 1, j += 2) {
        v2[i] = j;
    }

    auto fun = [&] (vector<int> v1, vector<int> v3) {
        do {
            auto v2 = v3;
            vector<int> temp(n);
            do {
                for (int i = 0, j = 0, k = 0; i < n; i++) {
                    if (i & 1 ^ 1) {
                        temp[i] = v1[j];
                        j++;
                    }
                    else {
                        temp[i] = v2[k];
                        k++;
                    }
                }
                res.emplace_back(temp);
            } while (next_permutation(v2.begin(), v2.end()));
        } while (next_permutation(v1.begin(), v1.end()));
    };

    fun(v1, v2);
    if (n1 == n2) {
        fun(v2, v1);
    }

    sort(res.begin(), res.end());

    return res;
}

int main() {

    auto res = alternatingParityPermutations(11);
    for (auto &a : res) {
        // print(a);
    }
    print(res.size());

    return 0;
}