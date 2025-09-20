#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;
using namespace std;

void solve() {
    int n, sum = 0, ans = 0;
    cin >> n;
    vector<int> d(n);
    for (int i = 0; i < n; i++) {
        cin >> d[i];
        sum += d[i];
    }
    while (sum != 0) {
        int min_d = 101, min_i;
        for (int i = 0; i < n; i++) {
            if (d[i] != 0 && d[i] < min_d) {
                min_d = min(min_d, d[i]);
                min_i = i;
            }
        }
        for (int i = min_i; i < n; i++) {
            if (d[i] == 0) break;
            d[i] -= min_d;
            sum -= min_d;
        }
        for (int i = min_i - 1; i >= 0; i--) {
            if (d[i] == 0) break;
            d[i] -= min_d;
            sum -= min_d;
        }
        ans++;
    }
    cout << ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout << setprecision(20);

    solve();
    return 0;
}