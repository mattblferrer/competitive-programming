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

    map<ll, ll, greater<ll>> cnt;
    for (ll i = 0; i < n; i++) {
        cnt[a[i]]++;
    }

    while (cnt.size() > 0) {
        map<ll, ll, greater<ll>> new_cnt;
        for (auto &[ai, c] : cnt) {
            cout << ai << " ";
            c--;
        }
        for (auto &[ai, c] : cnt) {
            if (c != 0) new_cnt[ai] = c; 
        }
        cnt = new_cnt;
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