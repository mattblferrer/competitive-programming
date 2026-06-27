#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());

    ll ans = 0;
    for (int i = n - 1; i > 2; i -= 2) {
        ans += min(2 * a[0] + a[i] + a[i - 1], a[0] + 2 * a[1] + a[i]);
    }
    if (n % 2 == 1) ans += a[0] + a[1] + a[2];
    else ans += a[1];
    cout << ans << "\n";
}

int main() {
    solve();
    return 0;
}