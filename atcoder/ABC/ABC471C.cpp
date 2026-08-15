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
    vector<ll> a(n);
    for (ll i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());

    ll ans = 0, curr = 0, left = -1, right = -1, min_dist = INF;
    for (ll i = 0; i < n; i++) {
        if (min_dist > abs(a[i])) {
            left = i;
            right = i;
            min_dist = abs(a[i]);
        }
    }
    ans += abs(a[left]);
    curr = a[left];
    left--;
    right++;

    while ((left != -1) || (right != n)) {
        if (left == -1) {
            ans += a[right] - curr;
            curr = a[right];
            right++;
        }
        else if (right == n) {
            ans += curr - a[left];
            curr = a[left];
            left--;
        }
        else if (curr - a[left] <= a[right] - curr) {
            ans += curr - a[left];
            curr = a[left];
            left--;
        }
        else {
            ans += a[right] - curr;
            curr = a[right];
            right++;
        }
    }
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}