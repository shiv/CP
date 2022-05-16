#include "bits/stdc++.h"
#include <string>
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

void solve() {
    string s;
    cin>>s;
    int d;
    cin>>d;
    // dbg(d);
    // cout<<s<<endl;
    int second=stoi(s.substr(0,2))*60+stoi(s.substr(3, 2));
    int percent=(second*d)/100;
    // cout<<second<<' '<<percent<<'\n';
    // int ans=1000;
    // int time=100000;
    // // dbg(percent);

    // auto calc=[&](string s, string &tmp)
    // {
    //     int count=0;
    //     if(s[0]!='0')
    //     {
    //         int cur=s[0]-'0';
    //         for(int i=0;i<s.size();i++)
    //         {
    //             if((s[i]-'0')==cur)
    //             {
    //                 count++;
    //             }
    //             else
    //             {
    //                 count+=2;
    //             }
    //             cur=(s[i]-'0');
    //             tmp+=s[i];
    //         }
    //     }
    //     return count;
    // };


    auto doit = [&] (string &s) {
        // dbg(1, s);
        while (s.size() > 1 && s[0] == '0') {
            s = s.substr(1);
        }
        // dbg(2, s);
        int sum = s.size();
        int i = 1;
        while (i < s.size()) {
            if (s[i] != s[i - 1]) {
                sum++;
            }
            i++;
        }
        return sum;
    };

    string res;
    int moves = inf;
    for(int j = 0; j <= percent; j++) {
        {
            int i = second + j;
            int first = i / 60;
            int second = i % 60;
            string s = to_string(first) + (second < 10 ? "0" : "") + to_string(second);
            int curr = doit(s);
            if (moves > curr) {
                moves = curr;
                res = s;
            }
            if (first && second < 40) {
                first--;
                second += 60;
                string s = to_string(first) + (second < 10 ? "0" : "") + to_string(second);
                int curr = doit(s);
                if (moves > curr) {
                    moves = curr;
                    res = s;
                }
            }
        }
        {
            int i = second - j;
            int first = i / 60;
            int second = i % 60;
            string s = to_string(first) + (second < 10 ? "0" : "") + to_string(second);
            int curr = doit(s);
            if (moves > curr) {
                moves = curr;
                res = s;
            }
            if (first && second < 40) {
                first--;
                second += 60;
                string s = to_string(first) + (second < 10 ? "0" : "") + to_string(second);
                int curr = doit(s);
                if (moves > curr) {
                    moves = curr;
                    res = s;
                }
            }
        }
    }

    print(res);


    // dbg(second - percent,  second + percent);
    // string ret="";
    // for(int i=second-percent;i<=second+percent;i++)
    // {
    //     int first=i/60;
    //     int second=i%60;
    //     // dbg(first, second);
    //     int count=0;

    //     string s=to_string(first);
    //     string tmp="";
    //     count+=calc(s, tmp);
    //     s=to_string(second);
    //     count+=calc(s, tmp);

    //     if(ans>count)
    //     {
    //         ans=count;
    //         time=first*60+second;
    //         ret=tmp;
    //     }
    //     else if(ans==count)
    //     {
    //         if(abs(second-time)>abs(second-i))
    //         {
    //             ret=tmp;
    //             time=first*60+second;
    //         }
    //     }
    //     if(first&&second<=39)
    //     {
    //         first--;
    //         second+=60;
    //         count=0;

    //         tmp="";
    //         s=to_string(first);
    //         count+=calc(s,tmp);
    //         s=to_string(second);
    //         count+=calc(s,tmp);

    //         if(ans>count)
    //         {
    //             ans=count;
    //             ret=tmp;
    //             time=first*60+second;
    //         }
    //         else if(ans==count)
    //         {
    //             if(abs(second-time)>abs(second-i))
    //             {
    //                 ret=tmp;
    //                 time=first*60+second;
    //             }
    //         }
    //     }
    // }
    // cout<<ans<<'\n';
    // cout<<time<<'\n';
    // cout<<ret<<'\n';

}

signed main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int t = 1;
    cin >> t;

    for (int tt = 1; tt <= t; tt++) {
        cout << "Case #" << tt << ": ";
        solve();
    }

    return 0;
}