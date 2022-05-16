/*
Gone are the days when you have to wait a day for anything to be delivered.A new startup is in town.
They promise to deliver goods from point a to point b via DRONES.

The company has 2 drones in operation. Assume there are M places where drones can deliver.
 The places M are arranged in a single row, equally spaced 1 metre apart.

The drones take instructions in the form of delivery request consisting of two integers,
'a' and 'b' respectively. To complete a delivery, a drone must travels to point a,
pick up the order, transports it to point b, and then stops at b until it receives
another delivery request.

Calculate the minimum total distance the drones must travel to complete all the deliveries in order.

**Note : First time any drone moves, there is no traveling cost.

Input :
The first line has two space-separated integers, M (the number of addresses) and  N(the number of delivery requests).
The subsequent lines each contain two space-separated integers, 'a' and 'b', respectively; each line  describes the  delivery requests.
Output :
print an integer denoting the minimum total distance that the drones must travel to complete all the deliveries in order.

Sample input:
5 4
1 5
3 2
4 1
2 4


output:
11
*/

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

struct pos {
    int a, b;
    friend istream& operator>>(istream &in, pos &n) {
        return in >> n.a >> n.b;
    }
};

void solve() {

    int m, n;
    scan(m, n);
    vector<pos> del(n);
    scan(del);

    int cost = 0;
    for (int i = 0; i < n; i++) {
        cost += abs(del[i].a - del[i].b);
    }

    /*
        dp[i][j] will store the optimum answer till ith delivery
        when the ith node is visited by jth drone
        (ith drone at del[i].b)
        pos[i][j] will store the position of j^1th drone when the ith
        node is visited by jth drone
    */

    vector<int> pref(n);
    for (int i = 1; i < n; i++) {
        pref[i] = pref[i - 1] + abs(del[i].a - del[i - 1].b);
    }
    auto go = [&] (int i, int j) {
        return pref[j] - pref[i];
    };

    vector<array<int, 2>> dp(n, array<int, 2>{inf, inf});
    vector<array<int, 2>> pos(n, array<int, 2>{-1, -1});

    dp[0][0] = dp[0][1] = 0;
    pos[0][1] = 0;

    for (int i = 1; i < n; i++) {
        for (int k = 0; k < 2; k++) {
            dp[i][k] = dp[i - 1][k] + go(i - 1, i);
            pos[i][k] = pos[i - 1][k];
        }
        for (int j = 0; j < i - 1; j++) {
            for (int k = 0; k < 2; k++) {
                int prev_other_pos = pos[j][k];
                // int curr_cost;
                // if (prev_other_pos == -1) {
                //     curr_cost = dp[j][k] + go(j, i) + go(j + 1, i - 1);
                // }
                // else {
                //     curr_cost = dp[j][k] + go(j, k) + go(j + 1, i - 1)
                //         + abs(del[prev_other_pos].b - del[j + 1].a);
                // }
                int curr_cost = dp[j][k];   // cost till last delivery
                curr_cost += abs(del[j].b - del[i].a);      // kth drone from j to i
                curr_cost += prev_other_pos == -1 ? 0 : abs(del[prev_other_pos].b - del[j + 1].a);          // if (k^1)th done some previous delivery
                curr_cost += go(j + 1, i - 1);

                if (dp[i][k] > curr_cost) {
                    dp[i][k] = curr_cost;
                    pos[i][k] = i - 1;
                }
            }
        }
        dbg(i, dp[i]);
        dbg(i, pos[i]);
    }

    dbg(cost);
    cost += min(dp.back()[0], dp.back()[1]);

    print(cost);
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