#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;

using namespace std;

void solve() {
    int n, sum = 0;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
    }
    double need = n * 4.5;
    if (sum >= need) {
        cout << 0 << "\n";
        return;
    }
    sort(a.begin(), a.end());
    for (int i = 0; i < n; i++) {
        sum += 5 - a[i];
        if (sum >= need) {
            cout << i + 1 << "\n";
            return;
        }
    }
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    solve();
    return 0;
}