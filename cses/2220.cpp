#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;

using namespace std;

ll count(ll k) {
    deque<int> kd;
    ll temp = k;
    while (temp > 0) {
        kd.push_front(temp % 10);
        temp /= 10;
    }
    vector<vector<vector<int>>> dp(kd.size() + 1, vector<vector<int>>(10, vector<int>(2)));
    // TODO: counting numbers dp
}

void solve() {
    ll a, b;
    cin >> a >> b;
    cout << count(b) - count(a - 1) << '\n';
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    solve();
    return 0;
}