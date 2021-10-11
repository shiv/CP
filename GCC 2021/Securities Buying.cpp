#include <bits/stdc++.h>
using namespace std;

int main(){

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int z;
    cin >> z;
    string s;
    getline(cin, s);
    getline(cin, s);
    s += ' ';

    vector<int> input_data;
    int m = s.length();
    int num = 0;
    for (int i = 0; i < m; i++) {
        if (s[i] == ' ') {
            input_data.emplace_back(num);
            num = 0;
        }
        else {
            num = (num << 3) + (num << 1) + (s[i] - '0');
        }
    }

    int n = input_data.size();

    pair<int, int> v[n];
    for (int i = 0; i < n; i++) {
        v[i].first = input_data[i];
        v[i].second = i + 1;
    }

    sort(v, v + n);
    int no_of_stocks_purchased = 0;

    for (int i = 0; i < n; i++) {
        if (z > 0) {
            int temp = min(z / v[i].first, v[i].second);
            no_of_stocks_purchased += temp;
            z -= temp * v[i].first;
        }
    }

    cout << no_of_stocks_purchased;
    return 0;
}