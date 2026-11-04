// github.com/mattblferrer/competitive-programming

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
    set<ll> a_set;
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
        a_set.insert(a[i]);
    }

    ll ans = INF;
    for (ll i = 0; i < n; i++) {
        ll curr = n;
        for (ll j = 0; j < n; j++) {
            if (a[j] % a[i] == 0) curr--;
        }
        ans = min(ans, curr);
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