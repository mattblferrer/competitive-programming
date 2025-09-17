#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;

using namespace std;

void solve() {
    string s;
    cin >> s;
    int max_l = 1, curr = 1;
    for (int i = 1; i < s.size(); i++) {
        if (s[i] != s[i - 1]) curr = 1;
        else curr++;
        max_l = max(max_l, curr);
    }
    cout << max_l << "\n";
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    solve();
    return 0;
}