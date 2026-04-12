#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n, a, b;
    cin >> n >> a >> b;
    vector<ll> ans(n);
    if ((a + b <= 2) || (a + b > n + 1)) {
        cout << "no\n";
        return;
    }
    bool rev = false;
    if (a < b) {
        swap(a, b);
        rev = true;
    }
    for (ll i = 0; i < a - 2; i++) ans[i] = i + 1;
    ans[a - 2] = n - 1;
    for (ll i = 0; i < b - 1; i++) ans[n - i - 1] = a + i - 1;
    ans[n - b] = n;
    for (ll i = 0; i < n - a - b + 1; i++) ans[a + i - 1] = a + b + i - 2;
    if (rev) reverse(ans.begin(), ans.end());
    cout << "yes\n";
    for (ll i = 0; i < n; i++) cout << ans[i] << " ";
} 

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}