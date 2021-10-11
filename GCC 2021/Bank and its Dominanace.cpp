#include "bits/stdc++.h"
#pragma GCC optimize ("O3")
// #pragma GCC target ("sse4")
using namespace std;

int main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    string s;
    cin >> s;
    s += '1';

    int m = s.length();
    int temp;

    int high = -1, shigh = -1;

    for (int i = 0; i < m; i++) {
        if (s[i] == '1' && temp) {
            if (high <= temp) {
                shigh = high;
                high = temp;
            }
            else if (shigh < temp) {
                shigh = temp;
            }
        }
        else {
            temp = 0;
            while (i + temp < m && s[i + temp] == '0') {
                temp++;
            }
        }
    }

    // if (high == 0) {
    //     cout << 'B';
    // }
    // else if (high & 1 ^ 1) {
    //     cout << 'B';
    // }
    // else if (high == shigh) {
    //     cout << 'B';
    // }
    // else if ((high + 1) >> 1 <= shigh) {
    //     cout << 'B';
    // }
    if (high == 0 || high & 1 ^ 1 || (high + 1) >> 1 <= shigh) {
        cout << 'B';
    }
    else {
        cout << 'A';
    }

    return 0;
}