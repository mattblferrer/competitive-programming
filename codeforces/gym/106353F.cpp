#include <bits/stdc++.h> 
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> p(n);
    int a_sum = 0, b_sum = 0;
    for (int i = 0; i < n; i++) {
        int ai, bi;
        cin >> ai >> bi;
        p[i] = {ai, bi};
        a_sum += ai;
        b_sum += bi;
    }
    for (int i = 0; i < n; i++) {
        if (p[i].second - p[i].first >= b_sum - a_sum) {
            cout << i + 1 << "\n";
            return 0;
        }
    }
    cout << "impossible\n";
    return 0;
}