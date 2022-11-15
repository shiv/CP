#include<bits/stdc++.h>
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

#define int long long
#define fast_io ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

vector<string> getItems(vector<vector<string>> &entries) {

    vector<string> res;

    priority_queue<pair<int, string>> mx;
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> mn;

    int n = 1;

    for (auto &entry : entries) {

        string a = entry[0], b = entry[1], c = entry[2];

        if (a == "VIEW") {
            n++;
            res.push_back(mx.top().second);
            if (!mn.empty()) {
                auto t = mn.top();
                mn.pop();
                mx.push(t);
            }
        }
        else {
            if (mx.size() == n) {
                mn.push({stoi(c), b});
            }
            else {
                mx.push({stoi(c), b});
            }
        }

        if (!mn.empty() && ((mn.top().first == mx.top().first && mn.top().second < mx.top().second) || mn.top().first < mx.top().first)) {
            auto mxt = mx.top();
            auto mnt = mn.top();
            mn.pop();
            mx.pop();
            mn.push(mxt);
            mx.push(mnt);
        }
    }

    return res;
}

int32_t main() {
    fast_io;

    vector<vector<string>> s = {{"INSERT", "milk", "4"},
                                {"INSERT", "coffee", "3"},
                                {"VIEW", "-", "-"},
                                {"INSERT", "pizza", "5"},
                                {"INSERT", "gum", "1"},
                                {"VIEW", "-", "-"}};
    getItems(s);
    vector<vector<string>> t = {{"INSERT", "fries", "4"},
                                {"INSERT", "soda", "2"},
                                {"VIEW", "-", "-"},
                                {"VIEW", "-", "-"},
                                {"INSERT", "hamburger", "5"},
                                {"VIEW", "-", "-"},
                                {"INSERT", "nuggets", "4"},
                                {"INSERT", "cookie", "1"},
                                {"VIEW", "-", "-"},
                                {"VIEW", "-", "-"}};
    getItems(t);
    return 0;
}
/*
    My approach:
        First I initialized a max heap of (int, string) and a min heap of (int, string)
        For INSERT opertation, if the size of max heap is less than the nth query, then I am adding the item to the max heap
                            otherwise if the price of th new item to be inserted is less than the price of item at the top of the max heap, I am removing the top item of the max heap and inserting it to min heap and adding the new item into the max heap.
        This way the size of max heap is equal to the nth query as top of max heap always contains the nth cheapest item.
    Run-time Complexity: O(n * log(n))
        where n is the number of items
*/