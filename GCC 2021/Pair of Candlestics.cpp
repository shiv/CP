#include "bits/stdc++.h"
#pragma GCC optimize ("O3")
// #pragma GCC target ("sse4")
using namespace std;

signed main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int answer = 0;

    int n;
    cin >> n;

    int value;
    int stack[n];
    int top = -1;

    for (int i = 0; i < n; i++) {

        cin >> value;

        while (top != -1 && stack[top] <= value) {
            top--;
            answer++;
        }

        answer += top != -1;

        stack[++top] = value;
    }

    cout << answer << endl;

    return 0;
}