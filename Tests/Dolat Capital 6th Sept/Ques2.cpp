#include "bits/stdc++.h"
using namespace std;

struct timing {
    int startTime;
    int endTime;
    string orgName;
};

void solve() {

    const int totalDays = 24 + 5;

    int numberOfCharges;
    cin >> numberOfCharges;

    map<string, vector<pair<int, int>>> individualTimings;

    for (int idx = 0; idx < numberOfCharges; idx++) {
        timing currentOrg;
        cin >> currentOrg.orgName >> currentOrg.startTime >> currentOrg.endTime;
        individualTimings[currentOrg.orgName].push_back({currentOrg.startTime, currentOrg.endTime});
    }

    for (auto& currentOrg : individualTimings) {

        int totalCostForOrg = 0;
        vector<int> prev(totalDays, 0);

        string currentOrgName = currentOrg.first;
        vector<pair<int, int>> currentOrgTiming = currentOrg.second;

        for (int idx = 0; idx < currentOrgTiming.size(); idx++) {
            prev[currentOrgTiming[idx].first]++;
            prev[currentOrgTiming[idx].second]--;
        }

        for (int day = 1; day <= 24; day++) {
            prev[day] += prev[day - 1];
        }

        for (int day = 0; day <= 24; day++) {
            if (prev[day] == 0) {
                continue;
            }
            if (prev[day] == 1) {
                totalCostForOrg += 100;
            }
            else if (prev[day] == 2) {
                totalCostForOrg += 150;
            }
            else if (prev[day] == 3) {
                totalCostForOrg += 200;
            }
            else {
                totalCostForOrg += (200 + (prev[day] - 3) * 20);
            }
        }

        cout << "Organisation " << currentOrgName << " bill:" << totalCostForOrg << '\n';
    }
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