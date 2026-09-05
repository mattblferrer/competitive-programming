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
    for (ll i = 0; i < n; i++) cin >> a[i];

    vector<ll> next_1(n, n), next_m1(n, n);
    ll curr_1 = n, curr_m1 = n, max_m1 = -1;
    for (ll i = n - 1; i >= 0; i--) {
        next_1[i] = curr_1;
        next_m1[i] = curr_m1;
        if (a[i] == 1) curr_1 = i;
        if (a[i] == -1) {
            curr_m1 = i;
            max_m1 = max(max_m1, i);
        }
    }

    ll score = 0, idx_max = -1;
    for (ll i = 0; i < n; i++) {
        if (a[i] == 0) continue;
        if (next_1[i] == n) {
            if (max_m1 == -1) break;
            else if (score < max_m1 - i - 1) {
                score = max_m1 - i - 1;
                idx_max = i;
            }
        }
        else if (score < next_1[i] - i - 1) {
            score = next_1[i] - i - 1;
            idx_max = i;
        }
    }

    for (ll i = 0; i < n; i++) {
        if (a[i] == -1) a[i] = 1;
    }
    if (idx_max != -1) {
        a[idx_max] = 1;
        a[idx_max + score + 1] = 1;
        for (ll i = idx_max + 1; i <= idx_max + score; i++) a[i] = 0;
    }

    for (ll i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    int t; cin >> t; while (t--) solve();
    return 0;
}