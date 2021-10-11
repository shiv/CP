#include "bits/stdc++.h"
using namespace std;

signed main() {

    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int a, b, s;
    cin >> a >> b >> s;

    int A[a];
    for (int i = 0; i < a; i++) {
        cin >> A[i];
    }

    int B[b];
    for (int i = 0; i < b; i++) {
        cin >> B[i];
    }

    int sum = 0, x = 0, y = 0;
    while (y < b && sum + B[y] <= s) {
        sum += B[y++];
    }

    int answer = x + y;

    while (x < a) {

        sum += A[x++];

        while (y > 0 && sum > s) {
            sum -= B[--y];
        }

        if (sum <= s) {
            answer = max(answer, x + y);
        }
    }

    cout << answer;

    return 0;
}