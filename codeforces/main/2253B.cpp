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
    vector<ll> a(n + 2);
    for (ll i = 1; i <= n; i++) cin >> a[i];

    bool has_swap = false;
    for (ll i = 1; i <= n - 1; i++) {
        // aabb -> abab
        if ((a[i - 1] == a[i]) && (a[i] != a[i + 1]) && (a[i + 1] == a[i + 2])) {   
            has_swap = true;
            swap(a[i], a[i + 1]);
            break;
        }
    }
    if (!has_swap) {
        for (ll i = 1; i <= n - 1; i++) {
            // aabc -> abac
            if ((a[i - 1] == a[i]) && (a[i] != a[i + 1]) && (a[i] != a[i + 2])) {  // 
                has_swap = true;
                swap(a[i], a[i + 1]);
                break;
            }
            // abcc -> acbc
            if ((a[i + 1] == a[i + 2]) && (a[i] != a[i + 1]) && (a[i - 1] != a[i + 1])) {
                has_swap = true;
                swap(a[i], a[i + 1]);
                break;
            }
        }
    }

    ll ans = 1;
    for (ll i = 1; i <= n - 1; i++) {
        if (a[i] != a[i + 1]) ans++;
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