#include "bits/stdc++.h"
#include <string>
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
const int inf = 1e18L + 5, mod = 1e9 + 7, N = 2e5 + 5;
// Function to return ASCII
// value of a character
int val(char c)
{
    if (c >= '0' && c <= '9')
        return (int)c - '0';
    else
        return (int)c - 'A' + 10;
}

// Function to convert a number
// from given base to decimal number
int toDeci(string str, int base)
{
    // Stores the length
    // of the string
    int len = str.size();

    // Initialize power of base
    int power = 1;

    // Initialize result
    int num = 0;

    // Decimal equivalent is str[len-1]*1
    // + str[len-2]*base + str[len-3]*(base^2) + ...
    for (int i = len - 1; i >= 0; i--) {

        // A digit in input number must
        // be less than number's base
        if (val(str[i]) >= base) {
            printf("Invalid Number");
            return -1;
        }

        // Update num
        num += val(str[i]) * power;

        // Update power
        power = power * base;
    }

    return num;
}

// Function to return equivalent
// character of a given value
char reVal(int num)
{
    if (num >= 0 && num <= 9)
        return (char)(num + '0');
    else
        return (char)(num - 10 + 'A');
}

// Function to convert a given
// decimal number to a given base
string fromDeci(int base, int inputNum)
{
    // Store the result
    string res = "";

    // Repeatedly divide inputNum
    // by base and take remainder
    while (inputNum > 0) {

        // Update res
        res += reVal(inputNum % base);

        // Update inputNum
        inputNum /= base;
    }

    // Reverse the result
    reverse(res.begin(), res.end());

    return res;
}

// Function to convert a given number
// from a base to another base
int convertBase(string s, int a)
{
    // Convert the number from
    // base A to decimal
    int num = toDeci(s, a);

    // Convert the number from
    // decimal to base B

    return num;
}

void solve() {

    int a, b, k;
    scan(k, a, b);

    int A = convertBase(to_string(a), k);
    int B = convertBase(to_string(b), k);

    print(A * B);
}

signed main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t = 1;

    for (int tt = 1; tt <= t; tt++) {
        solve();
    }

    return 0;
}