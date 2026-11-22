#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    string s;
    cin >> s;
    int score = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s.substr(i, 2) == "ha") score++;
        if (s.substr(i, 5) == "boooo") score--;
        if (s.substr(i, 5) == "bravo") score += 3;
    }
    cout << score << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}