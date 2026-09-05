#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
using pll = pair<ll, ll>;
#define M_PI 3.14159265358979323846
const ll INF = 2e18;
const ll MOD = 1'000'000'007;

void solve() {
    ll n;
    cin >> n;
    vector<ll> a(n);
    vector<ll> even, odd;
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
    }

    sort(a.begin(), a.end());
    vector<ll> na(n);
    na[n - 1] = a[n - 1];
    na[0] = a[n - 2];

    for (ll i = 0; i < n - 2; i++) {
        if (a[i] % 2 == 0) even.push_back(a[i]);
        else odd.push_back(a[i]);
    }

    if (even.size() >= odd.size()) {
        for (ll i = 0; i < odd.size(); i++) {
            na[2 * i + 1] = even[i];
            na[2 * i + 2] = odd[i];
        }
        for (ll i = odd.size(); i < even.size(); i++) {
            na[odd.size() + i + 1] = even[i];
        }
    }
    else {
        for (ll i = 0; i < even.size(); i++) {
            na[2 * i + 1] = odd[i];
            na[2 * i + 2] = even[i];
        }
        for (ll i = even.size(); i < odd.size(); i++) {
            na[even.size() + i + 1] = odd[i];
        }
    }

    ll init_sum = (na[0] + na[1]) / 2 + (na[n - 2] + na[n - 1]) / 2;
    ll new_sum = (na[n - 1] + na[1]) / 2 + (na[n - 2] + na[0]) / 2;
    if (new_sum < init_sum) swap(na[0], na[n - 1]);

    ll ans = 0;
    for (ll i = 0; i < n - 1; i++) {
        ans += (na[i] + na[i + 1]) / 2;
    }

    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}