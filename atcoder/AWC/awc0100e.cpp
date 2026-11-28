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

    map<ll, ll> cnt;
    for (ll i = 0; i < n; i++) cnt[a[i]]++;
    map<ll, ll> suff_cnt;
    ll curr = n;
    for (const auto& [ai, val]: cnt) {
        curr -= val;
        suff_cnt[ai] = curr;
    }
    for (ll i = 0; i < n; i++) {
        cout << suff_cnt[a[i]] << " ";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout << setprecision(20);

    solve();
    return 0;
}