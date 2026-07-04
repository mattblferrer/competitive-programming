#include <bits/stdc++.h>

using namespace std;

string solve() {
    int n;
    cin >> n;
    vector<pair<int, int>> scores;
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        scores.push_back({a, b});
    }
    for (int i = 0; i < n - 1; i++) {
        if (scores[i].first > scores[i + 1].first) return "no";
        if (scores[i].second > scores[i + 1].second) return "no";
    }
    return "yes";
}

int main() {
    cout << solve() << "\n";

    return 0;
}