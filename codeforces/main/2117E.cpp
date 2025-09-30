#include <bits/stdc++.h>
using ll = long long;
using pll = std::pair<long long, long long>;

using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];
    if (a[n - 1] == b[n - 1]) {
        cout << n << "\n";
        return;
    }
    vector<bool> seen(n + 1, false);
    for (int i = n - 2; i >= 0; i--) {
        if (a[i] == b[i] || a[i] == a[i + 1] || b[i] == b[i + 1]) {
            cout << i + 1 << "\n";
            return;
        }
        if (seen[a[i]] || seen[b[i]]) {
            cout << i + 1 << "\n";
            return;
        }
        seen[a[i + 1]] = true;
        seen[b[i + 1]] = true;
    }
    cout << "0\n";
} 

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t; std::cin >> t; while (t--) solve();
    return 0;
}