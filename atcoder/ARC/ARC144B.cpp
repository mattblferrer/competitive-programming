#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    ll n, a, b;
    cin >> n >> a >> b;
    vector<ll> arr(n);
    for (ll i = 0; i < n; i++) cin >> arr[i];

    sort(arr.begin(), arr.end());
    ll left = arr[0] - 1, right = arr[n - 1] + 1;
    while (right - left > 1) {
        ll mid = (left + right) / 2;
        ll curr = 0;
        for (ll i = 0; i < n; i++) {
            if (mid >= arr[i]) curr += (mid - arr[i] + a - 1) / a;
            else curr -= (arr[i] - mid) / b;
        }
        if (curr > 0) right = mid;
        else left = mid;
    }
    cout << left << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}