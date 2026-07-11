#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1000000007;

void solve() {
    ll n;
    cin >> n;
    vector<ll> a(n + 2);
    a[n + 1] = 1'001;
    for (ll i = 1; i <= n; i++) cin >> a[i];

    ll left = 0, right = 0, ans = 0;
    while ((left != n + 2) && (right != n + 2)) {
        if (right - left == a[right] - a[left]) right++;
        else {
            ans = max(ans, right - left - 2);
            left++;
            left = right;
        }
    }
    ans = max(ans, right - left - 2);
    cout << ans;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}