#include "bits/stdc++.h"
#include <algorithm>
#include <functional>
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T> using oset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
// functions: set.insert(val), *(set.find_by_order(order-1)), set.order_of_key(val)
// less_equal for multiset

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


class Trie {
public:

    struct node {
        vector<node*> child;
        bool endOfWord;
        oset<int> values;

        node () {
            endOfWord = false;
            child = vector<node*>(26, NULL);
        }
    };

    node *root;

    Trie () {
        root = new node();
    }

    node* add (string &s, int val, int idx = 0, node *cur = NULL) {
        if (cur == NULL) cur = root;

        for (int i = idx; i < s.size(); i++) {
            int ch = s[i] - 'a';

            if (!cur->child[ch])
                cur->child[ch] = new node();

            cur = cur->child[ch];
            cur->values.insert(val);
        }
        cur->endOfWord = true;
        return cur;
    }

    int search (string &s, int val, int idx = 0, node *cur = NULL) {
        if (cur == NULL) cur = root;

        for (int i = idx; i < s.size(); i++) {
            cur = cur->child[s[i] - 'a'];

            if (!cur)
                return 0;
        }
        auto v = cur->values;
        dbg(v);
        return v.size() - v.order_of_key(val);
    }

};

vector<int> solve(vector<int> A, vector<string> B, vector<int> C) {

    Trie t;

    vector<int> ans;

    int n = A.size();
    for (int i = 0; i < n; i++) {
        string s = B[i];
        int k = C[i];

        if (A[i] == 1) {
            t.add(s, k);
        }
        if (A[i] == 2) {
            ans.push_back(t.search(s, k));
        }
    }

    return ans;
}


signed main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
    // cin >> t;

    for (int tt = 1; tt <= t; tt++) {
        cout << solve({1, 1, 2, 1, 2}, {"abc", "bac", "ab", "abc", "ab"}, {5, 1, 4, 4, 4}) << endl;
        cout << solve({1, 1, 1, 1, 2, 2}, {"abc", "abc", "abc", "abc", "a", "ab"}, {1, 2, 3, 2, 2, 3}) << endl;
    }

    return 0;
}